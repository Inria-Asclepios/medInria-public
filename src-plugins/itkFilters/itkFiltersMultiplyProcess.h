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

class itkFiltersMultiplyProcessPrivate;
class medAbstractData;

class ITKFILTERSPLUGIN_EXPORT itkFiltersMultiplyProcess : public itkFiltersProcessBase
{
    Q_OBJECT
    
public:
    static const double defaultMultiplyFactor;

    itkFiltersMultiplyProcess(itkFiltersMultiplyProcess * parent = 0);
    itkFiltersMultiplyProcess(const itkFiltersMultiplyProcess& other);
    virtual ~itkFiltersMultiplyProcess(void);
    static bool registered ( void );

    virtual QString description(void) const;
    
public slots:
    int tryUpdate();

protected:
    void setDoubleParameter(double data, int channel = 0, int frame = 0) override;

    template <class PixelType> int updateProcess();

private:
    itkFiltersMultiplyProcessPrivate *d;
};

dtkAbstractProcess * createitkFiltersMultiplyProcess(void);


