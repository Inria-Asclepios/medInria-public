/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <itkFiltersProcessBase.h>
#include <itkMacro.h>
#include <itkProcessObject.h>

#include <medAbstractDataFactory.h>

class itkFiltersProcessBasePrivate
{
public:
    dtkSmartPointer<medAbstractImageData> inputData;
    dtkSmartPointer<medAbstractImageData> outputData;
};

itkFiltersProcessBase::itkFiltersProcessBase(itkFiltersProcessBase *parent) 
    : medAbstractProcess(parent), d(new itkFiltersProcessBasePrivate)
{  
    d->inputData = NULL;
    d->outputData = NULL;
}

itkFiltersProcessBase::itkFiltersProcessBase(const itkFiltersProcessBase& other)
     : medAbstractProcess(other), d(other.d)
{
}

itkFiltersProcessBase& itkFiltersProcessBase::operator = (const itkFiltersProcessBase& other)
{
    return *this;
}

void itkFiltersProcessBase::emitProgress(int progress)
{
    emit progressed(progress);
}

void itkFiltersProcessBase::setInputData(medAbstractData* data, int channel, int frame)
{
    Q_UNUSED(channel);
    Q_UNUSED(frame);

    if (!data)
        return;
   
    QString identifier = data->identifier();
    
    d->outputData = dynamic_cast<medAbstractImageData*> (medAbstractDataFactory::instance()->create(identifier));
    d->inputData = dynamic_cast<medAbstractImageData*> (data);
}

medAbstractData* itkFiltersProcessBase::getOutputData(int channel, int frame) const
{
    Q_UNUSED(channel);
    Q_UNUSED(frame);

    return d->outputData;
}

int itkFiltersProcessBase::update()
{
    int res = DTK_FAILURE;

    try
    {
        res = tryUpdate();
    }
    catch( itk::ExceptionObject & error )
    {
        qDebug() << "ExceptionObject caught in" << metaObject()->className() << "!";
        qDebug() << error.GetDescription();
    }

    return res;
}

void itkFiltersProcessBase::eventCallback ( itk::Object *caller, const itk::EventObject& event, void *clientData)
{
    itkFiltersProcessBase * source = reinterpret_cast<itkFiltersProcessBase *> ( clientData );
    itk::ProcessObject * processObject = ( itk::ProcessObject* ) caller;

    if ( !source ) { dtkWarn() << "Source is null"; }

    source->emitProgress((int) (processObject->GetProgress() * 100));
}

medAbstractImageData* itkFiltersProcessBase::getInputData()
{
    return d->inputData;
}

void itkFiltersProcessBase::setOutputData(medAbstractData* data)
{
    d->outputData = dtkSmartPointer<medAbstractData>(data);
}
