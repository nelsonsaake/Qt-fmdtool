#ifndef DELETESELECTOR_H
#define DELETESELECTOR_H

#include "delselectorlistwidget.h"
#include "selectfolder_df.h"
#include <duplicatefinder/duplicates.h>
#include <vector>
#include <QStringList>

using namespace std;

class DeleteSelector
{
public:
    DeleteSelector();

    void set(const vector<DupSet> &dupSetList, const vector<Folder> &keepFolderList);

    DeleteSelector(const vector<DupSet> &dupSetList, const vector<Folder> &keepFolderList);

    bool isSubFile(QString file, QString folder);

    bool isDelete(QString &file);

    void fillDelList();

    void fillDelListIAT();

    bool isThereAKeepFile(DelDupSet &delDupSet);

    void keepFirstFile(DelDupSet &dupSet);

    void keepAtLeastOne();

    vector<DelDupSet> getDelList();

private:
    vector<DupSet> dupSetList;

    vector<Folder> keepFolderList;

    vector<DelDupSet> delDupSetList;
};

#endif // DELETESELECTOR_H
