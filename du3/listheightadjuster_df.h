#ifndef LISTHEIGHTADUSTER_DF_H
#define LISTHEIGHTADUSTER_DF_H

#include <QListWidget>
#include <QtCore>

class ListHeightAdjuster_df
{
public:
    ListHeightAdjuster_df(QListWidget *list);
    
    void adjustList();
    
    void resizeListRows();
    
private:
    QListWidget *list;
};

#endif // LISTHEIGHTADUSTER_DF_H
