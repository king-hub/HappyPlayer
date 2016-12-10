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
#include <QTimer>
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
    InitPlayer();
    sliderPos = new SliderControlPos(this);
    btnPlay = new ButtonPlay(this);
    btnPlay->setPlayState(false);
    connect(btnPlay,SIGNAL(clicked()),SLOT(togglebtnPlay()));
    labelCurrentTime = new QLabel(this);
    labelTotalTime = new QLabel(this);
}
void VideoPlayerView::InitPlayer()
{
    playerView = new AVPlayer(this);
    _VideoOutPutMain = new VideoOutput(this);
    MainLayout->addWidget(_VideoOutPutMain->widget());
    if (!_VideoOutPutMain->widget())
    {
        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    playerView->setRenderer(_VideoOutPutMain);

    connect(playerView, SIGNAL(seekFinished(qint64)), SLOT(onSeekFinished(qint64)));
    connect(playerView, SIGNAL(mediaStatusChanged(QtAV::MediaStatus)), SLOT(onMediaStatusChanged()));
    connect(playerView, SIGNAL(bufferProgressChanged(qreal)), SLOT(onBufferProgress(qreal)));
    connect(playerView, SIGNAL(error(QtAV::AVError)), this, SLOT(handleError(QtAV::AVError)));
    connect(playerView, SIGNAL(started()), this, SLOT(onStartPlay()));
    connect(playerView, SIGNAL(stopped()), this, SLOT(onStopPlay()));
    connect(playerView, SIGNAL(paused(bool)), this, SLOT(onPaused(bool)));
    //connect(playerView, SIGNAL(speedChanged(qreal)), this, SLOT(onSpeedChange(qreal)));
    connect(playerView, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChange(qint64)));
}
void VideoPlayerView::InitView()
{
    addMenuAction();
    setupUI();
    m_unit = 1000;
    MainLayout->setSpacing(0);
    MainLayout->setContentsMargins(QMargins());
    sliderPos->setOrientation(Qt::Horizontal);
    QFont font(QString::fromLocal8Bit("微软雅黑"), 8, QFont::Light);
    labelCurrentTime->setFont(font);
    labelCurrentTime->setStyleSheet("color:white;");
    labelCurrentTime->setText(QString::fromLatin1("00:00:00"));
    labelCurrentTime->setContentsMargins(QMargins(1, 1, 1, 1));
    labelTotalTime->setFont(font);
    labelTotalTime->setStyleSheet("color:white;");
    labelTotalTime->setText(QString::fromLatin1("00:00:00"));
    labelTotalTime->setContentsMargins(QMargins(1, 1, 1, 1));   
    QTimer::singleShot(0, this, SLOT(initPlayer()));
}

void VideoPlayerView::InitEvents()
{
//    connect(sliderPos, SIGNAL(sliderMoved(int)), SLOT(seekBySlider(int)));
//    connect(sliderPos, SIGNAL(sliderPressed()), SLOT(seekBySlider()));
//    connect(playerView, SIGNAL(positionChanged(qint64)), SLOT(updateSlider(qint64)));
//    connect(playerView, SIGNAL(started()), SLOT(updateSlider()));
//    connect(playerView, SIGNAL(notifyIntervalChanged()), SLOT(updateSliderUnit()));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openAVFile()));
    connect(closeVideoPlayerViewAction, SIGNAL(triggered()), this, SLOT(eventClose()));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(eventHelp()));
//    connect(playerView,SIGNAL(positionChanged(qint64)),this,SLOT(onPositionChange(qint64)));
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

void VideoPlayerView::play(const QString &name)
{
    mFile = name;
    playerView->stop();
    if (!playerView->isPlaying()) {
        playerView->play();

        btnPlay->setText("Play");
        return;
    }
    playerView->pause(!playerView->isPaused());
    btnPlay->setPlayState(true);
}

void VideoPlayerView::togglebtnPlay()
{
    if (playerView->isPlaying()) {
            qDebug("isPaused = %d", playerView->isPaused());
            playerView->pause(!playerView->isPaused());
        } else {
            if (mFile.isEmpty())
                return;
            if (!playerView->isPlaying())
                play(mFile);
            else
                playerView->play();
            btnPlay->setPlayState(true);
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

void VideoPlayerView::onSeekFinished(qint64 pos)
{
    qDebug("seek finished at %lld/%lld", pos, playerView->position());
}

void VideoPlayerView::onMediaStatusChanged()
{
    QString status;
    AVPlayer *player = reinterpret_cast<AVPlayer*>(sender());
    if (!player) { //why it happens? reinterpret_cast  works.
        qWarning() << "invalid sender() " << sender() << player;
        return;
    }
    switch (player->mediaStatus()) {
    case NoMedia:
        status = tr("No media");
        break;
    case InvalidMedia:
        status = tr("Invalid meida");
        break;
    case BufferingMedia:
        status = tr("Buffering...");
        break;
    case BufferedMedia:
        status = tr("Buffered");
        break;
    case LoadingMedia:
        status = tr("Loading...");
        break;
    case LoadedMedia:
        status = tr("Loaded");
        break;
    case StalledMedia:
        status = tr("Stalled");
        break;
    default:
        status = QString();
        onStopPlay();
        break;
    }
    qDebug() << "status changed " << status;
}

void VideoPlayerView::onBufferProgress(qreal percent)
{
    const qreal bs = playerView->bufferSpeed();
    QString s;
    if (bs > 1024*1024*1024)
        s = QString("%1G/s").arg(bs/1024.0/1024.0/1024.0, 6, 'f', 1);
    else if (bs > 1024*1024)
        s = QString("%1M/s").arg(bs/1024.0/1024.0, 6, 'f', 1);
    else if (bs > 1024)
        s = QString("%1K/s").arg(bs/1024.0, 6, 'f', 1);
    else
        s = QString("%1B/s").arg(bs, 6, 'f', 1);
    //setWindowTitle(QString::fromLatin1("Buffering... %1% @%2 ").arg(percent*100.0, 5, 'f', 1).arg(s) + mTitle);
}
void VideoPlayerView::onStartPlay()
{
    _VideoRender->setRegionOfInterest(QRectF());
    mFile = playerView->file(); //open from EventFilter's menu
    //mTitle = mFile;
    btnPlay->setPlayState(true);
    sliderPos->setMinimum(playerView->mediaStartPosition());
    sliderPos->setMaximum(playerView->mediaStopPosition());
    sliderPos->setValue(0);
    sliderPos->setEnabled(playerView->isSeekable());
    labelTotalTime->setText(QTime(0, 0, 0).addMSecs(playerView->mediaStopPosition()).toString(QString::fromLatin1("HH:mm:ss")));
    //setVolume();
    //mShowControl = 0;
    //QTimer::singleShot(3000, this, SLOT(tryHideControlBar()));
    //ScreenSaver::instance().disable();
    //initAudioTrackMenu();
    /*mCursorTimer = startTimer(3000);
    if (mpStatisticsView && mpStatisticsView->isVisible())
        mpStati sticsView->setStatistics(mpPlayer->statistics())*/;
}

void VideoPlayerView::onStopPlay()
{
//    playerView->setPriority(idsFromNames(Config::instance().decoderPriorityNames()));
//    if (mpPlayer->currentRepeat() >= 0 && mpPlayer->currentRepeat() < mpPlayer->repeat())
//        return;
//    // use shortcut to replay in EventFilter, the options will not be set, so set here
//    mpPlayer->setFrameRate(Config::instance().forceFrameRate());
//    mpPlayer->setOptionsForAudioCodec(mpDecoderConfigPage->audioDecoderOptions());
//    mpPlayer->setOptionsForVideoCodec(mpDecoderConfigPage->videoDecoderOptions());
//    if (Config::instance().avformatOptionsEnabled())
//        mpPlayer->setOptionsForFormat(Config::instance().avformatOptions());
    btnPlay->setPlayState(false);
    sliderPos->setValue(0);
    sliderPos->setDisabled(true);
    sliderPos->setMinimum(0);
    sliderPos->setMaximum(0);
    labelCurrentTime->setText(QString::fromLatin1("00:00:00"));
    labelTotalTime->setText(QString::fromLatin1("00:00:00"));
    //tryShowControlBar();
    //ScreenSaver::instance().enable();
    //toggleRepeat(false);
    //mRepeateMax = 0;
    //killTimer(mCursorTimer);
    //unsetCursor();
    //if (m_preview)
      //  m_preview->setFile(QString());
}

void VideoPlayerView::onPaused(bool p)
{
    if (p) {
        qDebug("start pausing...");
        btnPlay->setPlayState(true);
    } else {
        qDebug("stop pausing...");
        btnPlay->setPlayState(false);
    }
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

bool VideoPlayerView::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    MSG* msg = reinterpret_cast<MSG*>(message);

    int xPos = 0, yPos = 0;
    switch(msg->message)
    {
    case WM_NCHITTEST:
        xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if(this->childAt(xPos,yPos) == 0)
        {
            *result = HTCAPTION;
        }else{
            return false;
        }
        if(xPos > 0 && xPos < 5)
            *result = HTLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0))
            *result = HTRIGHT;
        if(yPos > 0 && yPos < 5)
            *result = HTTOP;
        if(yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOM;
        if(xPos > 0 && xPos < 5 && yPos > 0 && yPos < 5)
            *result = HTTOPLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0) && yPos > 0 && yPos < 5)
            *result = HTTOPRIGHT;
        if(xPos > 0 && xPos < 5 && yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOMLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0) && yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOMRIGHT;

        return true;
        break;

    case WM_GETMINMAXINFO:
        if (::IsZoomed(msg->hwnd)) {

            RECT frame = { 0, 0, 0, 0 };
            AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
            frame.left = abs(frame.left);
            frame.top = abs(frame.bottom);
            this->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
        }
        else {
            this->setContentsMargins(0, 0, 0, 0);
        }

        *result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        break;

    case WM_NCCALCSIZE:
        return true;
        break;
    default:
        return false;
    }

}

