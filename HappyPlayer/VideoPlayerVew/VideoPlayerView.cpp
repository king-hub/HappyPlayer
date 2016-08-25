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
    InitView();
    InitEvents();
}
void VideoPlayerView::setupUI()
{
    MainLayout = new QVBoxLayout(this);
    setLayout(MainLayout);
    playerView = new AVPlayer(this);
    _VideoOutPutMain = new VideoOutput(this);
    MainLayout->addWidget(_VideoOutPutMain->widget());
    if (!_VideoOutPutMain->widget())
    {
        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    playerView->setRenderer(_VideoOutPutMain);
    sliderPos = new SliderControlPos(this);
    btnOpen = new QPushButton(tr("Open"),this);
    btnPlay = new QPushButton(tr("Play"),this);
    btnStop = new QPushButton(tr("Stop"),this);
}

void VideoPlayerView::InitView()
{
    addMenuAction();
    setupUI();
    m_unit = 1000;
    MainLayout->setSpacing(0);
    MainLayout->setContentsMargins(QMargins());
    sliderPos->setOrientation(Qt::Horizontal);
}

void VideoPlayerView::InitEvents()
{
    connect(btnOpen, SIGNAL(clicked()), SLOT(openMedia()));
    connect(btnPlay, SIGNAL(clicked()), SLOT(playPause()));
    connect(btnStop, SIGNAL(clicked()), playerView, SLOT(stop()));
    connect(sliderPos, SIGNAL(sliderMoved(int)), SLOT(seekBySlider(int)));
    connect(sliderPos, SIGNAL(sliderPressed()), SLOT(seekBySlider()));
    connect(playerView, SIGNAL(positionChanged(qint64)), SLOT(updateSlider(qint64)));
    connect(playerView, SIGNAL(started()), SLOT(updateSlider()));
    connect(playerView, SIGNAL(notifyIntervalChanged()), SLOT(updateSliderUnit()));
}
void VideoPlayerView::resizeEvent(QResizeEvent *event)
{
    sliderPos->resize(event->size().width()-20,20);
    sliderPos->move(10,event->size().height()-30);

    btnOpen->resize(50,20);
    btnOpen->move(event->size().width()/2-25,event->size().height()-50);

    btnPlay->resize(50,20);
    btnPlay->move(10,event->size().height()-50);

    btnStop->resize(50,20);
    btnStop->move(event->size().width()-60,event->size().height()-50);
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
    QAction *a3 = new QAction();
    a3->setText("帮助");
    mainmenu->addAction(a3);
}

void VideoPlayerView::openMedia()
{
    QString file = QFileDialog::getOpenFileName(0, tr("Open a video"));
    if (file.isEmpty())
        return;
    playerView->play(file);
}

void VideoPlayerView::seekBySlider(int value)
{
    if (!playerView->isPlaying())
        return;
    playerView->seek(qint64(value*m_unit));
}

void VideoPlayerView::seekBySlider()
{
    seekBySlider(sliderPos->value());
}

void VideoPlayerView::playPause()
{
    if (!playerView->isPlaying()) {
        playerView->play();
        return;
    }
    playerView->pause(!playerView->isPaused());
}

void VideoPlayerView::updateSlider(qint64 value)
{
    sliderPos->setRange(0, int(playerView->duration()/m_unit));
    sliderPos->setValue(int(value/m_unit));
}

void VideoPlayerView::updateSlider()
{
    updateSlider(playerView->position());
}

void VideoPlayerView::updateSliderUnit()
{
    m_unit = playerView->notifyInterval();
    updateSlider();
}



void VideoPlayerView::paintEvent(QPaintEvent *)
{

}

void VideoPlayerView::contextMenuEvent(QContextMenuEvent *)
{
    mainmenu->exec(QCursor::pos());
}
