#pragma once
/*=========================================================================

medInria

Copyright (c) INRIA 2026. All rights reserved.
See LICENSE.txt for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

=========================================================================*/

#include "vtkDataMeshPluginExport.h"
#include "vtkDataMeshWriterBase.h"

class vtkDataSetWriter;

/**
 * Simple VTK writer, no metadata added. 
 */
class VTKDATAMESHPLUGIN_EXPORT vtkDataMeshSimpleWriter : public vtkDataMeshWriterBase
{
    Q_OBJECT

public:
    vtkDataMeshSimpleWriter();
    ~vtkDataMeshSimpleWriter() override = default;

    QStringList handled() const override;
    static  QStringList s_handled();

    QString description() const override;
    QString identifier() const override;

    QStringList supportedFileExtensions() const override;

    static bool registered();

public slots:
    bool write (const QString& path);

private:
    static const char ID[];
};

dtkAbstractDataWriter *createVtkDataMeshSimpleWriter();
