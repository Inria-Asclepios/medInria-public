/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <vtkDataMesh4DWriter.h>

#include <medAbstractDataFactory.h>
#include <medAbstractData.h>
#include <dtkLog/dtkLog.h>

#include <vtkDataManagerWriter.h>
#include <vtkDataManager.h>
#include <vtkFieldData.h>
#include <vtkMetaDataSetSequence.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>

const char vtkDataMesh4DWriter::ID[] = "vtkDataMesh4DWriter";
const QString vtkDataMesh4DWriter::metaDataFieldPrefix = "medMetaData::";

vtkDataMesh4DWriter::vtkDataMesh4DWriter()
{
  this->writer = vtkDataManagerWriter::New();
}

vtkDataMesh4DWriter::~vtkDataMesh4DWriter()
{
  this->writer->Delete();
}

QStringList vtkDataMesh4DWriter::handled() const
{
    return QStringList() << "vtkDataMesh4D";
}

QStringList vtkDataMesh4DWriter::s_handled()
{
    return QStringList() << "vtkDataMesh4D";
}

bool vtkDataMesh4DWriter::canWrite(const QString& path)
{
    if ( ! this->data())
        return false;

    return dynamic_cast<vtkMetaDataSetSequence*>((vtkObject*)(this->data()->data()));
}

bool vtkDataMesh4DWriter::write(const QString& path)
{
  if (!this->data())
    return false;

  qDebug() << "Can write with: " << this->identifier();

  medAbstractData *medData = dynamic_cast<medAbstractData*>(this->data());

  if(medData->identifier()!="vtkDataMesh4D")
  {
    return false;
  }

  vtkMetaDataSetSequence* sequence = dynamic_cast< vtkMetaDataSetSequence* >( (vtkObject*)(this->data()->output()));
  if (!sequence)
    return false;

  foreach (vtkMetaDataSet* dataSet, sequence->GetMetaDataSetList())
  {
      addMetaDataAsFieldData(dataSet);
  }

  vtkDataManager* manager = vtkDataManager::New();
  manager->AddMetaDataSet (sequence);

  this->writer->SetFileName(path.toAscii().constData());
  this->writer->SetInput (manager);
  // this->writer->SetFileTypeToBinary();
  this->writer->Update();

  foreach (vtkMetaDataSet* dataSet, sequence->GetMetaDataSetList())
  {
      clearMetaDataFieldData(dataSet);
  }

  manager->Delete();

  return true;
}

void vtkDataMesh4DWriter::addMetaDataAsFieldData(vtkMetaDataSet* dataSet)
{
    foreach (QString key, data()->metaDataList())
    {
        vtkSmartPointer<vtkStringArray> metaDataArray = vtkSmartPointer<vtkStringArray>::New();
        QString arrayName = QString(metaDataFieldPrefix) + key;
        metaDataArray->SetName(arrayName.toStdString().c_str());

        foreach (QString value, data()->metaDataValues(key))
        {
            metaDataArray->InsertNextValue(value.toStdString().c_str());
        }

        dataSet->GetDataSet()->GetFieldData()->AddArray(metaDataArray);
    }
}

void vtkDataMesh4DWriter::clearMetaDataFieldData(vtkMetaDataSet* dataSet)
{
    vtkFieldData* fieldData = dataSet->GetDataSet()->GetFieldData();
    vtkSmartPointer<vtkFieldData> newFieldData = vtkSmartPointer<vtkFieldData>::New();

    for (int i = 0; i < fieldData->GetNumberOfArrays(); i++)
    {
        QString arrayName = fieldData->GetArrayName(i);

        if (!arrayName.startsWith(metaDataFieldPrefix))
        {
            newFieldData->AddArray(fieldData->GetAbstractArray(i));
        }
    }

    dataSet->GetDataSet()->SetFieldData(newFieldData);
}

QString vtkDataMesh4DWriter::description() const
{
    return tr( "VTK 4D Mesh Writer" );
}

QString vtkDataMesh4DWriter::identifier() const
{
    return ID;
}

bool vtkDataMesh4DWriter::registered()
{
    return medAbstractDataFactory::instance()->registerDataWriterType("vtkDataMesh4DWriter", vtkDataMesh4DWriter::s_handled(), createVtkDataMesh4DWriter);
}

QStringList vtkDataMesh4DWriter::supportedFileExtensions() const
{
    return QStringList() << ".xml";
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataWriter *createVtkDataMesh4DWriter()
{
  return new vtkDataMesh4DWriter;
}


