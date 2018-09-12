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

class itkMorphologicalFiltersProcessBasePrivate;

class ITKFILTERSPLUGIN_EXPORT itkMorphologicalFiltersProcessBase : public itkFiltersProcessBase
{
    Q_OBJECT

public:
    enum KernelShape
    {
        BallKernel,
        CrossKernel,
        BoxKernel,
    };

    itkMorphologicalFiltersProcessBase(itkMorphologicalFiltersProcessBase * parent = 0);
    itkMorphologicalFiltersProcessBase(const itkMorphologicalFiltersProcessBase& other);

public slots:
    int tryUpdate();

protected:
    void setDoubleParameter(double data, int channel = 0, int frame = 0) override;
    void setIntParameter(int data, int channel = 0, int frame = 0) override;

    template <class ImageType> void convertMmInPixels();
    template <class PixelType> int updateProcess();

private:
    itkMorphologicalFiltersProcessBasePrivate *d;
};

