#include "VideoPlayerView.h"
#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QGraphicsOpacityEffect>
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
    btnPlay = new ButtonPlay(this);
    labelCurrentTime = new QLabel(this);
    labelTotalTime = new QLabel(this);
}

void VideoPlayerView::InitView()
{
    addMenuAction();
    setupUI();
    m_unit = 1000;
    MainLayout->setSpacing(0);
    MainLayout->setContentsMargins(QMargins());
    sliderPos->setOrientation(Qt::Horizontal);
//    sliderPos->setMinimum(playerView->mediaStartPosition());
//    sliderPos->setMaximum(playerView->mediaStopPosition());
//    sliderPos->setValue(0);
//    sliderPos->setEnabled(playerView->isSeekable());
    QFont font(QString::fromLocal8Bit("微软雅黑"), 8, QFont::Light);
    labelCurrentTime->setFont(font);
    labelCurrentTime->setStyleSheet("color:white;");
    labelCurrentTime->setText(QString::fromLatin1("00:00:00"));
    labelCurrentTime->setContentsMargins(QMargins(1, 1, 1, 1));
    labelTotalTime->setFont(font);
    labelTotalTime->setStyleSheet("color:white;");
    labelTotalTime->setText(QString::fromLatin1("00:00:00"));
    labelTotalTime->setContentsMargins(QMargins(1, 1, 1, 1));

}

void VideoPlayerView::InitEvents()
{

    connect(btnPlay, SIGNAL(clicked()), SLOT(play()));

    connect(sliderPos, SIGNAL(sliderMoved(int)), SLOT(seekBySlider(int)));
    connect(sliderPos, SIGNAL(sliderPressed()), SLOT(seekBySlider()));
    connect(playerView, SIGNAL(positionChanged(qint64)), SLOT(updateSlider(qint64)));
    connect(playerView, SIGNAL(started()), SLOT(updateSlider()));
    connect(playerView, SIGNAL(notifyIntervalChanged()), SLOT(updateSliderUnit()));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openAVFile()));
    connect(closeVideoPlayerViewAction, SIGNAL(triggered()), this, SLOT(eventClose()));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(eventHelp()));
    connect(playerView,SIGNAL(positionChanged(qint64)),this,SLOT(onPositionChange(qint64)));
}
void VideoPlayerView::resizeEvent(QResizeEvent *event)
{
    sliderPos->resize(event->size().width()-150,25);
    sliderPos->move(75,event->size().height()-30);

    btnPlay->resize(25,25);
    btnPlay->move(event->size().width()/2-15,event->size().height()-60);

    labelCurrentTime->resize(50,25);
    labelCurrentTime->move(25,event->size().height()-30);

    labelTotalTime->resize(70,25);
    labelTotalTime->move(event->size().width()-75,event->size().height()-30);
}

void VideoPlayerView::addMenuAction()
{
    mainmenu = new MenuVideoPlayerView();
    openFileAction = new QAction();
    openFileAction->setText("打开文件");
    mainmenu->addAction(openFileAction);
    closeVideoPlayerViewAction = new QAction();
    closeVideoPlayerViewAction->setText("退出");
    mainmenu->addAction(closeVideoPlayerViewAction);
    helpAction = new QAction();
    helpAction->setText("帮助");
    mainmenu->addAction(helpAction);
}

void VideoPlayerView::openAVFile()
{
    QString file = QFileDialog::getOpenFileName(0, "打开所要播放的文件");
    if (file.isEmpty())
        return;
    playerView->play(file);
}

void VideoPlayerView::seekBySlider(int value)
{
    if (!playerView->isPlaying())
        return;
    playerView->seek(qint64(value*m_unit));
    //labelTotalTime->setText(QTime(0, 0, 0).addMSecs(playerView->mediaStopPosition()).toString(QString::fromLatin1("HH:mm:ss")));
}

void VideoPlayerView::seekBySlider()
{
    seekBySlider(sliderPos->value());
}

void VideoPlayerView::play()
{
    if (!playerView->isPlaying()) {
        playerView->play();

        btnPlay->setText("Play");
        return;
    }
    playerView->pause(!playerView->isPaused());
    btnPlay->setText("Pause");
}

void VideoPlayerView::togglebtnPlay()
{
    if(playerView->isPlaying())
    {
        playerView->pause(!playerView->isPaused());
    }else{

    }
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

void VideoPlayerView::onPositionChange(qint64 pos)
{
    if(playerView->isSeekable())
        //sliderPos->setValue(pos);
    labelCurrentTime->setText(QTime(0, 0, 0).addMSecs(pos).toString(QString::fromLatin1("HH:mm:ss")));
}

void VideoPlayerView::paintEvent(QPaintEvent *)
{

}

void VideoPlayerView::contextMenuEvent(QContextMenuEvent *)
{
    mainmenu->exec(QCursor::pos());
}

void VideoPlayerView::eventClose()
{
    qApp->exit();
}

void VideoPlayerView::eventHelp()
{
    qApp->aboutQt();
}
