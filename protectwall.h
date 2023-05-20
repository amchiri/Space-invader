#ifndef PROTECTWALL_H
#define PROTECTWALL_H
#include <QGraphicsObject>
#include <QTimerEvent>
#include <QPainter>
#include <QPointF>



class ProtectWall : public QGraphicsObject
{
private:
    int cpt;

public:
    ProtectWall():
        cpt(30)
    {}

    // CREE L'IMAGE DU MUR
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {

        painter -> drawImage(QRectF(0,0,120,80), QImage(":/Images-20210621/protection_wall.png"));

    }
    QRectF boundingRect() const override
    {
        QRectF rect(0,0,120,80);
        return rect;
    }

    void destroy_cpt()
    {
        cpt = cpt - 1;
        if(cpt == 0)
        {
            hide();
        }
    }

    void reset(){
        cpt = 30;
    }
};

#endif // PROTECTWALL_H
