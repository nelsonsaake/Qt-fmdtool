#ifndef FILEFINDER_H
#define FILEFINDER_H

#include <QtCore>

class FileFinder_fd
{
public:
    FileFinder_fd(QStringList searchareas={});

    QStringList findMusicFiles();

    QStringList lastSearchResult();

    void setSearchareas(QStringList searchareas);

    QStringList findMusicFilesIAT(); // IAT =  In Another Thread

private:
    QStringList fileNameFilters;

    QStringList searchResult;

    QStringList searchareas;
};

#endif // FILEFINDER_H
