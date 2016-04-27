/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medSegmentationWorkspace.h>

#include <medDataManager.h>
#include <medLayerParameterGroup.h>
#include <medSegmentationAbstractToolBox.h>
#include <medSegmentationSelectorToolBox.h>
#include <medTabbedViewContainers.h>
#include <medToolBoxFactory.h>
#include <medViewParameterGroup.h>

#include <stdexcept>

class medSegmentationWorkspacePrivate
{
public:
    // Give values to items without a constructor.
    medSegmentationWorkspacePrivate() :
       segmentationToolBox(NULL)
    {}

    medSegmentationSelectorToolBox *segmentationToolBox;
    medToolBox * roiManagementToolBox;
};


medSegmentationWorkspace::medSegmentationWorkspace(QWidget * parent /* = NULL */ ) :
medAbstractWorkspace(parent), d(new medSegmentationWorkspacePrivate)
{
    d->segmentationToolBox = new medSegmentationSelectorToolBox(parent);

    connect(d->segmentationToolBox,SIGNAL(success()),this,SLOT(onSuccess()));

    // Always have a parent.
    if (!parent)
        throw (std::runtime_error ("Must have a parent widget"));
    
    this->addToolBox(d->segmentationToolBox);
    if(medToolBoxFactory::instance()->createToolBox("medRoiManagementToolBox"))
	{
		d->roiManagementToolBox= medToolBoxFactory::instance()->createToolBox("medRoiManagementToolBox");
		d->roiManagementToolBox->setWorkspace(this);
		this->addToolBox(d->roiManagementToolBox);
	}

    setInitialGroups();

    connect(this->stackedViewContainers(), SIGNAL(containersSelectedChanged()),
            d->segmentationToolBox, SIGNAL(inputChanged()));
}

medSegmentationWorkspace::~medSegmentationWorkspace(void)
{
    delete d;
    d = NULL;
}

medSegmentationSelectorToolBox * medSegmentationWorkspace::segmentationToobox()
{
    return d->segmentationToolBox;
}

bool medSegmentationWorkspace::isUsable()
{
    medToolBoxFactory * tbFactory = medToolBoxFactory::instance();
    return (tbFactory->toolBoxesFromCategory("segmentation").size()!=0); 
}

//TODO: not tested yet
void medSegmentationWorkspace::onSuccess()
{
    medAbstractData * output = d->segmentationToolBox->currentToolBox()->processOutput();
    medDataManager::instance()->importData(output);
}
