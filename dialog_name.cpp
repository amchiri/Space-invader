#include "dialog_name.h"
#include "ui_dialog_name.h"

Dialog_name::Dialog_name(QWidget *parent) : QDialog(parent) {
    ui.setupUi(this);

    connect(ui.lineEdit, &QLineEdit::textChanged, [=](const QString &text) {
        qDebug() << "Le texte a été modifié :" << text;
        name=text;
    });

    connect(ui.radioButton, &QRadioButton::toggled, this, &Dialog_name::onRadioButtonToggled);
}

Dialog_name::~Dialog_name() {
    // Aucune action nécessaire ici car les objets sont gérés par l'interface utilisateur générée
}

void Dialog_name::onRadioButtonToggled(bool checked) {
    if (checked) {
        // Le bouton radio a été activé
        close();
    }
}

QString Dialog_name::return_name(){
    return name;
}

// ... autres fonctions ou slots si nécessaire

