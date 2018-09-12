/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <dtkCore/dtkSmartPointer.h>
#include <medAbstractProcess.h>
#include "medBinaryOperationPluginExport.h"

class medBinaryOperatorBasePrivate;

class MEDBINARYOPERATIONPLUGIN_EXPORT medBinaryOperatorBase : public medAbstractProcess
{
    Q_OBJECT
    
public:
    medBinaryOperatorBase();
    virtual ~medBinaryOperatorBase();

    template <class ImageType> int run();
    template <class ImageType, class ImageType2> int runProcess();

    medAbstractData* getOutputData(int channel = 0, int frame = 0) const override;

public slots:
    //! Method to actually start the filter
    virtual int update();

protected:
    dtkSmartPointer <medAbstractData> m_inputA;
    dtkSmartPointer <medAbstractData> m_inputB;
    dtkSmartPointer <medAbstractData> m_output;

    void setInputData(medAbstractData* data, int channel = 0, int frame = 0) override;
};


