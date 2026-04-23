/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2020. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medCore.h>

namespace medCore
{

DTK_DEFINE_LAYER_MANAGER

namespace pluginManager
{
    void initialize(const QString& path)
    {
        for(QString const& realpath : path.split(';'))
        {
            if(realpath.isEmpty())
                break;

            medCore::dwiMasking::pluginManager().initialize(realpath);
            medCore::diffusionModelEstimation::pluginManager().initialize(realpath);
            medCore::diffusionScalarMaps::pluginManager().initialize(realpath);
            medCore::tractography::pluginManager().initialize(realpath);
            medCore::maskImage::pluginManager().initialize(realpath);
            medCore::dataConverter::pluginManager().initialize(realpath);
        }
    }
}

DTK_DEFINE_CONCEPT(medAbstractProcess,generic,medCore)
DTK_DEFINE_CONCEPT(medAbstractDWIMaskingProcess,dwiMasking,medCore)
DTK_DEFINE_CONCEPT(medAbstractDiffusionModelEstimationProcess,diffusionModelEstimation,medCore)
DTK_DEFINE_CONCEPT(medAbstractDiffusionScalarMapsProcess,diffusionScalarMaps,medCore)
DTK_DEFINE_CONCEPT(medAbstractTractographyProcess,tractography,medCore)
DTK_DEFINE_CONCEPT(medAbstractMaskImageProcess,maskImage,medCore)
DTK_DEFINE_CONCEPT(medAbstractDataConverter,dataConverter,medCore)

} // end of medCore
