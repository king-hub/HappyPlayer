#ifndef BUTTONPLAY_H
#define BUTTONPLAY_H

#include <QWidget>
#include <Button/buttonheaderfile.h>
class ButtonPlay : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonPlay(QWidget *parent = 0);
    //static bool ifPlay = false;
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
    //QString type;
};

#endif // BUTTONPLAY_H
