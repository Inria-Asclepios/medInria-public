/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "itkFiltersBinaryFillholeProcess.h"

#include <dtkCore/dtkAbstractProcessFactory.h>

#include <itkImage.h>

#include <itkBinaryFillholeImageFilter.h>
#include <medUtilities.h>

class itkFiltersBinaryFillholeProcessPrivate
{
public:
    double binaryFillholeValue;
};

const double itkFiltersBinaryFillholeProcess::defaultBinaryFillholeValue = 10000.0;

//-------------------------------------------------------------------------------------------

itkFiltersBinaryFillholeProcess::itkFiltersBinaryFillholeProcess(itkFiltersBinaryFillholeProcess *parent)
    : itkFiltersProcessBase(parent), d(new itkFiltersBinaryFillholeProcessPrivate)
{  
    d->binaryFillholeValue = defaultBinaryFillholeValue;
}

itkFiltersBinaryFillholeProcess::itkFiltersBinaryFillholeProcess(const itkFiltersBinaryFillholeProcess& other)
     : itkFiltersProcessBase(other), d(other.d)
{
}

//-------------------------------------------------------------------------------------------

itkFiltersBinaryFillholeProcess::~itkFiltersBinaryFillholeProcess( void )
{
    delete d;
}

//-------------------------------------------------------------------------------------------

bool itkFiltersBinaryFillholeProcess::registered( void )
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("itkBinaryFillholeProcess", createitkFiltersBinaryFillholeProcess);
}

//-------------------------------------------------------------------------------------------

QString itkFiltersBinaryFillholeProcess::description() const
{
    return tr("ITK remove holes not connected to the boundary of the image.");
}

//-------------------------------------------------------------------------------------------

void itkFiltersBinaryFillholeProcess::setParameter(double data, int channel)
{
    if (channel != 0)
        return;
    
    d->binaryFillholeValue = data;
}

//-------------------------------------------------------------------------------------------

int itkFiltersBinaryFillholeProcess::tryUpdate()
{
    int res = DTK_FAILURE;

    if ( getInputData() )
    {
        QString id = getInputData()->identifier();

        if ( id == "itkDataImageChar3" )
        {
            res = updateProcess<char>();
        }
        else if ( id == "itkDataImageUChar3" )
        {
            res = updateProcess<unsigned char>();
        }
        else if ( id == "itkDataImageShort3" )
        {
            res = updateProcess<short>();
        }
        else if ( id == "itkDataImageUShort3" )
        {
            res = updateProcess<unsigned short>();
        }
        else if ( id == "itkDataImageInt3" )
        {
            res = updateProcess<int>();
        }
        else if ( id == "itkDataImageUInt3" )
        {
            res = updateProcess<unsigned int>();
        }
        else if ( id == "itkDataImageLong3" )
        {
            res = updateProcess<long>();
        }
        else if ( id== "itkDataImageULong3" )
        {
            res = updateProcess<unsigned long>();
        }
        else if ( id == "itkDataImageFloat3" )
        {
            res = updateProcess<float>();
        }
        else if ( id == "itkDataImageDouble3" )
        {
            res = updateProcess<double>();
        }
        else
        {
            res = medAbstractProcess::PIXEL_TYPE;
        }
    }

    return res;
}

template <class PixelType> int itkFiltersBinaryFillholeProcess::updateProcess()
{
//    typedef itk::Image< PixelType, 3 > ImageType;
//    typedef itk::BinaryFillholeImageFilter<ImageType> FilterType;
//    typename FilterType::Pointer filter = FilterType::New();

//    binaryFillholeFilter->SetInput ( dynamic_cast<ImageType *> ( ( itk::Object* ) ( getInputData()->data() ) ) );
//    binaryFillholeFilter->SetForegroundValue ( d->binaryFillholeValue );

//    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
//    callback->SetClientData ( ( void * ) this );
//    callback->SetCallback ( itkFiltersProcessBase::eventCallback );
//    binaryFillholeFilter->AddObserver ( itk::ProgressEvent(), callback );

//    binaryFillholeFilter->Update();

//    getOutputData()->setData ( binaryFillholeFilter->GetOutput() );

//    QString newSeriesDescription = "binary fill hole filter " + QString::number(d->binaryFillholeValue);
//    medUtilities::setDerivedMetaData(getOutputData(), getInputData(), newSeriesDescription);

    return DTK_SUCCEED;
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess * createitkFiltersBinaryFillholeProcess ( void )
{
    return new itkFiltersBinaryFillholeProcess;
}
