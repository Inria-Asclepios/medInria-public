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
#include "medBinaryOperationPluginExport.h"

class medBinaryOperationToolBoxPrivate;

/*! \brief Toolbox to compute binary operations between masks (OR, AND, XOR, etc.).
 *
 * This toolbox does not have named widgets which can be accessed in python pipelines.
 */
class MEDBINARYOPERATIONPLUGIN_EXPORT medBinaryOperationToolBox : public medAbstractSelectableToolBox
{
    Q_OBJECT
    MED_TOOLBOX_INTERFACE("Binary Operation","Compute binary operations between masks (OR, AND, XOR, etc.).",<<"Filtering")
    
public:
    medBinaryOperationToolBox(QWidget *parent = 0);
    ~medBinaryOperationToolBox();
    
    medAbstractData *processOutput();
    
    static bool registered();
    dtkPlugin * plugin();
  
signals:
    void success();
    void failure();
    
public slots:
    void run();
    void update (medAbstractData*){}

protected slots:

    /** Slot called when external input finishes being imported. */
    virtual void onSecondInputImported(const medDataIndex &index);

    /**
     * Slot called when the @meDropSite is clicked.
     * Will open a @QFileDialog so the user can choose
     * and external ROI image to open.
     */
    virtual void onDropSiteClicked();

    virtual void clearDropsite();
    void onXorButtonToggled(bool);
    void onAndButtonToggled(bool);
    void onOrButtonToggled(bool);
    void onNotButtonToggled(bool);
    
private:
    medBinaryOperationToolBoxPrivate *d;
};


