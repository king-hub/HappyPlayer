#include "ButtonForStatusBar.h"

ButtonForStatusBar::ButtonForStatusBar(QWidget *parent) : QPushButton(parent)
{
    status = NORMAL;
    _ifPress = false;
    this->setFlat(true);
}

void ButtonForStatusBar::setType(QString gettype)
{
    type = gettype;
}

void ButtonForStatusBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _ifPress = true;
        status = PRESS;
        update();
    }
}
void ButtonForStatusBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(_ifPress  && this->rect().contains(event->pos()))
        {
            _ifPress = false;
            status = ENTER;
            update();
            emit clicked();
        }
}

void ButtonForStatusBar::enterEvent(QEvent *)
{
    status = ENTER;
    update();
}

void ButtonForStatusBar::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}
void ButtonForStatusBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(type == "Close")
    {
    switch (status)
    {
    case NORMAL:
        pixmap.load(":/Res/buttonCloseNORMAL.png");
        break;
    case ENTER:
        pixmap.load(":/Res/buttonCloseENTER.png");
        break;
    case PRESS:
        pixmap.load(":/Res/buttonClosePRESS.png");
        break;
    case NOSTATUS:
        pixmap.load(":/Res/buttonCloseENTER.png");
        break;
    default:
        pixmap.load(":/Res/buttonCloseNORMAL.png");
        break;
    }
    }else if(type == "Min")
    {
    switch (status)
    {
    case NORMAL:
         pixmap.load(":/Res/buttonMinNOMAL.png");
         break;
    case ENTER:
         pixmap.load(":/Res/buttonMinENTER.png");
         break;
    case PRESS:
         pixmap.load(":/Res/buttonMinPRESS.png");
         break;
    case NOSTATUS:
         pixmap.load(":/Res/buttonMinENTER.png");
         break;
    default:
         pixmap.load(":/Res/buttonMinNOMAL.png");
     break;
        }
    }else if(type == "Max")
    {
        pixmap = QPixmap(":/Res/buttonMax.png");
    }
    painter.drawPixmap(0,0,15,15,pixmap);
}
