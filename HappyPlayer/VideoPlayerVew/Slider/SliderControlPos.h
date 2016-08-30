#ifndef SLIDERCONTROLPOS_H
#define SLIDERCONTROLPOS_H

#include <QWidget>
#include <QSlider>
#include <QMouseEvent>
#include <QEvent>
class SliderControlPos : public QSlider
{
    Q_OBJECT
public:
    explicit SliderControlPos(QWidget *parent = 0);

signals:
    void onEnter();
    void onLeave();
    void onHover(int pos, int value);
protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    //#if CODE_FOR_CLICK == 1
        inline int pick(const QPoint &pt) const;
        int pixelPosToRangeValue(int pos) const;
        void initStyleOption_Qt430(QStyleOptionSlider *option) const;
    //#endif
public slots:
};

#endif // SLIDERCONTROLPOS_H
