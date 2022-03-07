#pragma once
/*==============================================================================

 medInria

 Copyright (c) INRIA 2021. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

==============================================================================*/

#include <QString>

namespace med::python
{

bool initializeInterpreter(QStringList additionalModulePaths);
bool finalizeInterpreter();

namespace test
{

/// Returns the temporary directories used by the embedded interpreter.
///
QStringList getTemporaryDirectories();

}

} // namespace med::python