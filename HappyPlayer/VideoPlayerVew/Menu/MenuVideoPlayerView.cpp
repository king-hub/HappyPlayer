#include "MenuVideoPlayerView.h"
#include <QGraphicsOpacityEffect>
MenuVideoPlayerView::MenuVideoPlayerView(QWidget *parent) : QMenu(parent)
{
    menu = new QMenu();
    QString qss;
    QFile qssFile(":/menu.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
    menu->exec(QCursor::pos());
}

