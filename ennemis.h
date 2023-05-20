#ifndef ENNEMIS_H
#define ENNEMIS_H

#include <QGraphicsObject>
#include <QTimerEvent>
#include <QPainter>
#include <QPointF>

class Ennemis : public QGraphicsObject
{
private:
    typedef enum {VERT, ROUGE, BLEU} type_color;
    type_color type;
    int direction, compteur;
    bool descendre, pret_a_tirer,stop;
    double difficulte;

public:
    Ennemis()
        :direction(1),
         compteur(0),
         descendre(false),
         pret_a_tirer(false),
         difficulte(1.00),
         stop(true)
    {}


    // CREE L'IMAGE DE L'ENEMI
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {
        switch(type)
        {
            case VERT:
                if(compteur%2 == 0)
                {
                    painter -> drawImage(QRectF(0,0,30,30),QImage(":/Images-20210621/poulpe2.png"));
                } else {
                    painter -> drawImage(QRectF(0,0,30,30),QImage(":/Images-20210621/poulpe.png"));
                }
                break;
            case ROUGE:
                if(compteur%2 == 0)
                {
                    painter -> drawImage(QRectF(0,0,30,30),QImage(":/Images-20210621/monstre_up.png"));
                } else {
                    painter -> drawImage(QRectF(0,0,30,30),QImage(":/Images-20210621/monstre_down.png"));
                }
                break;
            case BLEU:
                if(compteur%2 == 0)
                {
                    painter -> drawImage(QRectF(0,0,30,30),QImage(":/Images-20210621/meduse.png"));
                } else {
                    painter -> drawImage(QRectF(0,0,30,30),QImage(":/Images-20210621/meduse2.png"));
                }
                break;
        }
    }
    QRectF boundingRect() const override
    {
        QRectF rect(0,0,30,30);
        return rect;
    }


    // GERE LE MOUVEMENT DES ENNEMIS
    void setdescendre(bool vertical)
    {
        descendre = vertical;
    }

    void setPretATirer(bool pret)
    {
        pret_a_tirer = pret;
    }

    bool getPretATirer()
    {
        return pret_a_tirer;
    }

    void setType(char color)
    {
        switch(color)
        {
            case 'v':
                type = VERT;
                break;
            case 'r':
                type = ROUGE;
                break;
            case 'b':
                type = BLEU;
                break;
        }
    }

    void setDifficulte(double hardness)
    {
        difficulte = hardness;
    }

    void timerEvent(QTimerEvent *event) override
    {
        QPointF position_actuelle;

        if(descendre)                                               // Baisse d'un cran les énemis à la fin de la ligne
        {
            position_actuelle = pos();
            setPos(position_actuelle + QPointF(0,30));
            descendre = false;
            direction = direction * (-1);
        } else {                                                    // Déplace lattéralement les énnemis
            position_actuelle = pos();
            setPos(position_actuelle+QPointF(direction*30,0));
        }

        compteur ++;                                                // Compteur pour faire danser les énnemis

        if((rand() % static_cast<int>(200 * difficulte)) == 0 && stop==false)                                     // Tires aléatoire ennemis
        {
            pret_a_tirer = true;
        }
        else if (stop==true){
                 pret_a_tirer = false;


        }
    }
    void set_tir(){
        stop=!stop;
    }
};

#endif // ENNEMIS_H
