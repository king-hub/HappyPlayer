#include "SliderControlPos.h"
#include <QFile>
#include <QString>
#include <QLatin1String>
SliderControlPos::SliderControlPos(QWidget *parent) : QSlider(parent)
{
    QString qss;
    QFile qssFile(":/Res/SliderControlSlider.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
    setOrientation(Qt::Horizontal);
    setMouseTracking(true);
}

//void SliderControlPos::enterEvent(QEvent *event)
//{

//}

//void SliderControlPos::leaveEvent(QEvent *event)
//{

//}

//void SliderControlPos::mouseMoveEvent(QMouseEvent *event)
//{

//}

//void SliderControlPos::mousePressEvent(QMouseEvent *event)
//{

//}
