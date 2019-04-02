/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "medVtkViewItkDataImage4DInteractor.h"

#include <medAbstractImageData.h>
#include <medAbstractImageView.h>
#include <medIntParameter.h>
#include <medMetaDataKeys.h>
#include <medTimeLineParameter.h>
#include <medViewFactory.h>
#include <medVtkViewBackend.h>

#include <vtkActor.h>
#include <vtkImageActor.h>
#include <vtkImageProperty.h>
#include <vtkMetaDataSetSequence.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

class medVtkViewItkDataImage4DInteractorPrivate
{
public:
    typedef vtkSmartPointer <vtkActor>  ActorSmartPointer;
    typedef vtkSmartPointer <vtkProperty>  PropertySmartPointer;

    medAbstractImageView *view;
    vtkImageView2D *view2d;
    vtkImageView3D *view3d;

    vtkMetaDataSetSequence *sequence;
    medAbstractImageData *imageData;

    double currentTime;

    vtkSmartPointer<vtkTextActor> textActor;
    medIntParameter *slicingParameter;
};

template <typename TYPE>
bool AppendImageSequence(medAbstractData* data,medAbstractImageView* view,vtkMetaDataSetSequence* sequence, int& layer) {

    if (itk::Image<TYPE,4>* image = dynamic_cast<itk::Image<TYPE,4>*>(static_cast<itk::Object*>(data->data())))
    {

        medVtkViewBackend* backend = static_cast<medVtkViewBackend*>(view->backend());

        sequence->SetITKDataSet<TYPE>(image);

        vtkMetaImageData* metaimage = vtkMetaImageData::SafeDownCast(sequence->GetMetaDataSet(0U));
        vtkImageData*     vtkimage  = vtkImageData::SafeDownCast(sequence->GetDataSet());

        backend->view2D->SetInput(vtkimage,metaimage->GetOrientationMatrix(), layer);
        backend->view3D->SetInput(vtkimage,metaimage->GetOrientationMatrix(), layer);
        layer = backend->view2D->GetNumberOfLayers()-1;

        return true;
    }
    return false;
}

medVtkViewItkDataImage4DInteractor::medVtkViewItkDataImage4DInteractor(medAbstractView *parent):
    medVtkViewItkDataImageInteractor(parent), d(new medVtkViewItkDataImage4DInteractorPrivate)
{
    d->view = dynamic_cast<medAbstractImageView *>(parent);

    medVtkViewBackend* backend = static_cast<medVtkViewBackend*>(parent->backend());
    d->view2d = backend->view2D;
    d->view3d = backend->view3D;

    d->currentTime = 0.0;

    d->textActor = nullptr;
    d->slicingParameter = nullptr;
}

medVtkViewItkDataImage4DInteractor::~medVtkViewItkDataImage4DInteractor()
{

}

QString medVtkViewItkDataImage4DInteractor::description() const
{
    return tr("Interactor displaying 4D Meshes");
}

QString medVtkViewItkDataImage4DInteractor::identifier() const
{
    return "medVtkViewItkDataImage4DInteractor";
}

QStringList medVtkViewItkDataImage4DInteractor::handled() const
{
    return medVtkViewItkDataImage4DInteractor::dataHandled();
}

QStringList medVtkViewItkDataImage4DInteractor::dataHandled()
{
    QStringList d = QStringList() << "itkDataImageChar4"
                                  << "itkDataImageUChar4"
                                  << "itkDataImageShort4"
                                  << "itkDataImageUShort4"
                                  << "itkDataImageInt4"
                                  << "itkDataImageUInt4"
                                  << "itkDataImageLong4"
                                  << "itkDataImageULong4"
                                  << "itkDataImageFloat4"
                                  << "itkDataImageDouble4";
    return  d;
}

bool medVtkViewItkDataImage4DInteractor::registered()
{
    medViewFactory *factory = medViewFactory::instance();
    return factory->registerInteractor<medVtkViewItkDataImage4DInteractor>("medVtkViewItkDataImage4DInteractor",
                                                                          QStringList () << "medVtkView" <<
                                                                          medVtkViewItkDataImage4DInteractor::dataHandled());
}

void medVtkViewItkDataImage4DInteractor::setInputData(medAbstractData *data)
{
    d->imageData = dynamic_cast<medAbstractImageData *>(data);
    if(!d->imageData)
        return;

    if( data->identifier().contains("itkDataImage") &&  d->imageData->Dimension() == 4 ) {

        d->sequence = vtkMetaDataSetSequence::New();

        int layer = d->view->layer(data);

        if (  AppendImageSequence<char>(data,d->view,d->sequence, layer)           ||
              AppendImageSequence<unsigned char>(data,d->view,d->sequence, layer)  ||
              AppendImageSequence<short>(data,d->view,d->sequence, layer)          ||
              AppendImageSequence<unsigned short>(data,d->view,d->sequence, layer) ||
              AppendImageSequence<int>(data,d->view,d->sequence, layer)            ||
              AppendImageSequence<unsigned int>(data,d->view,d->sequence, layer)   ||
              AppendImageSequence<long>(data,d->view,d->sequence, layer)           ||
              AppendImageSequence<unsigned long>(data,d->view,d->sequence, layer)  ||
              AppendImageSequence<float>(data,d->view,d->sequence, layer)          ||
              AppendImageSequence<double>(data,d->view,d->sequence, layer))
        {
            double maxTime = 1.0;
            if (data->hasMetaData(medMetaDataKeys::SeriesTime.key()))
            {
                maxTime = data->metadata(medMetaDataKeys::SeriesTime.key()).toDouble();
            }

            double frameRate = (double)d->sequence->GetNumberOfMetaDataSets() / maxTime;
            d->imageData->setMetaData("SequenceDuration", QString::number(maxTime));
            d->imageData->setMetaData("SequenceFrameRate", QString::number(frameRate));

            qDebug() << "SequenceDuration" << maxTime;
            qDebug() << "SequenceFrameRate" << frameRate;

            d->view2d->GetImageActor(d->view2d->GetCurrentLayer())->GetProperty()->SetInterpolationTypeToCubic();
            initParameters(d->imageData);

            double* range = d->sequence->GetScalarRange();
            d->view2d->SetColorRange(range);
            this->initWindowLevelParameters(range);

            medVtkViewItkDataImageInteractor::createSlicingParam();

            if(d->view->layer(d->imageData) == 0)
            {
                switch(d->view2d->GetViewOrientation())
                {
                case vtkImageView2D::VIEW_ORIENTATION_AXIAL:
                    d->view->setOrientation(medImageView::VIEW_ORIENTATION_AXIAL);
                    break;
                case vtkImageView2D::VIEW_ORIENTATION_SAGITTAL:
                    d->view->setOrientation(medImageView::VIEW_ORIENTATION_SAGITTAL);
                    break;
                case vtkImageView2D::VIEW_ORIENTATION_CORONAL:
                    d->view->setOrientation(medImageView::VIEW_ORIENTATION_CORONAL);
                    break;
                }
            }
        }
    }
}

medAbstractData *medVtkViewItkDataImage4DInteractor::inputData() const
{
    return d->imageData;
}

QWidget* medVtkViewItkDataImage4DInteractor::buildToolBoxWidget()
{
    QWidget *toolBoxWidget = new QWidget;
    QVBoxLayout *tbLayout = new QVBoxLayout(toolBoxWidget);
    tbLayout->addWidget(medVtkViewItkDataImageInteractor::buildToolBoxWidget());

    return toolBoxWidget;
}

QWidget* medVtkViewItkDataImage4DInteractor::buildToolBarWidget()
{
    return medVtkViewItkDataImageInteractor::buildToolBarWidget();
}

QWidget* medVtkViewItkDataImage4DInteractor::buildLayerWidget()
{
    return medVtkViewItkDataImageInteractor::buildLayerWidget();
}

QList<medAbstractParameter*> medVtkViewItkDataImage4DInteractor::linkableParameters()
{
    QList<medAbstractParameter*> parameters;
    parameters << medVtkViewItkDataImageInteractor::linkableParameters();
    return parameters;
}

void medVtkViewItkDataImage4DInteractor::setCurrentTime(double time)
{
    if(d->sequence->GetTime() == time)
        return;
    d->sequence->UpdateToTime(time);

    // Set the current time on the view if needed
    QString displayedTime = d->view->timeLineParameter()->getDisplayedTime();
    if (displayedTime != "")
    {
        // Refresh view size in case of resize
        QSize size = d->view->viewWidget()->size();
        int newSizeX = (int)((double)size.width()/90.0);
        int newSizeY = (int)((double)size.height()/1.5);

        // Display Time + Shift
        if (d->textActor == nullptr)
        {
            d->textActor = vtkSmartPointer<vtkTextActor>::New();
            d->textActor->SetInput(displayedTime.toStdString().c_str());
            d->textActor->SetDisplayPosition(newSizeX, newSizeY);
            d->textActor->GetTextProperty()->SetColor(1.0, 0.0, 0.0);
            d->textActor->GetTextProperty()->SetFontSize(20);

            d->view3d->GetRenderer()->AddViewProp(d->textActor);
            d->view2d->GetRenderer()->AddViewProp(d->textActor);
        }
        else
        {
            d->textActor->SetInput(displayedTime.toStdString().c_str());
            d->textActor->SetDisplayPosition(newSizeX, newSizeY);
        }
        d->view->render();
    }
    else
    {
        if (d->textActor != nullptr)
        {
            d->view3d->GetRenderer()->RemoveViewProp(d->textActor);
            d->view2d->GetRenderer()->RemoveViewProp(d->textActor);
            d->textActor = nullptr;
        }
    }
}

void medVtkViewItkDataImage4DInteractor::updateWidgets()
{
    medVtkViewItkDataImageInteractor::updateWidgets();
}

QString medVtkViewItkDataImage4DInteractor::name() const
{
    return "medVtkViewItkDataImage4DInteractor";
}
