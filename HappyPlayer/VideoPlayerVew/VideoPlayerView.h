#ifndef VIDEOPLAYERVIEW_H
#define VIDEOPLAYERVIEW_H

#include <QWidget>
#include <QtAV>
#include <VideoPlayerVew/Slider/SliderControlPos.h>
#include <VideoPlayerVew/Menu/MenuVideoPlayerView.h>
#include <QPaintEvent>
QT_BEGIN_NAMESPACE
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

class VideoPlayerView : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayerView(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    void addMenuAction();
public Q_SLOTS:
    void openMedia();
    void seekBySlider(int value);
    void seekBySlider();
    void playPause();
private Q_SLOTS:
    void updateSlider(qint64 value);
    void updateSlider();
    void updateSliderUnit();
private:
    void setupUI();
    void InitView();
    void InitEvents();

    QtAV::VideoOutput *_VideoOutPutMain;
    QtAV::AVPlayer *playerView;
    SliderControlPos *sliderPos;
    QPushButton *btnOpen;
    QPushButton *btnPlay;
    QPushButton *btnStop;
    QVBoxLayout *MainLayout;
    MenuVideoPlayerView *mainmenu;
    int m_unit;
    void paintEvent(QPaintEvent *);
    void contextMenuEvent(QContextMenuEvent *);

public slots:
};

#endif // VIDEOPLAYERVIEW_H
