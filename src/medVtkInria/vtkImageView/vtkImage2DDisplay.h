#pragma once
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkSetGet.h>
#include "medVtkImageInfo.h"


class vtkImage2DDisplay : public vtkObject
{
public:
  static vtkImage2DDisplay * New();
  vtkTypeMacro (vtkImage2DDisplay, vtkObject);

  virtual void SetInput(vtkAlgorithmOutput*  pi_poVtkAlgoPort);
  //virtual vtkImageData* GetInput() { return this->Input; }

  virtual vtkLookupTable * GetLookupTable() const;

  virtual vtkImageActor* GetImageActor() { return this->ImageActor; }

  virtual vtkImageMapToColors* GetWindowLevel() const
  { return this->WindowLevel; }
  vtkSetMacro(ColorWindow, double);
  vtkGetMacro(ColorWindow,double);
  vtkSetMacro(ColorLevel, double);
  vtkGetMacro(ColorLevel,double);

  virtual vtkColorTransferFunction* GetColorTransferFunction() { return this->ColorTransferFunction; }
  void SetColorTransferFunction ( vtkColorTransferFunction* function);
  void SetOpacityTransferFunction(vtkPiecewiseFunction* opacity);
  virtual vtkPiecewiseFunction* GetOpacityTransferFunction() { return this->OpacityTransferFunction; }
  virtual medVtkImageInfo* GetMedVtkImageInfo();

  virtual bool isInputSet();

  vtkGetMacro(UseLookupTable,bool);
  vtkSetMacro(UseLookupTable, bool);

protected:
  vtkImage2DDisplay();
  ~vtkImage2DDisplay();

private:
  vtkSmartPointer<vtkImageMapToColors>        WindowLevel;
  vtkSmartPointer<vtkImageData>               Input;
  vtkSmartPointer<vtkImageActor>              ImageActor;
  double                                      ColorWindow;
  double                                      ColorLevel;
  bool                                        UseLookupTable;
  vtkSmartPointer<vtkColorTransferFunction >  ColorTransferFunction;
  vtkSmartPointer<vtkPiecewiseFunction>       OpacityTransferFunction;
  medVtkImageInfo                             m_sVtkImageInfo;


  vtkImage2DDisplay (const vtkImage2DDisplay&);
  void operator=(const vtkImage2DDisplay&);
};
