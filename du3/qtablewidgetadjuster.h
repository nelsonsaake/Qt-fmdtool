#ifndef QTABLEWIDGETADJUSTER_H
#define QTABLEWIDGETADJUSTER_H

#include <QTableWidget>

class QTableWidgetAdjuster
{
public:
    QTableWidgetAdjuster(QTableWidget *table);

    void resizeTableRows();

    void hideTableHeaders();

    void removeTableGrid();

    void adjustTableau();

private:
    QTableWidget *table;
};

#endif // QTABLEWIDGETADJUSTER_H
