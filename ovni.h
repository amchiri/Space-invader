#ifndef OVNI_H
#define OVNI_H

#include <QGraphicsObject>
#include <QTimerEvent>
#include <QPainter>
#include <QCursor>


class Ovni : public QGraphicsObject
{
private:
    int direction;
    bool flag_lance;
public:
    Ovni()
        :direction(1),
         flag_lance(true)
    {

    }

    // CREE L'IMAGE DE L'OVNI
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {
        painter -> drawImage(QRectF(0, 0, 50, 50), QImage(":/Images-20210621/ovni_jaune.png"));
    }
    QRectF boundingRect() const override
    {
        QRectF rect (0, 0, 50, 50);
        return rect;
    }

    int getDirection()
    {
        return direction;
    }

    void setOvniRun(bool run){
        flag_lance = run;
    }

    void timerEvent(QTimerEvent *event) override
    {
        QPointF position_actuelle;

        if(rand() % 2 == 0)
        {
            if(rand() % 2 == 0 && flag_lance)
            {
                direction = -1;
            } else if (flag_lance) {
                direction = 1;
            }

        }
        position_actuelle = pos();
        setPos(position_actuelle + QPointF(direction*40,0));
    }
};

#endif // OVNI_H
