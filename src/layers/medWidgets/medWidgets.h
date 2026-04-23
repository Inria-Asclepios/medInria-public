#pragma once
/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2020. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medProcessPresenterFactory.h>

#include <medAbstractMaskImageProcessPresenter.h>
#include <medAbstractDWIMaskingProcessPresenter.h>
#include <medAbstractDiffusionModelEstimationProcessPresenter.h>
#include <medAbstractDiffusionScalarMapsProcessPresenter.h>
#include <medAbstractTractographyProcessPresenter.h>

#include <medWidgetsExport.h>

namespace medWidgets
{
    namespace pluginManager
    {
        MEDWIDGETS_EXPORT void initialize(const QString& path = QString(), bool verbose = true);
    }

    namespace generic
    {
        MEDWIDGETS_EXPORT medAbstractProcessPresenterFactory& presenterFactory();
    }

    namespace maskImage
    {
        MEDWIDGETS_EXPORT medAbstractMaskImageProcessPresenterFactory& presenterFactory();
    }

    namespace dwiMasking
    {
        MEDWIDGETS_EXPORT medAbstractDWIMaskingProcessPresenterFactory& presenterFactory();
    }

    namespace diffusionModelEstimation
    {
        MEDWIDGETS_EXPORT medAbstractDiffusionModelEstimationProcessPresenterFactory& presenterFactory();
    }

    namespace diffusionScalarMaps
    {
        MEDWIDGETS_EXPORT medAbstractDiffusionScalarMapsProcessPresenterFactory& presenterFactory();
    }

    namespace tractography
    {
        MEDWIDGETS_EXPORT medAbstractTractographyProcessPresenterFactory& presenterFactory();
    }
}
