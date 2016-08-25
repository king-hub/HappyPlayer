//thank you from CSDN
#include "TitleBar.h"
#include <QBitmap>
TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(30);   
    setAutoFillBackground(true);
    setAttribute(Qt::WA_TranslucentBackground);
    InitUI();
    InitEvents();
    //custom layout
    btnClose->move(LeftValue, TopValue);
    btnMin->move(LeftValue + btnClose->width() + SpacingValue, TopValue);
    btnMax->move(LeftValue + btnMin->width() + btnMax->width() + 2 * SpacingValue, TopValue);
}

TitleBar::~TitleBar()
{

}

void TitleBar::InitUI()
{
    btnClose = new ButtonForStatusBar(this);
    btnClose->setType("Close");
    btnClose->setFixedSize(15,15);
    btnClose->setToolTip(QString::fromUtf8("关闭"));

    btnMin = new ButtonForStatusBar(this);
    btnMin->setType("Min");
    btnMin->setFixedSize(15,15);
    btnMin->setToolTip(QString::fromUtf8("最小化"));

    btnMax = new ButtonForStatusBar(this);
    btnMax->setType("Max");
    btnMax->setFixedSize(15,15);
    btnMax->setToolTip(QString::fromUtf8("最大化"));
}

void TitleBar::InitEvents()
{
    connect(btnClose,&QAbstractButton::clicked,this,&TitleBar::ViewEvent);
    connect(btnMin,&QAbstractButton::clicked,this,&TitleBar::ViewEvent);
    connect(btnMax,&QAbstractButton::clicked,this,&TitleBar::ViewEvent);
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
#endif
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit btnMax->clicked();
}

void TitleBar::paintEvent(QPaintEvent *)
{
    //draw round rect
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


