#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QString>


class MyScene : public QGraphicsScene
{
private:
    QGraphicsSimpleTextItem *text_item;
    QGraphicsSimpleTextItem *vie_item;
    QGraphicsSimpleTextItem *score_item;
    QGraphicsSimpleTextItem *nom;

public:
    MyScene()
        :text_item(new QGraphicsSimpleTextItem),
         vie_item(new QGraphicsSimpleTextItem),
         score_item(new QGraphicsSimpleTextItem),
         nom(new QGraphicsSimpleTextItem)
    {
        setSceneRect(0,0,1100,950);                     // Défini la taille de la scène et place le point 0,0

        QPixmap image(":/Images-20210621/ciel.jpg");    // Défini le fond de la scène
        setBackgroundBrush(image);
    }

    void Afficher_txt(QString texte)
    {
        text_item -> setFont(QFont("Britannic Bold", 25));
        text_item -> setText(texte);
        text_item -> setPen(QPen(Qt::white));
        text_item -> setPos(QPointF(225, 475));
        addItem(text_item);
    }

    void Cacher_txt()
    {
        removeItem(text_item);
    }

    void Afficher_vie(int vie)
    {
        vie_item -> setFont(QFont("Britannic Bold", 25));
        vie_item -> setText("PV : " + QString::number(vie));
        vie_item -> setPen(QPen(Qt::white));
        vie_item -> setPos(QPointF(10, 10));
        addItem(vie_item);
    }

    void Afficher_score(int score)
    {
        score_item -> setFont(QFont("Britannic Bold", 25));
        score_item -> setText("Score : " + QString::number(score));
        score_item -> setPen(QPen(Qt::white));
        score_item -> setPos(QPointF(950, 10));
        addItem(score_item);
    }
    void afficher_nom(QString text){

    }
};

#endif // MYSCENE_H
