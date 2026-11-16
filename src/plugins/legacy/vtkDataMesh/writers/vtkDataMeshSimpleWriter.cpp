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

#include <vtkErrorCode.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridWriter.h>

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

    vtkDataSet* dataSet = mesh->GetDataSet();
    if (!dataSet)
    {
        return false;
    }

    bool res = true;
    DataMeshHelper::prepareMetaDataForAsciiReadOrWrite(mesh, true);
    try
    {
        setlocale(LC_NUMERIC, "C");
        QLocale::setDefault(QLocale("C"));

        // Surface or volume mesh
        if (auto poly = vtkPolyData::SafeDownCast(dataSet))
        {
            auto writer = vtkSmartPointer<vtkPolyDataWriter>::New();
            writer->SetFileName(path.toUtf8().constData());
            writer->SetInputData(poly);
            writer->SetFileVersion(42);
            writer->Write();
        }
        else if (auto grid = vtkUnstructuredGrid::SafeDownCast(dataSet))
        {
            auto writer = vtkSmartPointer<vtkUnstructuredGridWriter>::New();
            writer->SetFileName(path.toLocal8Bit().constData());
            writer->SetInputData(grid);
            writer->Write();
        }
    }
    catch (vtkErrorCode::ErrorIds error)
    {
        qDebug() << metaObject()->className() << vtkErrorCode::GetStringFromErrorCode(error);
        res = false;
    }
    DataMeshHelper::prepareMetaDataForAsciiReadOrWrite(mesh, false);

    return res;
}

QString vtkDataMeshSimpleWriter::description() const
{
    return tr( "VTK without metadata legacy Writer" );
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


