#ifndef VIDEOPLAYERVIEW_H
#define VIDEOPLAYERVIEW_H

#include <QWidget>
#include <QtAV>
#include <VideoPlayerVew/Slider/SliderControlPos.h>
#include <QPaintEvent>
QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class VideoPlayerView : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayerView(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
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

    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *m_player;
    SliderControlPos *m_slider;
    QPushButton *m_openBtn;
    QPushButton *m_playBtn;
    QPushButton *m_stopBtn;
    int m_unit;
    void paintEvent(QPaintEvent *);

public slots:
};

#endif // VIDEOPLAYERVIEW_H
