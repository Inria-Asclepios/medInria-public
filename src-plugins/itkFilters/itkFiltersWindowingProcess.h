/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <itkFiltersProcessBase.h>

class itkFiltersWindowingProcessPrivate;
class medAbstractData;

class ITKFILTERSPLUGIN_EXPORT itkFiltersWindowingProcess : public itkFiltersProcessBase
{
    Q_OBJECT
    
public:
    static const double defaultMinimumIntensityValue;
    static const double defaultMaximumIntensityValue;

    itkFiltersWindowingProcess(itkFiltersWindowingProcess * parent = 0);
    itkFiltersWindowingProcess(const itkFiltersWindowingProcess& other);
    virtual ~itkFiltersWindowingProcess(void);
    static bool registered ( void );

    virtual QString description(void) const;
    
public slots:
    int tryUpdate();

protected:
    void setDoubleParameter(double data, int channel = 0, int frame = 0) override;

    template <class PixelType> int updateProcess();

private:
    itkFiltersWindowingProcessPrivate *d;
};

dtkAbstractProcess * createitkFiltersWindowingProcess(void);


