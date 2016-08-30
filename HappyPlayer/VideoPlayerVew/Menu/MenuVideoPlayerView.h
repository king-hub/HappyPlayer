#ifndef MENUVIDEOPLAYERVIEW_H
#define MENUVIDEOPLAYERVIEW_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QLatin1String>
#include <QAction>
#include <QMenu>

class MenuVideoPlayerView : public QMenu
{
    Q_OBJECT
public:
    explicit MenuVideoPlayerView(QWidget *parent = 0);
    QMenu *menu;
signals:

public slots:
};

#endif // MENUVIDEOPLAYERVIEW_H
