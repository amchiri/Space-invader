#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsObject>
#include <QPainter>
#include <QTimerEvent>
#include <QCursor>


class Projectile : public QGraphicsObject
{
private:
    QPointF location;
    int id;
    bool time, type;

public:
    Projectile(QPointF position, bool color)
        :location(position),
         type(color)
    {
        setPos(location);
    }


    // CREE L'IMAGE DU PROJECTILE
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {
        if(!type)                                   // Projectiles jaunes : projectiles du vaisseau
        {
            painter -> setBrush(Qt::yellow);
            painter -> drawRect(QRectF(0,0,2,20));
        } else if(type)                             // Projectiles rouges : projectiles des ennemis
        {
            painter -> setBrush(Qt::red);
            painter -> drawRect(QRectF(0,0,2,20));
        }
    }
    QRectF boundingRect() const override
    {
        QRectF rect(0,0,5,20);
        return rect;
    }


    // GERE LE MOUVEMENT DU PROJECTILE
    void setTimer(void)
    {
        if(!time)
        {                               // initialisation (premier appuis sur espace)
            id = startTimer(100);
            time = true;
        } else {
            killTimer(id);              // arrêt du chrono à chaque appuis sur espace, pour que chaque projectile ait la bonne vitesse
            id = startTimer(100);
        }
    }

    void timerEvent(QTimerEvent *event) override
    {
        if(!type)                                           // Projectiles jaunes : se déplacent vers le haut
        {
            QPointF position_actuelle = pos();
            setPos(position_actuelle + QPointF(0,-40));
        } else if(type)                                     // Projectiles rouges : se déplacent vers le bas
        {
            QPointF position_actuelle = pos();
            setPos(position_actuelle + QPointF(0,15));
        }
    }
};

#endif // PROJECTILE_H
