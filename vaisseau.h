#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <QGraphicsObject>
#include <QPainter>
#include <QCursor>


class Vaisseau : public QGraphicsObject
{
    private:
        bool gauche, droite;
    public:
        Vaisseau()
           :gauche(false),
            droite(false)
        {
            startTimer(1000/33);         //Lance le chrono
        }

        void mouvement_gauche(bool G)    //Fonction qui gère le flag gauche pour le clavier
        {
            gauche = G;
        }
        void mouvement_droit(bool D)    //Fonction qui gère le flag droit pour le clavier
        {
            droite = D;
        }


        // CREE L'IMAGE DU VAISSEAU
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
        {
            painter -> drawImage(QRectF(550, 900, 50, 50), QImage(":/Images-20210621/vaisseau.png"));
        }

        QRectF boundingRect() const override
        {
            QRectF rect (560, 900, 30, 50);
            return rect;
        }


        // GERE LE MOUVEMENT DU VAISSEAU
        void timerEvent(QTimerEvent *event) override
        {
            QPointF position_actuelle = pos();
            int position_souris;
            static int position_souris_old = 550;
            int ajout_mouv;

            if(gauche || droite)
            {
                // PARTIE CLAVIER
                if(gauche && (position_actuelle.x() > -580))
                {
                    setPos(position_actuelle + QPointF(-10, 0));
                }else if(droite && (position_actuelle.x() < 530))
                {
                    setPos(position_actuelle + QPointF(10, 0));
                }
            } else {
                // PARTIE SOURIS
                position_souris = QCursor::pos().x();
                ajout_mouv = position_souris - position_souris_old;
                if((-585 < (position_actuelle.x() + ajout_mouv)) && ((position_actuelle.x() + ajout_mouv) < 535))
                {
                    setPos(position_actuelle + QPointF((position_souris - position_souris_old), 0));
                }
                position_souris_old = position_souris;
            }
        }
};

#endif // VAISSEAU_H
