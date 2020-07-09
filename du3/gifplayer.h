#ifndef GIFPLAYER_H
#define GIFPLAYER_H

#include <QLabel>
#include <QMovie>
#include <QtCore>

class GifPlayer
{
public:
    GifPlayer(QString file, QLabel *gifWrapper);
    
    void start();
    void stop();
    
private:
    QLabel *gifWrapper;
    QMovie *gif;
};

#endif // GIFPLAYER_H
