/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medAbstractProcess.h>
#include <dtkCore/dtkAbstractObject.h>

medAbstractProcess::medAbstractProcess(medAbstractProcess * parent) : dtkAbstractProcess(*new medAbstractProcessPrivate(this), parent)
{
}

medAbstractProcess::medAbstractProcess(const medAbstractProcess& other) : dtkAbstractProcess(*new medAbstractProcessPrivate(*other.d_func()), other)
{

}

medAbstractProcess::~medAbstractProcess()
{
}

void medAbstractProcess::setParameter(int data)
{
    setIntParameter(data);
}

void medAbstractProcess::setParameter(int data, int channel)
{
    setIntParameter(data, channel);
}

void medAbstractProcess::setParameter(int data, int channel, int frame)
{
    setIntParameter(data, channel, frame);
}

void medAbstractProcess::setParameter(int* data)
{
    setIntPointerParameter(data);
}

void medAbstractProcess::setParameter(int* data, int channel)
{
    setIntPointerParameter(data, channel);
}

void medAbstractProcess::setParameter(int* data, int channel, int frame)
{
    setIntPointerParameter(data, channel, frame);
}

void medAbstractProcess::setParameter(qlonglong data)
{
    setQLongLongParameter(data);
}

void medAbstractProcess::setParameter(qlonglong data, int channel)
{
    setQLongLongParameter(data, channel);
}

void medAbstractProcess::setParameter(qlonglong data, int channel, int frame)
{
    setQLongLongParameter(data, channel, frame);
}

void medAbstractProcess::setParameter(qlonglong* data)
{
    setQLongLongPointerParameter(data);
}

void medAbstractProcess::setParameter(qlonglong* data, int channel)
{
    setQLongLongPointerParameter(data, channel);
}

void medAbstractProcess::setParameter(qlonglong* data, int channel, int frame)
{
    setQLongLongPointerParameter(data, channel, frame);
}

void medAbstractProcess::setParameter(double data)
{
    setDoubleParameter(data);
}

void medAbstractProcess::setParameter(double data, int channel)
{
    setDoubleParameter(data, channel);
}

void medAbstractProcess::setParameter(double data, int channel, int frame)
{
    setDoubleParameter(data, channel, frame);
}

void medAbstractProcess::setParameter(double* data, int count)
{
    setDoublePointerParameter(data);
}

void medAbstractProcess::setParameter(double* data, int count, int channel)
{
    setDoublePointerParameter(data, channel);
}

void medAbstractProcess::setParameter(double* data, int count, int channel, int frame)
{
    setDoublePointerParameter(data, channel, frame);
}

void medAbstractProcess::setParameter(dtkAbstractObject* data)
{
    setParameter(data, 0, 0);
}

void medAbstractProcess::setParameter(dtkAbstractObject* data, int channel)
{
    setParameter(data, channel, 0);
}

void medAbstractProcess::setParameter(dtkAbstractObject* data, int channel, int frame)
{
    medAbstractData* medData = dynamic_cast<medAbstractData*>(data);

    if (medData != nullptr)
    {
        setDataParameter(medData, channel, frame);
    }
    else
    {
        qDebug() << metaObject()->className() << " only works on medAbstractData types.";
        dtkAbstractProcess::setParameter(data, channel, frame);
    }
}

void medAbstractProcess::setInput(dtkAbstractData* data)
{
    setInput(data, 0, 0);
}

void medAbstractProcess::setInput(dtkAbstractData* data, int channel)
{
    setInput(data, channel, 0);
}

void medAbstractProcess::setInput(dtkAbstractData* data, int channel, int frame)
{
    medAbstractData* medData = dynamic_cast<medAbstractData*>(data);

    if (medData != nullptr)
    {
        setInputData(medData, channel, frame);
    }
    else
    {
        qDebug() << metaObject()->className() << " only works on medAbstractData types.";
        dtkAbstractProcess::setInput(data, channel, frame);
    }
}

dtkAbstractData* medAbstractProcess::output()
{
    return output(0, 0);
}

dtkAbstractData* medAbstractProcess::output(int channel)
{
    return output(channel, 0);
}

dtkAbstractData* medAbstractProcess::output(int channel, int frame)
{
    return getOutputData(channel, frame);
}

void medAbstractProcess::setIntParameter(int data, int channel, int frame)
{
    qDebug() << metaObject()->className() << " does not take int parameters.";
}

void medAbstractProcess::setIntPointerParameter(int* data, int channel, int frame)
{
    qDebug() << metaObject()->className() << " does not take int* parameters.";
}

void medAbstractProcess::setQLongLongParameter(qlonglong data, int channel, int frame)
{
    qDebug() << metaObject()->className() << " does not take qlonglong parameters.";
}

void medAbstractProcess::setQLongLongPointerParameter(qlonglong* data, int channel, int frame)
{
    qDebug() << metaObject()->className() << " does not take qlonglong* parameters.";
}

void medAbstractProcess::setDoubleParameter(double data, int channel, int frame)
{
    qDebug() << metaObject()->className() << " does not take double parameters.";
}

void medAbstractProcess::setDoublePointerParameter(double* data, int count, int channel, int frame)
{
    qDebug() << metaObject()->className() << " does not take double* parameters.";
}

void medAbstractProcess::setDataParameter(medAbstractData* data, int channel, int frame)
{
    qDebug() << metaObject()->className() << " does not take medAbstractData* parameters.";
}

