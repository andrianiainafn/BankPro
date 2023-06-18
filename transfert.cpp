#include "transfert.h"
#include "ui_transfert.h"
#include <QMessageBox>
#include "comptes.h"
comptes *h;
transfert::transfert(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::transfert)
{
    ui->setupUi(this);
    ui->numCompte1 -> setPlaceholderText("Numero de l' envoyeur");
    ui->numCompte2 -> setPlaceholderText("Numero du recepteur");
    ui->montant -> setPlaceholderText("Montant a envoyer");
    setFixedSize(580,316);
}

transfert::~transfert()
{
    delete ui;
}

void transfert::on_transferer_clicked()
{
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte1,compte2;
    int montant;
    compte1 = ui -> numCompte1 -> text();
    compte2 = ui -> numCompte2 -> text();
    montant = ui -> montant -> text().toInt();
    if(myDataBase.open()){
        QMessageBox::information(this,"myDataBase","OPEN");
        querymodel = new QSqlQueryModel();
        querymodel->setQuery("SELECT solde FROM clients WHERE compte = '"+ compte1 +"' ");
        int ancienSolde;
        for (int i = 0 ; i < querymodel->rowCount();i++) {
            ancienSolde = querymodel->record(i).value("solde").toInt();
            qDebug() << ancienSolde;
        }
        queryupdatemodel = new QSqlQueryModel();
        queryupdatemodel->setQuery("SELECT solde FROM clients WHERE compte = '"+ compte2 +"' ");
        int ancienSolde1;
        for (int i = 0 ; i < queryupdatemodel->rowCount();i++) {
            ancienSolde1 = queryupdatemodel->record(i).value("solde").toInt();
            qDebug() << ancienSolde1;
        }

        ancienSolde = ancienSolde - montant;
        QSqlQuery query1,query2;
        query1.prepare("UPDATE  clients SET solde = :ancienSolde WHERE compte = :compte1");
        query1.bindValue(":ancienSolde", ancienSolde);
        query1.bindValue(":compte1", compte1);
        if(query1.exec()){
            QMessageBox::information(this,"UPDATE","Update Solde 1 reussi");
        }else{
            QMessageBox::warning(this,"UPDATE","Update solde 1 echouer");
        }
        ancienSolde1 = ancienSolde1 + montant;
        qDebug() << ancienSolde1;
        query2.prepare("UPDATE  clients SET solde = :ancienSolde1 WHERE compte = :compte2");
        query2.bindValue(":ancienSolde1", ancienSolde1);
        query2.bindValue(":compte2", compte2);
        if(query2.exec()){
            QMessageBox::information(this,"UPDATE","Update solde 2 reussi");
        }else{
             QMessageBox::warning(this,"UPDATE","Update solde 2 echouer");
        }
    }
}

void transfert::on_back_clicked()
{
    hide();
    h = new comptes(this);
    h->show();
}
