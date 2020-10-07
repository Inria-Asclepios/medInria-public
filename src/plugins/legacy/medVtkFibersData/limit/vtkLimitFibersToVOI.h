#pragma once
/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2018. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medVtkFibersDataPluginExport.h>

#include <vtkPolyDataAlgorithm.h>
#include <vector>

class MEDVTKFIBERSDATAPLUGIN_EXPORT vtkLimitFibersToVOI: public vtkPolyDataAlgorithm
{

 public:
  static vtkLimitFibersToVOI *New();
  vtkTypeMacro(vtkLimitFibersToVOI, vtkPolyDataAlgorithm);
    
  void PrintSelf (ostream& os, vtkIndent indent){};
  
  
  /** Set the VOI */
  void SetVOI (const double&, const double&, const double&,
               const double&, const double&, const double&);


  /**
     Set the boolean operator: switch between concatenating the fibers (AND - 1)
     and removing the fibers (NOT - 0).
   */
  void SetBooleanOperation (int n)
  {
    this->BooleanOperation = n;
  }
  

  /**
     Set the boolean operator: switch between concatenating the fibers (AND - 0)
     and removing the fibers (NOT - 1).
   */
  void SetBooleanOperationToAND()
  {
    this->BooleanOperation = 1;
  }
  

  /**
     Set the boolean operator: switch between concatenating the fibers (AND - 0)
     and removing the fibers (NOT - 1).
   */
  void SetBooleanOperationToNOT()
  {
    this->BooleanOperation = 0;
  }

  vtkGetMacro (BooleanOperation, int);
  
  
 protected:
  vtkLimitFibersToVOI();
  ~vtkLimitFibersToVOI(){};
  
  // Usual data generation method
  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  

 private:
  vtkLimitFibersToVOI (const vtkLimitFibersToVOI&);
  void operator=(const vtkLimitFibersToVOI&);

  int BooleanOperation;

  double m_XMin;
  double m_XMax;
  double m_YMin;
  double m_YMax;
  double m_ZMin;
  double m_ZMax;
  
};




