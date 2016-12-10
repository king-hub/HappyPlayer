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
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *);
    void setupUI();
    void InitView();
    void InitEvent();
    void paintEvent(QPaintEvent *);
    QVBoxLayout *layoutMain;
    TitleBar *titleBar;
    VideoPlayerView *viewVideoPlayerView;
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};

#endif // MAINVIEW_H
