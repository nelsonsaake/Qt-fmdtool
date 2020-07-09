#ifndef DELETER_H
#define DELETER_H

#include <QString>
#include <QStringList>
#include <windows.h>

using namespace std;

class Deleter
{
public:
    Deleter(QStringList delList);

    QString toQstr(QStringList delList);

    WCHAR *toWCHAR(QString delList);

    void deleteFiles(WCHAR *delList);

    void deleteFiles();

    void deleteIAT(); // IAT = In Another Thread

private:
    QStringList delList;
};

#endif // DELETER_H
