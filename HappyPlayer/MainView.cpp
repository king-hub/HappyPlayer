#include "MainView.h"
#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <windows.h>
#include <windowsx.h>
#include <QtMath>
#endif
#include <QLinearGradient>
#include <QPainterPath>
#include <QBitmap>
MainView::MainView(QWidget *parent)
    : QWidget(parent)
{
    HWND hwnd = (HWND)this->winId();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    this->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    InitView();
    InitEvent();

}

MainView::~MainView()
{

}

void MainView::mousePressEvent(QMouseEvent *event)
{
//    if (ReleaseCapture())
//           SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
//    event->ignore();
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
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(9, 9, this->width()-18, this->height()-18);


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));


    QColor color(0, 0, 0, 50);
    for(int i=0; i<9; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(9-i, 9-i, this->width()-(9-i)*2, this->height()-(9-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

bool MainView::nativeEvent(const QByteArray &eventType, void *message, long *result)
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

