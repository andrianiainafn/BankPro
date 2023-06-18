#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> username ->setPlaceholderText("Entrer Votre nom d' utilisateur");
    ui -> password ->setPlaceholderText("Entrer votre mots de passe");
    ui -> fullname -> setPlaceholderText("Entrer votre Nom complet");
    setFixedSize(800,515);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_seConnecter_clicked()
{
    hide();
    myLogin = new Login(this);
    myLogin ->show();
}

void MainWindow::on_inscrire_clicked()
{
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    if(myDataBase.open()){
        QString username,fullname,password;
        username = ui -> username ->text();
        fullname = ui -> fullname -> text();
        password = ui -> password -> text();
        QSqlQuery query;
        query.prepare("INSERT INTO admins (username,password,name)"
                      "VALUES(:username,:password,:fullname)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.bindValue(":fullname",fullname);
        if(query.exec()){
            QMessageBox::information(this,"Sign UP","Autenthification reussi");
            hide();
            secondeWindow = new secondewindow(this);
            secondeWindow->show();
        }else{
            QMessageBox::warning(this,"Sign UP","echec de l' autentification");
        }
    }else{
        QMessageBox::warning(this,"DATABASE"," echec de l' ouverture du BD");
    }

}
