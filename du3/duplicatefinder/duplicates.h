#ifndef DUPLICATES_H
#define DUPLICATES_H

#include "dir.h"
#include "fileProperties/fileProperties.h"


struct DupSet
{
    QStringList files;
};

ostream &operator << (ostream &os, DupSet &df);

class DupFinder
{
public:
    DupFinder();
    
    void setScanList(const QStringList &value);
    const vector<DupSet> &getDupsList() const;
    
    void withSamePropts (QStringList propts);
    bool isSame(const FilePropts &a,const FilePropts &b,const QStringList &propts);

    vector<DupSet> findDup_df(QStringList fl);
    vector<DupSet> findDupsIAT_df(QStringList fl); // IAT = In Another Thread

protected:
    void noteDup(int i);
    
    void noteAsDup(QString val);

    void swap(int x, int y);

    QString fileName(int i);

    void fillFileProptsList(QStringList sl);

private:
    vector <FilePropts> fpl; // file properties list
    vector <DupSet> list;

};

ostream &operator << (ostream &os, DupFinder &df);

#endif // DUPLICATES_H
