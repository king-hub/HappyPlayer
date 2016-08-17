#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

#include "Button/ButtonForStatusBar.h"
#include "QApplication"
#include <QMainWindow>
#include <QMouseEvent>
#include <QEvent>
#include <QPalette>
#ifdef Q_OS_WIN
#include <qt_windows.h>
#endif
#include <QGraphicsEffect>
class ButtonForStatusBar;
class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    void ViewEvent();
private:
    ButtonForStatusBar *btnClose;//关闭按钮
    ButtonForStatusBar *btnMin;//最小化按钮
    ButtonForStatusBar *btnMax;//最大化按钮

};

#endif // TITLEBAR_H
