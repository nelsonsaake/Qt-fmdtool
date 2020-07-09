#include "deleter.h"

#include <duplicatefinder/duplicates.h>

Deleter::Deleter(QStringList delList)
    : delList(delList)
{

}

QString Deleter::toQstr(QStringList delList)
{
    QString delListStr;

    for(QString file : delList)
    {
        delListStr += file;

        if(delListStr[delListStr.size()-1]!='\0') delListStr+='\0';
    }

    return delListStr;
}

WCHAR *Deleter::toWCHAR(QString delList)
{
    WCHAR* from = new WCHAR [ delList.size() + 2 ];
    delList.toWCharArray(from);
    from[delList.size()]='\0';

    return from;
}

void Deleter::deleteFiles(WCHAR *delList)
{
    SHFILEOPSTRUCT fileop;
    memset(&fileop, 0, sizeof(fileop));
    fileop.wFunc = FO_DELETE;
    fileop.pFrom = delList;
    fileop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;

    SHFileOperationW( &fileop );
}

void Deleter::deleteFiles()
{
    QString delStr = toQstr(delList);

    WCHAR *delwchar = toWCHAR(delStr);

    deleteFiles(delwchar);
}

void Deleter::deleteIAT()
{
    QEventLoop qel;
    bool isFinished = false;

    std::thread t(
        [&isFinished, &qel, this]{
            deleteFiles();

            qel.quit();

            isFinished = true;
        }
    );

    if(!isFinished) qel.exec();
    t.join();
}
