#pragma once
/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2020. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medAbstractProcess.h>

#include <medAbstractMaskImageProcess.h>
#include <medAbstractDWIMaskingProcess.h>
#include <medAbstractDiffusionModelEstimationProcess.h>
#include <medAbstractDiffusionScalarMapsProcess.h>
#include <medAbstractTractographyProcess.h>

#include <medAbstractDataConverter.h>

#include <medCoreExport.h>

namespace medCore
{
    namespace pluginManager
    {
        MEDCORE_EXPORT void initialize(const QString& path = QString());
    }

    DTK_DECLARE_CONCEPT(medAbstractProcess,MEDCORE_EXPORT,generic)
    DTK_DECLARE_CONCEPT(medAbstractDWIMaskingProcess,MEDCORE_EXPORT,dwiMasking)
    DTK_DECLARE_CONCEPT(medAbstractDiffusionModelEstimationProcess,MEDCORE_EXPORT,diffusionModelEstimation)
    DTK_DECLARE_CONCEPT(medAbstractDiffusionScalarMapsProcess,MEDCORE_EXPORT,diffusionScalarMaps)
    DTK_DECLARE_CONCEPT(medAbstractTractographyProcess,MEDCORE_EXPORT,tractography)
    DTK_DECLARE_CONCEPT(medAbstractMaskImageProcess, MEDCORE_EXPORT, maskImage)
    DTK_DECLARE_CONCEPT(medAbstractDataConverter,MEDCORE_EXPORT,dataConverter)
}
