#include "MainView.h"
#include <QApplication>
#include <qgraphicseffect.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainView w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setMinimumSize(1024,600);
//    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect;
//    wndShadow->setBlurRadius(9.0);
//    wndShadow->setColor(QColor(0, 0, 0, 160));
//    wndShadow->setOffset(4.0);
//    w.setGraphicsEffect(wndShadow);
    w.show();

    return a.exec();
}
