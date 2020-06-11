/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2020. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medPacsSelector.h>

#include <QtGui>
#include <QtWidgets>
#include <QListWidget>


class medToolBoxPacsSelectorPrivate
{
public:
    QListWidget* selectionList;
};

medPacsSelector::medPacsSelector( QWidget *parent /*= 0*/ ): d(new medToolBoxPacsSelectorPrivate)
{
    Q_UNUSED(parent);
    d->selectionList = new QListWidget(this);

    QFormLayout* fLayout = new QFormLayout(this);
    fLayout->addWidget(d->selectionList);

    connect(d->selectionList, SIGNAL(itemClicked(QListWidgetItem* )), this, SLOT(emitSelectionChanged()));

    readSettings();
}

medPacsSelector::~medPacsSelector( void )
{
    delete d;
    d = nullptr;
}

void medPacsSelector::readSettings( void )
{

    QList<QVariant> nodes;

    QSettings settings;

    settings.beginGroup("medBrowserPacsNodesToolBox");
    nodes = settings.value("nodes").toList();
    settings.endGroup();

    fillWidget(nodes);
}

void medPacsSelector::fillWidget( QList<QVariant> nodes )
{
    d->selectionList->clear();
    for(QVariant node : nodes)
    {
        QListWidgetItem* myItem = new QListWidgetItem(node.toStringList().at(0),d->selectionList);
        myItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        myItem->setCheckState(Qt::Checked);
    }
}

void medPacsSelector::updateList()
{
    readSettings();
    emitSelectionChanged();
}

void medPacsSelector::emitSelectionChanged()
{
    QVector<int> list;
    for(int i=0; i<d->selectionList->count() ;i++)
    {
        if (d->selectionList->item(i)->checkState() == Qt::Checked)
            list.push_back(i);
    }
    emit selectionChanged(list);
}
