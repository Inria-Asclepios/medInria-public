/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include "iterativeClosestPointPluginExport.h"

#include <medAbstractData.h>
#include <medAbstractProcess.h>

class iterativeClosestPointProcessPrivate;

class ITERATIVECLOSESTPOINTPLUGIN_EXPORT iterativeClosestPointProcess : public medAbstractProcess
{
    Q_OBJECT
    
public:
    iterativeClosestPointProcess();
    virtual ~iterativeClosestPointProcess();
    
    virtual QString description() const;
    
    static bool registered();

    medAbstractData* getOutputData(int channel = 0, int frame = 0) const override;
    
public slots:
    //! Method to actually start the filter
    int update();

protected:
    void setDoubleParameter(double data, int channel = 0, int frame = 0) override;
    void setIntParameter(int data, int channel = 0, int frame = 0) override;

    void setInputData(medAbstractData* data, int channel = 0, int frame = 0) override;

private:
    iterativeClosestPointProcessPrivate *d;
};

dtkAbstractProcess *createiterativeClosestPointProcess();


