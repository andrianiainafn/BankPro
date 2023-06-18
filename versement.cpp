#include "versement.h"
#include "ui_versement.h"
#include <QMessageBox>
#include <QBEInteger>
#include "comptes.h"
comptes *c;
versement::versement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::versement)
{
    ui->setupUi(this);
    ui->date-> setPlaceholderText("Entrer le date de versement");
    ui -> montant -> setPlaceholderText("Entrer le montant du versement");
    ui -> numComptes -> setPlaceholderText("Entrer le numero de compte");
    ui -> numAffiche -> setPlaceholderText("Entrer le numero de compte");
    setFixedSize(980,526);
}

versement::~versement()
{
    delete ui;
}

void versement::on_verser_clicked()
{
   int montant;
   QString date,compte,comptenum;
   compte = ui -> numComptes -> text();
   date = ui -> date -> text();
   montant = (ui -> montant  -> text()).toInt();
   comptenum = compte;
    myDataBase =  QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    if(myDataBase.open()){
        QMessageBox::information(this,"DataBase","Open succes");
        QSqlQuery query;
        query.prepare("INSERT INTO versement(compte,montantVersement,dateVersement,clientV_compte)"
                      "VALUES(:compte,:montant,:date,:comptenum)");
        query.bindValue(":montant",montant);
         query.bindValue(":compte",compte);
         query.bindValue(":comptenum",comptenum);
         query.bindValue(":date",date);
         if(query.exec()){
             QMessageBox::information(this,"Inseted","success");
             querymodel = new QSqlQueryModel();
             QString qstr = compte;

             querymodel->setQuery("SELECT solde FROM clients WHERE compte = '"+ qstr +"' ");
//             ui -> tableView  ->setModel(querymodel);
             QSqlQuery query1;
             int ancienSolde;
             for(int i =0 ; i < querymodel->rowCount(); i++){
                  ancienSolde = querymodel->record(i).value("solde").toInt();
                  qDebug() << ancienSolde;
             }
             ancienSolde = ancienSolde + montant;
             query1.prepare("UPDATE clients SET solde =  :ancienSolde WHERE compte = :compte ");
             query1.bindValue(":ancienSolde", ancienSolde);
             query1.bindValue(":compte", compte);
             if(query1.exec()){
                 QMessageBox::information(this,"Update","Update reussi");
             }
         }else{
             qDebug() << compte;
             QMessageBox::warning(this,"Inserted","Error");
         }

    }else{
        QMessageBox::warning(this,"Retrait","Failed");
    }
}

void versement::on_supprimer_clicked()
{
    QString date, compte, montant;
    QSqlQuery query;
    date = ui -> date -> text();
    compte = ui -> numComptes -> text();
    montant = ui -> montant -> text();
    query.prepare("DELETE FROM versement WHERE compte = :compte AND dateVersement = :date AND montantVersement = :montant");
    query.bindValue(":montant",montant);
     query.bindValue(":compte",compte);
     query.bindValue(":date",date);
     if(query.exec()){
         QMessageBox::information(this,"Suppression","Suppression Reussi");
     }
}

void versement::on_affiche_clicked()
{
    myDataBase =  QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte;
    compte = ui -> numAffiche ->text();
    if(myDataBase.open()){
        querymodel = new QSqlQueryModel();
        querymodel->setQuery("SELECT compte,montantVersement,dateVersement FROM versement WHERE compte = '"+compte +"' ");
        ui -> tableView ->setModel(querymodel);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QSqlQuery query;
        int row_count(0);
        query.exec("SELECT COUNT(*) FROM versement WHERE compte = '"+ compte +"' ");
        if(query.first()){
            row_count = query.value(0).toInt();
            qDebug() << row_count;
        }
        qDebug() << row_count;
        ui -> number -> setText(QString::number(row_count));

    }else{
        QMessageBox::warning(this,"Affiche","Afficahge echouer");
    }
}

void versement::on_modifier_clicked()
{
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte,date;
    int montant;
    compte= ui -> numComptes -> text();
    montant = ui -> montant -> text().toInt();
    date = ui -> date -> text();
    if(myDataBase.open()){
        querymodel = new QSqlQueryModel();
        queryupdatemodel = new QSqlQueryModel;
        QString qstr = compte;
        querymodel->setQuery("SELECT solde FROM clients WHERE compte = '"+ qstr +"' ");
        int ancienSolde;
        for(int i =0 ; i < querymodel->rowCount(); i++){
             ancienSolde = querymodel->record(i).value("solde").toInt();
             qDebug() << ancienSolde;
        }
        QString qstr1 = compte;
        queryupdatemodel->setQuery("SELECT montantVersement FROM versement WHERE compte ='"+ qstr1 +"' AND dateVersement = '"+ date +"' ");
        int ancienVersement;
        QString qstrupdate = compte;
        for(int i =0 ; i < queryupdatemodel->rowCount(); i++){
             ancienVersement = queryupdatemodel->record(i).value("montantVersement").toInt();
             qDebug() << ancienVersement;
        }
        QSqlQuery query1,query2;
        int nouvelleSolde;
        nouvelleSolde = ancienSolde - ancienVersement + montant;
        query2.prepare("UPDATE clients SET solde = :nouvelleSolde WHERE compte = :compte");
        query2.bindValue(":compte", compte);
        query2.bindValue(":nouvelleSolde", nouvelleSolde);
        if(query2.exec()){
            QMessageBox::information(this,"SOLDE","Le solde est mis a jour");
        }else{
          QMessageBox::warning(this,"SOLDE","Erreur du mise a jour du Solde ");
        }
        query1.prepare("UPDATE versement SET montantVersement = :montant WHERE compte = :compte AND dateVersement  = :date");
        query1.bindValue(":montant", montant);
        query1.bindValue(":compte", compte);
        query1.bindValue(":date", date);
        if(query1.exec()){
            QMessageBox::information(this,"Update","Update reussi");

        }
        else{
            qDebug() << compte;
            QMessageBox::warning(this,"Update","Error");
        }
    }

    else{
        QMessageBox::information(this,"DB","echec de l' ouverture");
    }
}

void versement::on_back_clicked()
{
    hide();
    c = new comptes(this);
    c->show();
}

void versement::on_actualiser_clicked()
{
    myDataBase =  QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte;
    compte = ui -> numAffiche ->text();
    if(myDataBase.open()){
        querymodel = new QSqlQueryModel();
        querymodel->setQuery("SELECT compte,montantVersement,dateVersement FROM versement WHERE compte = '"+compte +"' ");
        ui -> tableView ->setModel(querymodel);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QSqlQuery query;
        int row_count(0);
        query.exec("SELECT COUNT(*) FROM versement WHERE compte = '"+ compte +"' ");
        if(query.first()){
            row_count = query.value(0).toInt();
            qDebug() << row_count;
        }
        qDebug() << row_count;
        ui -> number -> setText(QString::number(row_count));

    }else{
        QMessageBox::warning(this,"Affiche","Afficahge echouer");
    }
}

void versement::on_tableView_doubleClicked(const QModelIndex &index)
{
    QVariant compte= index.sibling(index.row(),0).data();
    QVariant montant = index.sibling(index.row(),1).data();
    QVariant date = index.sibling(index.row(),2).data();
    ui->montant->setText(montant.toString());
    ui->numComptes->setText(compte.toString());
    ui->date->setText(date.toString());
}

void versement::on_modifierDate_clicked()
{
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte,date;
    int montant;
    compte= ui -> numComptes -> text();
    montant = ui -> montant -> text().toInt();
    date = ui -> date -> text();
    if(myDataBase.open()){
        QSqlQuery query1;
        query1.prepare("UPDATE versement SET dateVersement = :date WHERE compte = :compte AND montantVersement  = :montant");
        query1.bindValue(":montant", montant);
        query1.bindValue(":compte", compte);
        query1.bindValue(":date", date);
        if(query1.exec()){
            QMessageBox::information(this,"Update","Update reussi");

        }
        else{
            qDebug() << compte;
            QMessageBox::warning(this,"Update","Error");
        }
    }

    else{
        QMessageBox::information(this,"DB","echec de l' ouverture");
    }
}
