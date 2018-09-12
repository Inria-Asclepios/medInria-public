/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include "itkFiltersProcessBase.h"

class itkFiltersComponentSizeThresholdProcessPrivate;
class dtkAbstractData;

class ITKFILTERSPLUGIN_EXPORT itkFiltersComponentSizeThresholdProcess : public itkFiltersProcessBase
{
    Q_OBJECT
    
public:
    static const double defaultMinimumSize;

    itkFiltersComponentSizeThresholdProcess(itkFiltersComponentSizeThresholdProcess * parent = 0);
    itkFiltersComponentSizeThresholdProcess(const itkFiltersComponentSizeThresholdProcess& other);
    virtual ~itkFiltersComponentSizeThresholdProcess(void);
    static bool registered ( void );

    virtual QString description(void) const;
    
public slots:
    int tryUpdate();

protected:
    void setIntParameter(int data, int channel = 0, int frame = 0) override;

    template <class PixelType> int castToUInt3();
    template <class PixelType> int updateProcess();

private:
    itkFiltersComponentSizeThresholdProcessPrivate *d;
};

dtkAbstractProcess * createitkFiltersComponentSizeThresholdProcess(void);

