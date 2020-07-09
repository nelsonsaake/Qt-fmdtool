#include "listheightadjuster_df.h"

ListHeightAdjuster_df::ListHeightAdjuster_df(QListWidget *list)
    : list(list)
{

}

void ListHeightAdjuster_df::adjustList()
{
    if (list==nullptr) return;

    resizeListRows();
}

void ListHeightAdjuster_df::resizeListRows()
{
    if (list==nullptr) return;

    const int rows = list->count();

    list->setFixedHeight((43.2)*rows);
}
