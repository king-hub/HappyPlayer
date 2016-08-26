#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QVBoxLayout>
#include "Button/ButtonForStatusBar.h"
#include "View/TitleBar.h"
#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <View/PlayControlView.h>
#include <VideoPlayerVew/VideoPlayerView.h>
class MainView : public QWidget
{
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();

private:
#ifdef Q_OS_OSX
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseGrabber();
    QPoint _DragPosition;
#endif

#ifdef Q_OS_WIN
    void mousePressEvent(QMouseEvent *event);
#endif
    void mouseDoubleClickEvent(QMouseEvent *);
    void setupUI();
    void InitView();
    void InitEvent();
    void paintEvent(QPaintEvent *);
    QVBoxLayout *layoutMain;
    TitleBar *titleBar;
    VideoPlayerView *viewVideoPlayerView;

};

#endif // MAINVIEW_H
