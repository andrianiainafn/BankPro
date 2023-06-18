#include "mylogin.h"
#include "ui_mylogin.h"

myLogin::myLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myLogin)
{
    ui->setupUi(this);
}

myLogin::~myLogin()
{
    delete ui;
}
