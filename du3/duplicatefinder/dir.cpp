#include "dir.h"

Dir::Dir(QString name)
    : fnf ({"*"}), dnf({"*"})
{
    setPath(name);
    setFilter(QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    setDirNameFilters({"*"});
    setDirFilters(QDir::Dirs|QDir::NoDotAndDotDot|QDir::NoSymLinks);

    setFileFilters(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::NoFilter);

}

//
QStringList Dir::getAllFiles()
{
    // returns all files using the filters

    QStringList files;
    for(QFileInfo drive : drives())
    {
        Dir dir (drive.filePath());
        dir.setFileNameFilters(fnf);
        dir.setFileFilters(ff);
        dir.setDirNameFilters(dnf);
        dir.setDirFilters(df);

        files << dir.getSubFiles();
    }
    return files;
}

QStringList Dir::getFiles ()
{
    // returns files of this directory using the filters
    QStringList sl;

    setFilter(ff); // set filters neccessary for reading files
    if(!fnf.isEmpty()) setNameFilters(fnf);

    for(QFileInfo fn: entryInfoList()) // for each set of info
    {
        sl << fn.filePath(); // store only the file path
    }

    return sl;
}

QStringList Dir::getSubFiles()
{
    // returns the files current directory files and sub-directory files

    if(!exists())
        error("Dir does not exist.  Dir::getFiles().");

    if(path().isEmpty())
        error("Dir name not specified.  Dir::getFiles().");

    QStringList sl {getFiles()};

    // we need to get sub dirs files
    setFilter(df);  // set the filters required for reading directories
    if(!dnf.isEmpty()) setNameFilters(dnf); //

    for(QFileInfo fn: entryInfoList())
    {
        if(!fn.isDir()) continue; // just incase the filters set includes files

        Dir subDir(fn.filePath()); //

        // we pass the parents filters to the sub directory
        subDir.setDirFilters(df);
        subDir.setDirNameFilters(dnf);
        subDir.setFileFilters(ff);
        subDir.setFileNameFilters(fnf);

        sl << subDir.getSubFiles(); // get the files
    }

    return sl;
}




QStringList Dir::getFileNameFilters() const
{
    return fnf;
}

void Dir::setFileNameFilters(const QStringList &value)
{
    fnf = value;
}



QDir::Filters Dir::getFileFilters() const
{
    return ff;
}

void Dir::setFileFilters(const QDir::Filters &value)
{
    ff = value;
}



QStringList Dir::getDirNameFilters() const
{
    return dnf;
}

void Dir::setDirNameFilters(const QStringList &value)
{
    dnf = value;
}



QDir::Filters Dir::getDirFilters() const
{
    return df;
}

void Dir::setDirFilters(const QDir::Filters &value)
{
    df = value;
}





