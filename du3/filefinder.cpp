#include "filefinder.h"
#include "duplicatefinder/dir.h"
#include <thread>

using namespace std;

FileFinder_fd::FileFinder_fd(QStringList searchareas)
    : searchareas(searchareas)
{}

QStringList FileFinder_fd::findMusicFiles()
{

    fileNameFilters << "*.mp3" << "*.mpeg" << "*.wav" << "*.m4a" << "*.flac";

    for(QString searcharea: searchareas)
    {
        Dir dir(searcharea);

        dir.setFileNameFilters(fileNameFilters);

        searchResult << dir.getSubFiles();
    }

    return searchResult;
}

QStringList FileFinder_fd::lastSearchResult()
{
    return searchResult;
}

void FileFinder_fd::setSearchareas(QStringList searchareas)
{
    this->searchareas=searchareas;

}

QStringList FileFinder_fd::findMusicFilesIAT()
{
    QEventLoop qel;
    bool isFinishSearching = false;

    thread find(
        [&isFinishSearching, &qel, this]{
            findMusicFiles();

            qel.quit();

            isFinishSearching = true;
        }
    );

    if(!isFinishSearching) qel.exec();
    find.join();

    return lastSearchResult();
}
