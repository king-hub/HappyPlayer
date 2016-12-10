#include "MainView.h"
#include <QApplication>
#include <QtAVWidgets>
int main(int argc, char *argv[])
{
    QtAV::Widgets::registerRenderers();
    QApplication a(argc, argv);
    MainView w;
    w.setMinimumSize(1024,600);
    w.show();

    return a.exec();
}
