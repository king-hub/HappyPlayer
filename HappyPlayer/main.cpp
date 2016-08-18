#include "MainView.h"
#include <QApplication>
#include <QtAVWidgets>
int main(int argc, char *argv[])
{
    QtAV::Widgets::registerRenderers();
    QApplication a(argc, argv);
    MainView w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setMinimumSize(1024,600);
    w.show();

    return a.exec();
}
