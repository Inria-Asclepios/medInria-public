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

class itkFiltersGaussianProcessPrivate;
class medAbstractData;

class ITKFILTERSPLUGIN_EXPORT itkFiltersGaussianProcess : public itkFiltersProcessBase
{
    Q_OBJECT
    
public:
    static const double defaultSigma;

    itkFiltersGaussianProcess(itkFiltersGaussianProcess * parent = 0);
    itkFiltersGaussianProcess(const itkFiltersGaussianProcess& other);
    virtual ~itkFiltersGaussianProcess(void);
    static bool registered ( void );

    virtual QString description(void) const;
    
public slots:
    int tryUpdate();

protected:
    void setDoubleParameter(double data, int channel = 0, int frame = 0) override;

    template <class PixelType> int updateProcess();

private:
    itkFiltersGaussianProcessPrivate *d;
};

dtkAbstractProcess * createitkFiltersGaussianProcess(void);


