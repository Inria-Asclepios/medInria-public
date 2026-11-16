/*=========================================================================

 medInria

 Copyright (c) INRIA 2026. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "vtkDataMeshSimpleWriter.h"
#include "vtkDataMeshHelper.h"

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

const char vtkDataMeshSimpleWriter::ID[] = "vtkDataMeshSimpleWriter";

vtkDataMeshSimpleWriter::vtkDataMeshSimpleWriter() : vtkDataMeshWriterBase()
{
}

QStringList vtkDataMeshSimpleWriter::handled() const
{
    return QStringList() << "vtkDataMesh";
}

QStringList vtkDataMeshSimpleWriter::s_handled()
{
    return QStringList() << "vtkDataMesh";
}

bool vtkDataMeshSimpleWriter::write(const QString& path)
{
    if (!this->data())
    {
        return false;
    }

    qDebug().noquote() << "Can write with: " << this->identifier();

    medAbstractData * medData = dynamic_cast<medAbstractData*>(this->data());

    if(medData->identifier() != "vtkDataMesh")
    {
        return false;
    }

    vtkMetaDataSet * mesh = dynamic_cast< vtkMetaDataSet*>( (vtkObject*)(this->data()->data()));
    if (!mesh)
    {
        return false;
    }

    DataMeshHelper::prepareMetaDataForAsciiReadOrWrite(mesh, true);
    bool success = true;
    try
    {
        setlocale(LC_NUMERIC, "C");
        QLocale::setDefault(QLocale("C"));

        mesh->Write(path.toLocal8Bit().constData());
    }
    catch (...)
    {
        qDebug() << metaObject()->className() << ": error writing to " << path;
        success = false;
    }
    DataMeshHelper::prepareMetaDataForAsciiReadOrWrite(mesh, false);

    return success;
}

QString vtkDataMeshSimpleWriter::description() const
{
    return tr( "VTK without metadata Mesh Writer" );
}

QString vtkDataMeshSimpleWriter::identifier() const
{
    return ID;
}

QStringList vtkDataMeshSimpleWriter::supportedFileExtensions() const
{
    return QStringList() << ".vtk" << ".vtp" << ".vtu";
}

bool vtkDataMeshSimpleWriter::registered()
{
  return medAbstractDataFactory::instance()->registerDataWriterType("vtkDataMeshSimpleWriter", 
        vtkDataMeshSimpleWriter::s_handled(), createVtkDataMeshSimpleWriter);
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataWriter *createVtkDataMeshSimpleWriter()
{
  return new vtkDataMeshSimpleWriter;
}


