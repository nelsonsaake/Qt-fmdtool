#include "gifplayer.h"

GifPlayer::GifPlayer(QString file, QLabel *gifWrapper_arg)
    : gifWrapper(gifWrapper_arg)
{
    gif = new QMovie(file);

    gifWrapper->setMovie(gif);

    int someRandomNumber = 300;
    gif->setScaledSize(QSize(someRandomNumber * 1.5,someRandomNumber));
}

void GifPlayer::start()
{
    if(gifWrapper==nullptr) return;

    if(gif==nullptr) return;

    gif->start();
}

void GifPlayer::stop()
{
    if(gif->state()==QMovie::MovieState::Running) gif->stop();
}
