#ifndef DIALOG_NAME_H
#define DIALOG_NAME_H

#include <QDialog>
#include "ui_dialog_name.h"

class Dialog_name : public QDialog
{
    Q_OBJECT

public:
    Dialog_name(QWidget *parent = nullptr);
    ~Dialog_name();
    QString return_name();

private slots:
    void onRadioButtonToggled(bool checked);


private:
    Ui::Dialog_name ui;
    QString name;
};

#endif // DIALOG_NAME_H

