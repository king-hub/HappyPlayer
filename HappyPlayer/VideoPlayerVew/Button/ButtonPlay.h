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
};

#endif // BUTTONPLAY_H
