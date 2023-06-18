#include "secondewindow.h"
#include "ui_secondewindow.h"

secondewindow::secondewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondewindow)
{
    ui->setupUi(this);
    setFixedSize(400,268);
}

secondewindow::~secondewindow()
{
    delete ui;
}

void secondewindow::on_pushButton_comptes_clicked()
{
    hide();
    clientsComptes = new comptes(this);
    clientsComptes->show();
}

void secondewindow::on_pushButton_clients_clicked()
{
    hide();
    classepremier = new premierclasse(this);
    classepremier->show();
}
