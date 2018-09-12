/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include "medBinaryOperatorBase.h"
#include "medBinaryOperationPluginExport.h"


class itkNotOperatorPrivate;

class MEDBINARYOPERATIONPLUGIN_EXPORT itkNotOperator : public medBinaryOperatorBase
{
    Q_OBJECT
    
public:
    
    virtual QString description() const;
    
    static bool registered();

    int update();
    template <class ImageType> int run();

protected:
    void setInputData(medAbstractData* data, int channel = 0, int frame = 0) override;
};

dtkAbstractProcess *createitkNotOperator();


