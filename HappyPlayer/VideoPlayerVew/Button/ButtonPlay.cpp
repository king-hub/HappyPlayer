#include "ButtonPlay.h"

ButtonPlay::ButtonPlay(QWidget *parent) : QPushButton(parent)
{
    status = NORMAL;
    _ifPress = false;
    this->setFlat(true);
}

void ButtonPlay::setPlayState(bool ifPlay)
{
    _ifPlay = ifPlay;
}

void ButtonPlay::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _ifPress = true;
        status = PRESS;
        update();
    }
}

void ButtonPlay::mouseReleaseEvent(QMouseEvent *event)
{
    if(_ifPress  && this->rect().contains(event->pos()))
        {
            _ifPress = false;
            status = ENTER;
            update();
            emit clicked();
        }
}

void ButtonPlay::enterEvent(QEvent *)
{
    status = ENTER;
    update();
}

void ButtonPlay::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}

void ButtonPlay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(_ifPlay == false){
    switch (status)
    {
    case NORMAL:
        pixmap.load(":/Res/PlayNormal.png");
        break;
    case ENTER:
        pixmap.load(":/Res/PlayPress.png");
        break;
    case PRESS:
        pixmap.load(":/Res/PlayPress.png");
        break;
    case NOSTATUS:
        pixmap.load(":/Res/PlayPress.png");
        break;
    default:
        pixmap.load(":/Res/PlayNormal.png");
        break;
    }
    }
    else if(_ifPlay == true)
    {
        switch (status)
        {
        case NORMAL:
            pixmap.load(":/Res/PauseNormal.png");
            break;
        case ENTER:
            pixmap.load(":/Res/pausePress.png");
            break;
        case PRESS:
            pixmap.load(":/Res/pausePress.png");
            break;
        case NOSTATUS:
            pixmap.load(":/Res/pausePress.png");
            break;
        default:
            pixmap.load(":/Res/PauseNormal.png");
            break;
        }
    }
    Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio;
    pixmap.scaled(25,25,aspectRatioMode);
    painter.drawPixmap(0,0,25,25,pixmap);
}
