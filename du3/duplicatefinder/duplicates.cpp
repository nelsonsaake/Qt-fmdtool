#include "duplicates.h"


//
struct ReducedFilePropts 
{
    QString fileName; 
    QStringList proptList; 
}; 

bool operator ==(const ReducedFilePropts &a, const ReducedFilePropts &b)
{
    if(a.proptList.size()!=b.proptList.size()) return false;
    if(a.proptList.isEmpty()) return false;
    
    for(int i=0; i<a.proptList.size(); i++)
    {
        if(a.proptList[i].toLower()!=b.proptList[i].toLower())
            return false;
    }
    return true;
}

bool operator !=(const ReducedFilePropts &a, const ReducedFilePropts &b)
{
    return !(a==b);
}


struct ReducedFileProptsList 
{
    void fill(const vector<FilePropts> &fpl, QStringList propts);
    
    ReducedFilePropts &get(unsigned int i);
    
    void swap(int x, int y);
    
    ReducedFileProptsList(){}
    
    vector<ReducedFilePropts> list;
};

//?
void ReducedFileProptsList::fill(const vector<FilePropts> &fpl, QStringList propts)
{
    list.clear();
    
    for(const FilePropts &fp: fpl)
    {
        ReducedFilePropts rfp;
        rfp.fileName=qstr(fp.fileName);
        
        try{
            for(const QString &propt: propts)  
            {
                QString tp=fp.get(propt);
                if(tp.isEmpty()) error("");                               // doesnot have a property
                if(tp.contains("unknown",Qt::CaseInsensitive)) error(""); // invalid
                rfp.proptList.push_back(tp);                              // add property to list
                QCoreApplication::sendPostedEvents();
            }
            list.push_back(rfp);
        }catch(...){} 
    }
}

ReducedFilePropts &ReducedFileProptsList::get(unsigned int i)
{
    if(i<0 || list.size()-1<i) error("out of range access");
    return list[i];
}

void ReducedFileProptsList::swap(int x, int y)
{
    std::swap(get(x),get(y)); // swap in the search property list
}


//
FilePropts getPropts (const string &fn)
{
    return getFilePropts(fn);
}

DupFinder::DupFinder(){}


void DupFinder::setScanList(const QStringList &value)
{
    fillFileProptsList(value);
}

const vector<DupSet> &DupFinder::getDupsList() const
{
    return list;
}


void DupFinder::withSamePropts(QStringList propts)
{
    /*
    makes a list of duplicates files
    
    what is a duplicate file, here :
    for a pair of file property set belonging to two different files, a, b,
    for each property in propts
    if a and b has that property to be equal,
    a and b are duplicates
*/
    
    list.clear(); // make sure the list empty before we start
    
    ReducedFileProptsList rfpl;
    rfpl.fill(fpl,propts);
    
    for(unsigned int i1 = 0;  i1 < rfpl.list.size(); i1++)
    {
        for(unsigned int i2 = i1; i2 < rfpl.list.size(); i2++)
        {
            if(i1 == i2) continue;                                                                                                       // same index => same file
            if(rfpl.get(i1)==rfpl.get(i2))        // if duplicates
            {
                noteAsDup(rfpl.get(i2).fileName); // record file name of duplicate
                // if(note) note("dup:"+rfpl.get(i2).fileName);
                
                rfpl.swap(i1+1,i2); // move l2 right infront of the i1
                rfpl.swap(i1,i1+1); // move it behind i1
                i1++;
            }
        }
        if(list.empty()) continue;
        if(list[list.size()-1].files.size()>0)
        {
            noteAsDup(rfpl.get(i1).fileName); // record file name of duplicate
            list.push_back({}); // for the next duplicate set
        }
    }
    
    if(list.empty()) return;
    if(list[list.size()-1].files.size()==0)
    {
        // remove the last item from the list if it is empty
        list.erase(list.begin()+list.size()-1);
    }
}

bool DupFinder::isSame(const FilePropts &a, const FilePropts &b, const QStringList &propts)
{
    /*
       false, if a file lacks a property specified
       false, if the a or b does not contain the properties specified
       false, if the same properties specified for a and b are not equal
       else, true
    */
    
    for(const QString &propt : propts)
    {
        try{if(a.get(propt).toLower()!=b.get(propt).toLower()) return false;}
        catch(...){return false;}// the get function well throw an error
        // if the propt is not found
    }
    return true;
}


//
vector<DupSet> DupFinder::findDup_df(QStringList fl)
{
    setScanList(fl);
    
    QStringList pl;
    pl<<"artist"<<"album"<<"title";
    withSamePropts(pl);
    
    return getDupsList();
}

vector<DupSet> DupFinder::findDupsIAT_df(QStringList fl)
{
    QEventLoop qel;
    bool isFinished = false;
    vector<DupSet> dups;
    
    std::thread t(
                [&isFinished, &qel, this, &fl, &dups]{
        
        dups = findDup_df(fl);
        
        qel.quit();
        
        isFinished = true;
    }
    );
    
    if(!isFinished) qel.exec();
    t.join();
    
    return dups;
}


//
void DupFinder::noteDup(int i)
{
    // add the file name from the property set to duplicates list
    // to the last set of duplicates
    
    if(list.empty()) list.push_back(DupSet{});
    list[list.size()-1].files.push_back(fileName(i));
}

void DupFinder::noteAsDup(QString val)
{
    if(list.empty()) list.push_back(DupSet{});
    list[list.size()-1].files.push_back(val);
}

void DupFinder::swap(int x, int y)
{
    std::swap(fpl[x],fpl[y]); // swap in the search property list
}

QString DupFinder::fileName(int i)
{
    return qstr(fpl[i].fileName);
}


bool hasPropts(const FilePropts &fp, QStringList propts)
{
    /*
       false, if file lacks a property specified
       false, if 
       else, true
    */
    
    for(const QString &propt : propts)  
    {
        try{if(fp.get(propt).isEmpty()) return false;}
        catch(...){return false;} // the get function well throw an error
        // if the property is not found
    }
    return true;
}

void DupFinder::fillFileProptsList(QStringList sl)
{
    // clear fpl
    // use the search list to fill the fill proptery list
    
    fpl.clear();
    for(const QString &fn: sl) // get file propts using fn
    {
        FilePropts fp=getPropts(str(fn));
        fpl.push_back(fp); // into fpl
    }
}


ostream &operator <<(ostream &os,const DupSet &df)
{
    for(const QString &x : df.files)
        os << x << "\n";
    return os;
}

ostream &operator <<(ostream &os, DupFinder &d)
{
    for(const DupSet &x : d.getDupsList())
        os << x << "\n\n";
    return os;
}













// needs editing

