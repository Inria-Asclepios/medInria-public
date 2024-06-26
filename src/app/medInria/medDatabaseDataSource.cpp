/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2018. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "medDatabaseDataSource.h"

#include <medActionsToolBox.h>
#include <medDatabaseCompactWidget.h>
#include <medDatabaseExporter.h>
#include <medDatabaseModel.h>
#include <medDatabasePreview.h>
#include <medDatabaseProxyModel.h>
#include <medDatabaseSearchPanel.h>
#include <medDatabaseView.h>
#include <medDataManager.h>

class medDatabaseDataSourcePrivate
{
public:
    QPointer<QWidget> mainWidget;
    QPointer<medDatabaseCompactWidget> compactWidget;

    medDatabaseModel *model;
    QPointer<medDatabaseView> largeView;
    medDatabaseView *compactView;

    medDatabasePreview *compactPreview;

    medDatabaseProxyModel *proxy;
    medDatabaseProxyModel *compactProxy;

    QList<medToolBox*> toolBoxes;
    medDatabaseSearchPanel *searchPanel;
    medDatabaseSearchPanel *compactSearchPanel;
    medActionsToolBox* actionsToolBox;
};

medDatabaseDataSource::medDatabaseDataSource( QWidget* parent ): medAbstractDataSource(parent), d(new medDatabaseDataSourcePrivate)
{
    d->model = new medDatabaseModel (this);
    d->proxy = new medDatabaseProxyModel(this);
    d->proxy->setSourceModel(d->model);

    d->compactProxy = new medDatabaseProxyModel(this);
    d->compactProxy->setSourceModel(d->model);
}

medDatabaseDataSource::~medDatabaseDataSource()
{
    qDeleteAll(d->toolBoxes.begin(), d->toolBoxes.end());
    d->toolBoxes.clear();

    delete d->model;

    delete d;
    d = nullptr;
}

QWidget* medDatabaseDataSource::mainViewWidget()
{
    if(d->mainWidget.isNull())
    {
        d->mainWidget = new QWidget;
        d->largeView = new medDatabaseView(d->mainWidget);
        d->largeView->setModel(d->proxy);

        QVBoxLayout *database_layout = new QVBoxLayout(d->mainWidget);
        database_layout->setContentsMargins(0, 0, 0, 0);
        database_layout->setSpacing(0);
        database_layout->addWidget(d->largeView);

        connect(d->largeView, SIGNAL(open(const medDataIndex&)), this, SIGNAL(open(const medDataIndex&)));
        connect(d->largeView, SIGNAL(exportData(const medDataIndex&)), this, SIGNAL(exportData(const medDataIndex&)));
        connect(d->largeView, SIGNAL(dataRemoved(const medDataIndex&)), this, SIGNAL(dataRemoved(const medDataIndex&)));

        if(!d->toolBoxes.isEmpty())
        {
            connect(d->actionsToolBox, SIGNAL(removeClicked()), d->largeView, SLOT(onRemoveSelectedItemRequested()));
            connect(d->actionsToolBox, SIGNAL(exportClicked()), d->largeView, SLOT(onExportSelectedItemRequested()));
            connect(d->actionsToolBox, SIGNAL(viewClicked()), d->largeView, SLOT(onViewSelectedItemRequested()));
            connect(d->actionsToolBox, SIGNAL(saveClicked()), d->largeView, SLOT(onSaveSelectedItemRequested()));
            connect(d->actionsToolBox, SIGNAL(newPatientClicked()), d->largeView, SLOT(onCreatePatientRequested()));
            connect(d->actionsToolBox, SIGNAL(newStudyClicked()), d->largeView, SLOT(onCreateStudyRequested()));
            connect(d->actionsToolBox, SIGNAL(editClicked()), d->largeView, SLOT(onEditRequested()));

            connect(d->largeView, SIGNAL(patientClicked(const medDataIndex&)), d->actionsToolBox, SLOT(patientSelected(const medDataIndex&)));
            connect(d->largeView, SIGNAL(studyClicked(const medDataIndex&)), d->actionsToolBox, SLOT(studySelected(const medDataIndex&)));
            connect(d->largeView, SIGNAL(seriesClicked(const medDataIndex&)), d->actionsToolBox, SLOT(seriesSelected(const medDataIndex&)));
            connect(d->largeView, SIGNAL(noPatientOrSeriesSelected()), d->actionsToolBox, SLOT(noPatientOrSeriesSelected()));
        }

    }

    return d->mainWidget;
}

QWidget* medDatabaseDataSource::compactViewWidget()
{
    if(d->compactWidget.isNull())
    {
        d->compactWidget = new medDatabaseCompactWidget();

        d->compactSearchPanel = new medDatabaseSearchPanel(d->compactWidget);
        d->compactSearchPanel->setColumnNames(d->model->columnNames());
        connect(d->compactSearchPanel, SIGNAL(filter(const QString &, int)),this, SLOT(compactFilter(const QString &, int)),
                Qt::UniqueConnection);

        d->compactView = new medDatabaseView(d->compactWidget);
        d->compactView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        d->compactView->setModel(d->compactProxy);
        d->compactPreview = new medDatabasePreview(d->compactWidget);

        d->compactWidget->setSearchPanelViewAndPreview(d->compactSearchPanel, d->compactView, d->compactPreview);

        for(int i =1; i<12; ++i)
            d->compactView->hideColumn(i);

        connect(d->compactView, SIGNAL(patientClicked(const medDataIndex&)), d->compactPreview, SLOT(showPatientPreview(const medDataIndex&)));
        connect(d->compactView, SIGNAL(studyClicked(const medDataIndex&)), d->compactPreview, SLOT(showStudyPreview(const medDataIndex&)));
        connect(d->compactView, SIGNAL(seriesClicked(const medDataIndex&)), d->compactPreview, SLOT(showSeriesPreview(const medDataIndex&)));

        connect(d->compactPreview, SIGNAL(openRequest(medDataIndex)), d->compactView , SIGNAL(open(medDataIndex)));
        connect(d->compactView, SIGNAL(exportData(const medDataIndex&)), this, SIGNAL(exportData(const medDataIndex&)));
        connect(d->compactView, SIGNAL(dataRemoved(const medDataIndex&)), this, SIGNAL(dataRemoved(const medDataIndex&)));
    }

    return d->compactWidget;
}

QWidget* medDatabaseDataSource::sourceSelectorWidget()
{
    return new QWidget();
}

QString medDatabaseDataSource::tabName()
{
    return tr("Database");
}

QList<medToolBox*> medDatabaseDataSource::getToolBoxes()
{
    if(d->toolBoxes.isEmpty())
    {
        d->actionsToolBox = new medActionsToolBox(0, false);
        d->toolBoxes.push_back(d->actionsToolBox);

        d->searchPanel = new medDatabaseSearchPanel();
        d->searchPanel->setColumnNames(d->model->columnNames());
        d->toolBoxes.push_back(d->searchPanel);

        connect(d->searchPanel, SIGNAL(filter(const QString &, int)),this, SLOT(onFilter(const QString &, int)),
                Qt::UniqueConnection);

        if( !d->largeView.isNull())
        {
            connect(d->actionsToolBox, SIGNAL(removeClicked()), d->largeView, SLOT(onRemoveSelectedItemRequested()));
            connect(d->actionsToolBox, SIGNAL(exportClicked()), d->largeView, SLOT(onExportSelectedItemRequested()));
            connect(d->actionsToolBox, SIGNAL(viewClicked()), d->largeView, SLOT(onViewSelectedItemRequested()));
            connect(d->actionsToolBox, SIGNAL(saveClicked()), d->largeView, SLOT(onSaveSelectedItemRequested()));
            connect(d->actionsToolBox, SIGNAL(newPatientClicked()), d->largeView, SLOT(onCreatePatientRequested()));
            connect(d->actionsToolBox, SIGNAL(newStudyClicked()), d->largeView, SLOT(onCreateStudyRequested()));
            connect(d->actionsToolBox, SIGNAL(editClicked()), d->largeView, SLOT(onEditRequested()));

            connect(d->largeView, SIGNAL(patientClicked(const medDataIndex&)), d->actionsToolBox, SLOT(patientSelected(const medDataIndex&)));
            connect(d->largeView, SIGNAL(studyClicked(const medDataIndex&)), d->actionsToolBox, SLOT(studySelected(const medDataIndex&)));
            connect(d->largeView, SIGNAL(seriesClicked(const medDataIndex&)), d->actionsToolBox, SLOT(seriesSelected(const medDataIndex&)));
            connect(d->largeView, SIGNAL(noPatientOrSeriesSelected()), d->actionsToolBox, SLOT(noPatientOrSeriesSelected()));
        }
    }
    return d->toolBoxes;
}

QString medDatabaseDataSource::description(void) const
{
    return tr("Browse the Database");
}

void medDatabaseDataSource::onFilter( const QString &text, int column )
{
    // adding or overriding filter on column
    d->proxy->setFilterRegExpWithColumn(QRegExp(text, Qt::CaseInsensitive, QRegExp::Wildcard), column);
}

void medDatabaseDataSource::compactFilter( const QString &text, int column )
{
    // adding or overriding filter on column
    d->compactProxy->setFilterRegExpWithColumn(QRegExp(text, Qt::CaseInsensitive, QRegExp::Wildcard), column);
}

void medDatabaseDataSource::onOpeningFailed(const medDataIndex& index, QUuid)
{
    d->largeView->onOpeningFailed(index);
}
