#include "dialog.h"
#include "ui_dialog.h"
#include <QTextEdit>
#include <QPushButton>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    text(),
    text1()
{
    ui->setupUi(this);
//    text1=ui->textEdit->placeholderText();
//    connect(ui->pushButton,&QPushButton::clicked,this,[this](){
//         text=text1;



//    });


}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::name(){
    return text;
}
