#ifndef PLAYCONTROLVIEW_H
#define PLAYCONTROLVIEW_H

#include <QWidget>
#include <QWidget>
#include <QPalette>
#include <QPainter>
#include <QPaintEvent>
class PlayControlView : public QWidget
{
    Q_OBJECT
public:
    explicit PlayControlView(QWidget *parent = 0);

signals:

public slots:
public:
    void paintEvent(QPaintEvent *);
};

#endif // PLAYCONTROLVIEW_H
