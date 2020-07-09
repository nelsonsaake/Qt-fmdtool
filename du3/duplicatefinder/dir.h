//------------------------------------------------------------------------------------------
#ifndef DIR_H
#define DIR_H

//------------------------------------------------------------------------------------------
#include <QDir>
#include "globals.h"

using namespace  std; 

//------------------------------------------------------------------------------------------
// we would have four filters
// fileNameFilters
// fileFilters

// dirNameFilters
// dirFilters

// for a read operation
// we will need to read directory enteries twice

// we only read the files whose fileName that pass for the fileNameFilters
// and types pass for filters set except for QDir::Dirs

// the sub directories that will be read will depend on filters and nameFilters only

class Dir : public  QDir, public QObject
{
public:
    Dir(QString name = "c:/");

    QStringList getAllFiles ();
    QStringList getFiles();
    QStringList getSubFiles ();

    // getters and setters
    QStringList getFileNameFilters() const;
    void setFileNameFilters(const QStringList &value);

    QDir::Filters getFileFilters() const;
    void setFileFilters(const QDir::Filters &value);

    QStringList getDirNameFilters() const;
    void setDirNameFilters(const QStringList &value);

    QDir::Filters getDirFilters() const;
    void setDirFilters(const QDir::Filters &value);
    
private:
    QStringList fnf;    // file name filter
    QDir::Filters ff;   // file type filter

    QStringList dnf;    // directory name filter
    QDir::Filters df;   // directory type filter
 };

//------------------------------------------------------------------------------------------
#endif // DIR_H

//------------------------------------------------------------------------------------------
