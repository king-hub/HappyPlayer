#include "TitleBar.h"
#include <QBitmap>
TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(30);
    int nSpacing = 10;
    int nLeft = 10;
    int nTop = 10;


    setAutoFillBackground(true);
    setAttribute(Qt::WA_TranslucentBackground);
    btnClose = new ButtonForStatusBar(this);
    btnClose->setType("Close");
    btnClose->setFixedSize(15,15);
    btnClose->setToolTip("关闭");
    connect(btnClose,SIGNAL(clicked(bool)),this,SLOT(ViewEvent()));
    btnMin = new ButtonForStatusBar(this);
    btnMin->setType("Min");
    btnMin->setToolTip("最小化");
    btnMin->setFixedSize(15,15);
    connect(btnMin,SIGNAL(clicked(bool)),this,SLOT(ViewEvent()));
    btnMax = new ButtonForStatusBar(this);
    btnMax->setType("Max");
    btnMax->setToolTip("最大化");
    btnMax->setFixedSize(15,15);
    connect(btnMax,SIGNAL(clicked(bool)),this,SLOT(ViewEvent()));
    btnClose->move(nLeft, nTop);
    btnMin->move(nLeft + btnClose->width() + nSpacing, nTop);
    btnMax->move(nLeft + btnMin->width() + btnMax->width() + 2 * nSpacing, nTop);
}

TitleBar::~TitleBar()
{

}
void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit btnMax->clicked();
}

void TitleBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawRoundedRect(0, 3, width(), height(), 5, 5);

}


void TitleBar::ViewEvent()
{
    ButtonForStatusBar *pButton = qobject_cast<ButtonForStatusBar *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
        {
            if (pButton == btnMin)
            {
                pWindow->showMinimized();
            }
            else if (pButton == btnMax)
            {
                pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
            }
            else if (pButton == btnClose)
            {
                qApp->exit();
            }
        }
}
