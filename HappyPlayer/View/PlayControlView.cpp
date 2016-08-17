#include "PlayControlView.h"

PlayControlView::PlayControlView(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(1024,500);
}

void PlayControlView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::gray);
    painter.drawRect(rect());
}
