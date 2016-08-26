#include "MainView.h"
#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <windowsx.h>
#endif
#include <QLinearGradient>
#include <QPainterPath>
#include <QBitmap>
MainView::MainView(QWidget *parent)
    : QWidget(parent)
{
    InitView();
    InitEvent();
}

MainView::~MainView()
{

}
#ifdef Q_OS_OSX
//Let View Move
void MainView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        _DragPosition = event->globalPos() - geometry().topLeft();
        event->accept();
    }
}

void MainView::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons() & Qt::LeftButton )
    {
        move(event->globalPos() - _DragPosition);
    }
}

//
#endif

void MainView::mousePressEvent(QMouseEvent *event)
{
    if (ReleaseCapture())
           SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    event->ignore();
}

void MainView::mouseDoubleClickEvent(QMouseEvent *)
{
    this->isMaximized() ? this->showNormal() : this->showMaximized();
}

void MainView::setupUI()
{
    titleBar = new TitleBar(this);
    viewVideoPlayerView = new VideoPlayerView(this);
    layoutMain = new QVBoxLayout(this);
    layoutMain->setSpacing(0);
    layoutMain->setContentsMargins(QMargins());
    setLayout(layoutMain);
    layoutMain->addWidget(titleBar);
    layoutMain->addWidget(viewVideoPlayerView);
}

void MainView::InitView()
{    
    setupUI();
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.8);
    titleBar->setGraphicsEffect(effect);       
}

void MainView::InitEvent()
{

}

void MainView::paintEvent(QPaintEvent *)
{

}
