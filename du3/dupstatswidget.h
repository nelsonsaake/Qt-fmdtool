#ifndef DUPSETLISTSTATS_H
#define DUPSETLISTSTATS_H

#include "delselectorlistwidget.h"
#include <duplicatefinder/duplicates.h>


class DupStatsWidget : public QObject
{
    Q_OBJECT

public:
    DupStatsWidget(QLabel *label);

    void set(vector<DelWidget *> *value);

    int filesCount();

    int selectedFilesCount();

    int unselectedFilesCount();

    qint64 freeableSpace();

    QString toHTML();

    void displayStats();

protected slots:
    void refresh(vector<DelWidget *> *dupWidgets);

private:
    vector<DelWidget *> *dupWidgets;

    QLabel *label;
};

#endif // DUPSETLISTSTATS_H
