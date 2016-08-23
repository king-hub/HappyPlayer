#include "VideoPlayerView.h"
#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QDebug>
using namespace QtAV;
VideoPlayerView::VideoPlayerView(QWidget *parent) : QWidget(parent)
{    
    addMenuAction();

    m_unit = 1000;
    setWindowTitle(QString::fromLatin1(""));
    m_player = new AVPlayer(this);
    QVBoxLayout *vl = new QVBoxLayout();
    vl->setSpacing(0);
    vl->setContentsMargins(QMargins());
    setLayout(vl);

    m_vo = new VideoOutput(this);
    if (!m_vo->widget()) {
        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    m_player->setRenderer(m_vo);
    vl->addWidget(m_vo->widget());
    m_slider = new SliderControlPos(this);
    m_slider->setOrientation(Qt::Horizontal);
    connect(m_slider, SIGNAL(sliderMoved(int)), SLOT(seekBySlider(int)));
    connect(m_slider, SIGNAL(sliderPressed()), SLOT(seekBySlider()));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider(qint64)));
    connect(m_player, SIGNAL(started()), SLOT(updateSlider()));
    connect(m_player, SIGNAL(notifyIntervalChanged()), SLOT(updateSliderUnit()));
    QHBoxLayout *hb = new QHBoxLayout(this);
    hb->setSpacing(0);
    hb->setContentsMargins(QMargins());
    m_openBtn = new QPushButton(tr("Open"),this);
    m_playBtn = new QPushButton(tr("Play/Pause"));
    m_stopBtn = new QPushButton(tr("Stop"));
    hb->addWidget(m_playBtn);
    hb->addWidget(m_stopBtn);
    connect(m_openBtn, SIGNAL(clicked()), SLOT(openMedia()));
    connect(m_playBtn, SIGNAL(clicked()), SLOT(playPause()));
    connect(m_stopBtn, SIGNAL(clicked()), m_player, SLOT(stop()));


}

void VideoPlayerView::resizeEvent(QResizeEvent *event)
{
    m_slider->resize(event->size().width()-20,20);
    m_slider->move(10,event->size().height()-30);
    m_openBtn->resize(50,20);
    m_openBtn->move(event->size().width()/2-25,event->size().height()-50);
}

void VideoPlayerView::addMenuAction()
{
    mainmenu = new MenuVideoPlayerView();
    QAction *a1 = new QAction();
    a1->setText("打开文件");
    mainmenu->addAction(a1);
    QAction *a2 = new QAction();
    a2->setText("退出");
    mainmenu->addAction(a2);
}

void VideoPlayerView::openMedia()
{
    QString file = QFileDialog::getOpenFileName(0, tr("Open a video"));
    if (file.isEmpty())
        return;
    m_player->play(file);
}

void VideoPlayerView::seekBySlider(int value)
{
    if (!m_player->isPlaying())
        return;
    m_player->seek(qint64(value*m_unit));
}

void VideoPlayerView::seekBySlider()
{
    seekBySlider(m_slider->value());
}

void VideoPlayerView::playPause()
{
    if (!m_player->isPlaying()) {
        m_player->play();
        return;
    }
    m_player->pause(!m_player->isPaused());
}

void VideoPlayerView::updateSlider(qint64 value)
{
    m_slider->setRange(0, int(m_player->duration()/m_unit));
    m_slider->setValue(int(value/m_unit));
}

void VideoPlayerView::updateSlider()
{
    updateSlider(m_player->position());
}

void VideoPlayerView::updateSliderUnit()
{
    m_unit = m_player->notifyInterval();
    updateSlider();
}

void VideoPlayerView::paintEvent(QPaintEvent *)
{

}

void VideoPlayerView::contextMenuEvent(QContextMenuEvent *)
{
    mainmenu->exec(QCursor::pos());
}
