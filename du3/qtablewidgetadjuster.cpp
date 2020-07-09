#include "qtablewidgetadjuster.h"

#include <QHeaderView>

QTableWidgetAdjuster::QTableWidgetAdjuster(QTableWidget *table)
    : table(table)
{

}

void QTableWidgetAdjuster::resizeTableRows()
{
    if (table==nullptr) return;

    const int rowHeight = 43;

    for(int i=0; i<table->rowCount(); i++){
        table->setRowHeight(i,rowHeight);
    }

    table->setColumnWidth(1, 250); // ? filepripts dialog customized
    table->adjustSize();
}

void QTableWidgetAdjuster::hideTableHeaders()
{
    if (table==nullptr) return;

    QHeaderView *horizontalHeader = table->horizontalHeader();
    horizontalHeader = const_cast<QHeaderView*>(horizontalHeader);
    horizontalHeader->setVisible(false);

    QHeaderView *verticalHorizontal = table->verticalHeader();
    const_cast<QHeaderView*>(verticalHorizontal)->setVisible(false);
}

void QTableWidgetAdjuster::removeTableGrid()
{
    if (table==nullptr) return;

    table->setShowGrid(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void QTableWidgetAdjuster::adjustTableau()
{
    if (table==nullptr) return;

    table->adjustSize();
    resizeTableRows();
    hideTableHeaders();
    removeTableGrid();
}
