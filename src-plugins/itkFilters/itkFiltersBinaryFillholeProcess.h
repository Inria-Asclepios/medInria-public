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

class itkFiltersBinaryFillholeProcessPrivate;
class medAbstractData;

class ITKFILTERSPLUGIN_EXPORT itkFiltersBinaryFillholeProcess : public itkFiltersProcessBase
{
    Q_OBJECT
    
public:
    static const int defaultBinaryFillholeValue = 1000;

    itkFiltersBinaryFillholeProcess(itkFiltersBinaryFillholeProcess * parent = 0);
    itkFiltersBinaryFillholeProcess(const itkFiltersBinaryFillholeProcess& other);
    virtual ~itkFiltersBinaryFillholeProcess(void);
    static bool registered ( void );

    virtual QString description(void) const;
    
public slots:

    void setParameter ( double  data);
    void setParameter ( int data);
    int tryUpdate();

protected:
    template <class PixelType> int updateProcess();

private:
    itkFiltersBinaryFillholeProcessPrivate *d;
};

dtkAbstractProcess * createitkFiltersBinaryFillholeProcess(void);

