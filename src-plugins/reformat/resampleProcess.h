#pragma once
#include <medAbstractProcess.h>
#include <medAbstractData.h>
#include <reformatPluginExport.h>

class resampleProcessPrivate;
class REFORMATPLUGIN_EXPORT resampleProcess : public medAbstractProcess
{
    Q_OBJECT
public:
    resampleProcess(void);
    virtual ~resampleProcess(void);
    virtual QString description(void) const;
    static bool registered(void);

    medAbstractData* getOutputData(int channel = 0, int frame = 0) const override;

public slots:
    //! Method to actually start the filter
    int update(void);

protected:
    void setDoubleParameter(double data, int channel = 0, int frame = 0) override;

    void setInputData(medAbstractData* data, int channel = 0, int frame = 0) override;

private:
    template <class ImageType> void resample(const char * str);
    resampleProcessPrivate *d;
};
dtkAbstractProcess *createResampleProcess();
