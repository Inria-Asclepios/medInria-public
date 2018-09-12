/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <dtkCore/dtkSmartPointer.h>

#include <itkCommand.h>
#include <itkFiltersPluginExport.h>

#include <medAbstractImageData.h>
#include <medAbstractProcess.h>

class itkFiltersProcessBasePrivate;

class ITKFILTERSPLUGIN_EXPORT itkFiltersProcessBase : public medAbstractProcess
{
    Q_OBJECT

public:
    itkFiltersProcessBase(itkFiltersProcessBase * parent = 0);
    itkFiltersProcessBase(const itkFiltersProcessBase& other);
    itkFiltersProcessBase& operator = (const itkFiltersProcessBase& other);
    
    void emitProgress(int progress);

    virtual int tryUpdate(){return DTK_FAILURE;}
    int update();

    medAbstractImageData* getInputData();
    medAbstractData* getOutputData(int channel = 0, int frame = 0) const override;

    static void eventCallback ( itk::Object *caller, const itk::EventObject& event, void *clientData);

protected:
    void setInputData(medAbstractData* data, int channel = 0, int frame = 0) override;
    void setOutputData(medAbstractData* data);

private:
    itkFiltersProcessBasePrivate *d;
};


