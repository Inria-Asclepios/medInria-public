/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <medAbstractSelectableToolBox.h>
#include "iterativeClosestPointPluginExport.h"

class iterativeClosestPointToolBoxPrivate;

/*! \brief Toolbox to match two meshes using the ICP (Iterative Closest Point) algorithm.
 *
 * This toolbox does not have named widgets which can be accessed in python pipelines.
 */
class ITERATIVECLOSESTPOINTPLUGIN_EXPORT iterativeClosestPointToolBox : public medAbstractSelectableToolBox
{
    Q_OBJECT
    MED_TOOLBOX_INTERFACE("Iterative Closest Point",
                          "Used to match two meshes using the ICP algorithm.",<<"Meshing")
    
public:
    iterativeClosestPointToolBox(QWidget *parent = 0);
    ~iterativeClosestPointToolBox();

    static bool registered();
    medAbstractData* processOutput();
    dtkPlugin* plugin();
    void addLayer(unsigned int layer);
    
public slots:
    void run();
    virtual void updateView();
    void resetComboBoxes();
    
protected slots:
    void displayOutput();

private:
    iterativeClosestPointToolBoxPrivate *d;
};


