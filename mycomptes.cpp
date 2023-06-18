#include "mycomptes.h"
#include "ui_mycomptes.h"

mycomptes::mycomptes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mycomptes)
{
    ui->setupUi(this);
}

mycomptes::~mycomptes()
{
    delete ui;
}

