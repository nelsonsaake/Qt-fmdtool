#include "deleteselector.h"

DeleteSelector::DeleteSelector(){}

void DeleteSelector::set(const vector<DupSet> &dupSetList, const vector<Folder> &keepFolderList)
{
    this->dupSetList = dupSetList;
    this->keepFolderList = keepFolderList;
}

DeleteSelector::DeleteSelector(const vector<DupSet> &dupSetList, const vector<Folder> &keepFolderList) : dupSetList(dupSetList), keepFolderList(keepFolderList)
{}

bool DeleteSelector::isSubFile(QString file, QString folder)
{
    return file.contains(folder);
}

bool DeleteSelector::isDelete(QString &file)
{
    //

    for(Folder &kf: keepFolderList){

        if(!kf.keep) continue;

        // if the file is a subfile of a keep folder
        // don't delete
        if(isSubFile(file, kf.name)) return false;
    }

    return true;
}

void DeleteSelector::fillDelList()
{
    for(DupSet dupset: dupSetList){

        DelDupSet dds;
        for(QString file: dupset.files){
            DelFile df;
            df.name = file;
            df.isDelete = isDelete(file);
            dds.vdf.push_back(df);
        }

        delDupSetList.push_back(dds);
    }
}

void DeleteSelector::fillDelListIAT()
{
    QEventLoop qel;
    bool isFinished = false;

    std::thread t(
        [&isFinished, &qel, this]{
            fillDelList();

            qel.quit();

            isFinished = true;
        }
    );

    if(!isFinished) qel.exec();
    t.join();
}

bool DeleteSelector::isThereAKeepFile(DelDupSet &delDupSet)
{
    for(DelFile &delfile: delDupSet.vdf){
        if(!delfile.isDelete) return true;
    }

    return false;
}

void DeleteSelector::keepFirstFile(DelDupSet &dupSet)
{
    // look carefully before you touch anything

    for(DelFile &delfile: dupSet.vdf){
        delfile.isDelete = false;
        return; // must be here
    }
    return;
}

void DeleteSelector::keepAtLeastOne()
{
    for(DelDupSet &dupSet: delDupSetList){
        if(isThereAKeepFile(dupSet)) continue;
        keepFirstFile(dupSet);
    }
}

vector<DelDupSet> DeleteSelector::getDelList()
{
    fillDelListIAT();
    keepAtLeastOne();
    return delDupSetList;
}
