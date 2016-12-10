#ifndef VIDEOPLAYERVIEW_H
#define VIDEOPLAYERVIEW_H

#include <QWidget>
#include <QApplication>
#include <QtAV>
#include <VideoPlayerVew/Slider/SliderControlPos.h>
#include <VideoPlayerVew/Menu/MenuVideoPlayerView.h>
#include <VideoPlayerVew/Button/ButtonPlay.h>
#include <QPaintEvent>

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <windows.h>
#include <windowsx.h>
#endif

QT_BEGIN_NAMESPACE
class QPushButton;
class QVBoxLayout;
class QAction;
class QLabel;
QT_END_NAMESPACE

class VideoPlayerView : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayerView(QWidget *parent = 0);
public Q_SLOTS:
    void openAVFile();
    void seekBySlider(int value);
    void seekBySlider();
    void play(const QString &name);
    void togglebtnPlay();
    //means toggle button which control play pause

    void eventClose();
    void eventHelp();
private Q_SLOTS:
    void InitPlayer();

    void updateSlider(qint64 value);
    void updateSlider();
    void updateSliderUnit();
    void onPositionChange(qint64 pos);


    void onSeekFinished(qint64);
    void onMediaStatusChanged();
    void onBufferProgress(qreal percent);
    void onStartPlay();
    void onStopPlay();
    void onPaused(bool);
protected:
    void resizeEvent(QResizeEvent *event);
    //custom main layout
    void addMenuAction();
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private:
    void setupUI();
    void InitView();
    void InitEvents();

    QVBoxLayout *MainLayout;
    QtAV::VideoOutput *_VideoOutPutMain;
    QtAV::VideoRenderer *_VideoRender;
    QtAV::AVPlayer *playerView;
    QString mFile;

    SliderControlPos *sliderPos;
    //Control Time Position,from QSlider
    QLabel *labelCurrentTime, *labelTotalTime;
    //Current Time,Total Time,from QLabel
    ButtonPlay *btnPlay;

    MenuVideoPlayerView *mainmenu;
    int m_unit;
    void paintEvent(QPaintEvent *);
    void contextMenuEvent(QContextMenuEvent *);
    QAction *openFileAction;
    QAction *closeVideoPlayerViewAction;
    QAction *helpAction;

public slots:
};

#endif // VIDEOPLAYERVIEW_H
