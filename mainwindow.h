#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myscene.h"
#include "vaisseau.h"
#include "ennemis.h"
#include "projectile.h"
#include "ovni.h"
#include "protectwall.h"
#include <QMainWindow>
#include "dialog_name.h"
#include <QSoundEffect>
#include <fstream>
#include <iostream>
#include <string>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    int calcul_max(int tab[15][5]);
    int calcul_min(int tab[15][5]);
    bool Check_lignes(int tab[15][5]);
    void mouvements_ennemis(bool &flag, Ennemis * tab[15][5],int max,int min);
    void TirEnnemis();
    void ennemis_touche();
    void vaisseau_touche();
    void spawn_ovni();
    void win_game(bool a);
    int acceleration(int tab[15][5],int & resultat);
    void setacceleration();
    void ajouterNomDansCSV(const std::string& nom,int score, const std::string& nomFichier);

private:
    Ui::MainWindow *ui;
    Vaisseau *ship;
    Ennemis *ennemis[15][5];
    Projectile *projectile[5], *projectile_ennemis[30];
    MyScene *scene;
    ProtectWall *mur[4];
    Ovni *ovni;
    int cpt_ligne[15][5], timer[15][5];
    int main_timer,ovni_timer;
    int vie, score;
    int select_ligne_max, select_ligne_min, select_ligne_empty,select_remanent;
    bool redemarrer, flag_ovni[2];
    double difficulte;
    Dialog_name *nom;
    QSoundEffect effect;
    std::string nomFichier = "noms.csv"; // Nom du fichier CSV


};

#endif // MAINWINDOW_H
