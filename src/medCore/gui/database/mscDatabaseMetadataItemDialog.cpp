/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "mscDatabaseMetadataItemDialog.h"

#include <medAbstractDatabaseItem.h>
#include <medDataIndex.h>

#include <QtGui>
#include <QVariant>

class mscDatabaseMetadataItemDialogPrivate
{
public:
    QTreeWidget* tree;
};


mscDatabaseMetadataItemDialog::mscDatabaseMetadataItemDialog(QList<QString> keyList, QList<QVariant> metadataList, QWidget *parent):
    QDialog(parent, Qt::Dialog | Qt::WindowCloseButtonHint), d (new mscDatabaseMetadataItemDialogPrivate)

{
    QVBoxLayout *dialogLayout = new QVBoxLayout;
    setLayout(dialogLayout);
    setModal(true);

    d->tree = new QTreeWidget();
    d->tree->setFrameStyle(QFrame::NoFrame);
    d->tree->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->tree->setUniformRowHeights(true);
    d->tree->setAlternatingRowColors(true);
    d->tree->setAnimated(true);
    d->tree->setSortingEnabled(true);
    d->tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    d->tree->setSelectionMode(QAbstractItemView::SingleSelection);
    d->tree->header()->setStretchLastSection(true);
    d->tree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    d->tree->setColumnCount(2);

    // Create tree columns
    QStringList treeColumns;
    treeColumns << tr("Key") << tr("Value");
    d->tree->setHeaderLabels(treeColumns);
    d->tree->setColumnWidth(0, 200);
    d->tree->setColumnWidth(1, 400);
    dialogLayout->addWidget(d->tree);
    this->resize(700, 700);

    // Populate the tree
    int cpt = 0;
    foreach (QString key, keyList)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(d->tree);
        item->setText(0, key);
        item->setText(1, metadataList.at(cpt).toString());
        d->tree->addTopLevelItem(item);
        cpt++;
    }
}

mscDatabaseMetadataItemDialog::~mscDatabaseMetadataItemDialog()
{
    delete d;
}
