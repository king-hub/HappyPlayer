#ifndef BUTTONFORSTATUSBAR_H
#define BUTTONFORSTATUSBAR_H

#include <QWidget>
#include "Button/buttonheaderfile.h"
class ButtonForStatusBar : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonForStatusBar(QWidget *parent = 0);
    void setType(QString gettype);
signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
private:
    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus status;
    bool _ifPress = false;
    QString type;
};

#endif // BUTTONFORSTATUSBAR_H
