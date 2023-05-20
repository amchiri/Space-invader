#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "vaisseau.h"
#include "ennemis.h"
#include "projectile.h"
#include "myscene.h"
#include "ovni.h"
#include "protectwall.h"
#include <QKeyEvent>
#include <QTimerEvent>
#include <QSoundEffect>
#include "dialog_name.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ship(new Vaisseau),
    scene(new MyScene),
    ovni(new Ovni),
    vie(3),
    score(0),
    select_ligne_max(0),
    select_ligne_min(0),
    select_remanent(1),
    redemarrer(false),
    difficulte(0),
    nom (new Dialog_name)


{
    ui -> setupUi(this);

    for(int j=0; j<5; j++)
    {
        for(int i=0; i<15; i++)
        {
            ennemis[i][j] = new Ennemis;                                    // Ajoute les objets ennemis à la scène (première ligne)
            if(j == 4)
            {
                ennemis[i][j] -> setType('b');
            } else if(j == 2 || j == 3)
            {
                ennemis[i][j] -> setType('r');
            } else {
                ennemis[i][j] -> setType('v');
            }
            ennemis[i][j] -> setPos((50*i + 200), (250 - j*40));
            scene -> addItem(ennemis[i][j]);

            cpt_ligne[i][j] = i + 1;
        }
    }
    for(int i=0; i<5; i++)                                                  // Ajoute les objets projectile à la scène destinés à être utilisé par le vaisseau
    {
        projectile[i] = new Projectile(QPointF(0,0), false);
        scene -> addItem(projectile[i]);
        projectile[i] -> hide();
    }
    for(int i=0; i<30; i++)                                                 // Ajoute les objets projectile à la scène destinés à être utilisé par le vaisseau
    {
        projectile_ennemis[i] = new Projectile(QPointF(0,0), true);         // Ajoute les objets projectile à la scène destinés à être utilisé par les ennemis
        scene -> addItem(projectile_ennemis[i]);
        projectile_ennemis[i] -> hide();
    }
    for(int i=0;i<4;i++)
    {
        mur[i] = new ProtectWall;
        mur[i] -> setPos(250*i+130, 600);
        scene -> addItem(mur[i]);
    }
    scene -> addItem(ship);                                                 // Ajoute l'objet vaisseau à la scène
    ovni -> hide();
    scene -> addItem(ovni);
    scene -> Afficher_txt("Appuyer sur la touche espace pour démarrer.");   // Ajoute le texte du menu à la scène
    scene -> Afficher_vie(vie);
    scene -> Afficher_score(score);
    ui -> graphicsView -> setScene(scene);                                  // Met en place la scène
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    static int cpt = 0;
    static bool start = false;

    // Donne l'information que le clavier est actif
    switch(event -> key())
    {
        case Qt::Key_D:
            ship -> mouvement_droit(true);                                  // Commande aller sur la droite
            ship -> mouvement_gauche(false);
            break;
        case Qt::Key_Q:                                                     // Commande aller sur la gauche
            ship -> mouvement_gauche(true);
            ship -> mouvement_droit(false);
            break;
        case Qt::Key_Space:                                                 // Commande du tir
            if(!start && !redemarrer)
            {



                for(int j=0; j<5; j++)
                {
                    for(int i=0; i<15; i++)
                    {
                        timer[i][j] = ennemis[i][j] -> startTimer(1000);// Lance des timers différents pour chaque énnemis
                        ennemis[i][j]->set_tir();
                    }
                }
                scene -> Cacher_txt();
                main_timer = startTimer(1000/33);
                start = true;
            } else if(redemarrer)
            {
                for(int j=0; j<5; j++)
                {

                    for(int i=0; i<15; i++)
                    {
                        ennemis[i][j] -> setPos((50*i + 200), (250 - j*40));
                        ennemis[i][j] -> show();
                        ennemis[i][j] -> setEnabled(true);
                        ennemis[i][j]->set_tir();


                        cpt_ligne[i][j] = i + 1;

                        timer[i][j] = ennemis[i][j] -> startTimer(1000/(1+difficulte));// Lance des timers différents pour chaque énnemis
                    }
                }
                redemarrer = false;
                scene -> Cacher_txt();
                scene -> Afficher_vie(vie);
                main_timer = startTimer(1000/33);
            } else {
                projectile[cpt] -> setPos(((ship -> pos().x()) + 573), 900);
                projectile[cpt] -> show();
                projectile[cpt] -> setEnabled(true);
                projectile[cpt] -> setTimer();
                effect.setSource(QUrl::fromLocalFile(":/Effets sonores-20210621/sound112.wav"));
                effect.play();

                cpt ++;
                if(cpt == 4)
                {
                    cpt = 0;
                }
            }
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    // Donne l'information que le clavier est relaché
    ship -> mouvement_droit(false);
    ship -> mouvement_gauche(false);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    static bool flag = true;
    int n_max;
    int n_min;

    n_max = calcul_max(cpt_ligne);
    n_min = calcul_min(cpt_ligne);
    acceleration(cpt_ligne,select_ligne_empty);
    mouvements_ennemis(flag, ennemis, n_max, n_min);
    ennemis_touche();
    TirEnnemis();
    vaisseau_touche();
    spawn_ovni();
    win_game(Check_lignes(cpt_ligne));
    setacceleration();








}

int MainWindow::calcul_max(int tab[15][5])
{
    int max = 0;

    for(int j=0; j<5; j++)
    {
        for(int i=0; i<15; i++)
        {
            if((tab[i][j] > 0))
            {
                if((j > 0) && (tab[i][j] > (max + 1))){
                max = tab[i][j] - 1;
                select_ligne_min = j;
                } else if(j == 0)
                {
                    max = tab[i][j] - 1;
                    select_ligne_min = j;

                }
            }
        }
    }
    return max;
}

int MainWindow::calcul_min(int tab[15][5])
{
    int min = 14;

    for(int j=0; j<5; j++)
    {
        for(int i=0; i<15; i++)
        {

            if((tab[14-i][5-j] > 0))
            {
                if((j > 0) && (tab[14-i][5-j] < (min + 1)))
                {
                    min = tab[14-i][5-j] - 1 ;
                    select_ligne_min = j;
                }
                else if(j == 0)
                {
                    min = tab[14-i][5-j] - 1 ;
                    select_ligne_min = j;

                }
            }
        }
    }
    return min;
}

bool MainWindow::Check_lignes(int tab[15][5])
{
    int lignes = 0;
    static bool empty = false;

    for(int j=0; j<5; j++)
    {
        for(int i=0; i<15; i++)
        {
            if((tab[i][j] > 0))
            {
                lignes = lignes + tab[i][j];
            }
        }
        if(lignes == 0)
        {
            empty = true;

        } else {
            empty = false;
        }

    }

    return empty;
}

void MainWindow::mouvements_ennemis(bool &flag, Ennemis * tab[15][5],int max,int min)
{
    if((tab[min][select_ligne_min] -> pos().x() <= 0) && !flag)
    {
         for(int j=0; j<5; j++)
        {
            for(int i=0; i<15; i++)
            {
                tab[i][j] -> setdescendre(true);
            }
        }
        flag = true;
    } else if((tab[max][select_ligne_max] -> pos().x() >= 1080) && flag)
    {
        for(int j=0; j<5; j++)
        {
            for(int i=0; i<15; i++)
            {
                tab[i][j] -> setdescendre(true);
            }
        }
        flag = false;
    }


}

void MainWindow::ennemis_touche()
{
    for(int k=0; k<5; k++)
    {
        QList<QGraphicsItem*> items_dangereux = scene -> collidingItems(projectile[k]);
        for(QGraphicsItem *item:items_dangereux)
        {
            for(int j=0; j<5; j++)
            {
                for(int i=0; i<15; i++)
                {
                    if((ennemis[i][j] == item) && (projectile[k] -> isEnabled()) && (ennemis[i][j] -> isEnabled()))
                    {
                        ennemis[i][j] -> hide();
                        ennemis[i][j] -> setEnabled(false);
                        cpt_ligne[i][j] = 0;
                        projectile[k] -> hide();
                        projectile[k] -> setEnabled(false);

                        if(j == 4)
                        {
                            score = score + 30;
                        } else if(j == 2 || j == 3)
                        {
                            score = score + 20;
                        } else {
                            score = score + 10;
                        }
                    } else if((ovni -> isEnabled()) && (projectile[j] -> isEnabled()) && (ovni == item))
                    {
                        ovni -> hide();
                        ovni -> setEnabled(false);
                        projectile[j] -> hide();
                        projectile[j] -> setEnabled(false);
                        ovni -> killTimer(ovni_timer);
                        ovni -> setOvniRun(true);
                        score = score + 50;
                        flag_ovni[0] = false;
                        flag_ovni[1] = false;
                    }


                }
            }
            scene -> Afficher_score(score);

            for(int l=0; l<4; l++)
            {
                if((projectile[k] -> isEnabled()) && (mur[l] == item))
                {
                    projectile[k] -> hide();
                    projectile[k] -> setEnabled(false);
                    mur[l] -> destroy_cpt();
                }
            }
        }
    }
}

void MainWindow::TirEnnemis()
{
    static int cpt = 0;

    for(int j=0; j<5; j++)
    {
        for(int i=0; i<15; i++)
        {
            if((ennemis[i][j] -> isEnabled()) && (ennemis[i][j] -> getPretATirer()))
            {
                ennemis[i][j] -> setPretATirer(false);
                projectile_ennemis[cpt] -> setPos((ennemis[i][j] -> pos()));
                projectile_ennemis[cpt] -> show();
                projectile_ennemis[cpt] -> setEnabled(true);
                projectile_ennemis[cpt] -> setTimer();
                effect.setSource(QUrl::fromLocalFile(":/Effets sonores-20210621/sound83.wav"));
                effect.play();
            }

            cpt ++;
            if(cpt == 30)
            {
                cpt = 0;
            }
        }
    }
}

void MainWindow::vaisseau_touche()
{
    QList<QGraphicsItem*> items_dangereux = scene -> collidingItems(ship);
    for(QGraphicsItem *item:items_dangereux){
        for(int l=0; l<5; l++)
        {
            for (int k=0; k<15; k++)
            {
                if((ennemis[k][l] == item) && (ennemis[k][l] -> isEnabled()))
                {
                    for(int j=0; j<5; j++)
                    {
                        projectile[j]->setEnabled(false);
                        for(int i=0; i<15; i++)
                        {
                            ennemis[i][j] -> killTimer(timer[i][j]);
                        }
                    }
                    effect.setSource(QUrl::fromLocalFile(":/Effets sonores-20210621/game_over.wav"));
                    effect.play();
                    scene -> Afficher_txt("                         GAME OVER !\nAppuyer sur la touche espace pour redémarrer.");
                    vie = 3;
                    killTimer(main_timer);
                    redemarrer = true;
                    nom->setModal(true);
                    nom->exec();
                    ajouterNomDansCSV(nom->return_name().toStdString(),score, nomFichier);

                }
            }
        }
    }

    for(int k=0; k<29; k++)
    {
        QList<QGraphicsItem*> items_dangereux = scene -> collidingItems(projectile_ennemis[k]);
        for(QGraphicsItem *item:items_dangereux)
        {
            if((ship == item) && (projectile_ennemis[k] -> isEnabled()))
            {
                vie = vie - 1;
                scene -> Afficher_vie(vie);
                projectile_ennemis[k] -> hide();
                projectile_ennemis[k] -> setEnabled(false);
                effect.play();
                effect.setSource(QUrl::fromLocalFile(":/Effets sonores-20210621/sound98.wav"));
                effect.play();
                if(vie == 0)
                {
                    for(int j=0; j<5; j++)
                    {
                        for(int i=0; i<15; i++)
                        {
                            ennemis[i][j] -> killTimer(timer[i][j]);
                            ennemis[i][j]->set_tir();
                        }
                    }
                    effect.setSource(QUrl::fromLocalFile(":/Effets sonores-20210621/game_over.wav"));
                    effect.play();
                    scene -> Afficher_txt("                         GAME OVER !\nAppuyer sur la touche espace pour redémarrer.");
                    vie = 3;

                    killTimer(main_timer);
                    difficulte=0;
                    redemarrer = true;
                    nom->setModal(true);
                    nom->exec();
                    ajouterNomDansCSV(nom->return_name().toStdString(),score, nomFichier);


                }
            }
            for(int l=0; l<4; l++)
            {
                if((projectile_ennemis[k] -> isEnabled()) && (mur[l] == item))
                {
                    projectile_ennemis[k] -> hide();
                    projectile_ennemis[k] -> setEnabled(false);
                    mur[l] -> destroy_cpt();
                }
            }
        }
    }
}

void  MainWindow::spawn_ovni()
{
    if(rand() % 560 == 0 && !flag_ovni[0])
    {
        ovni -> setOvniRun(false);
        if(ovni -> getDirection() == 1 && !flag_ovni[1])
        {
           ovni -> show();
           ovni -> setPos(0,120);
           ovni_timer = ovni -> startTimer(1000);
           ovni -> startTimer(1000);
           ovni -> setEnabled(true);
           flag_ovni[1] = true;
        } else if(!flag_ovni[1])
        {
            ovni -> show();
            ovni_timer = ovni -> startTimer(1000);
            ovni -> setPos(1080,120);
            ovni -> setEnabled(true);
            flag_ovni[1] = true;
        }
    } else if((ovni -> pos().x() <= -30) || (ovni -> pos().x() >= 1110))
    {
        ovni -> hide();
        ovni -> setEnabled(false);
        killTimer(ovni_timer);
        ovni -> setOvniRun(true);
        flag_ovni[0] = false;
        flag_ovni[1] = false;
    }

}
void MainWindow::win_game(bool a){
    if(a){
    effect.setSource(QUrl::fromLocalFile(":/Effets sonores-20210621/ta-da-sound-effect.wav"));
    effect.play();
    scene -> Afficher_txt("                           GAGNÉ !\nAppuyer sur la touche espace pour redémarrer.");
    vie = 3;
    killTimer(main_timer);
    redemarrer = true;
    difficulte=difficulte+(1/3);
    for(int j=0; j<5; j++)
    {
        for(int i=0; i<15; i++)
        {
            ennemis[i][j] -> killTimer(timer[i][j]);
            ennemis[i][j]->set_tir();


    }
}
    }


}

int MainWindow::acceleration(int tab[15][5],int & resultat){
    int calcul;
     resultat=1;
    for (int j=0;j<5 ;j++ ) {
        calcul=0;
        for (int i=0;i<15 ; i++){
           calcul=calcul+tab[i][j];

        }
        if(calcul==0){
            resultat=resultat+1;
        }
    }
    return resultat;
}
void MainWindow::setacceleration(){

    if(select_ligne_empty != select_remanent){
        select_remanent=select_ligne_empty;
        for(int j=0; j<5; j++)
        {
            for(int i=0; i<15; i++)
            {
                ennemis[i][j]->killTimer(timer[i][j]);
              timer[i][j] = ennemis[i][j] -> startTimer(1000/(select_ligne_empty+difficulte));
                }

        }


    }
}

void MainWindow::ajouterNomDansCSV(const std::string& nom,int score, const std::string& nomFichier)
{
    std::ofstream fichier(nomFichier, std::ios::app); // Ouvre le fichier en mode ajout

    fichier << nom <<";"<< score << std::endl; // Ajoute le nom suivi d'un saut de ligne
    std::cout << "Nom enregistré avec succès dans le fichier CSV." << std::endl;

    fichier.close(); // Ferme le fichier
}



