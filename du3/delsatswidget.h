#ifndef DELSATSWIDGET_H
#define DELSATSWIDGET_H

#include <QLabel>
#include <QObject>

class DelStatsWidget
{
public:
    DelStatsWidget(QLabel *label);

    void setClearedSpace(qint64 clearedSpace);

    QString toHTML();

    void displayStats();

public:
    qint64 clearedSpace;

    QLabel *label;

};

#endif // DELSATSWIDGET_H
