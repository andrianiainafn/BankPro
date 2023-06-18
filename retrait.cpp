#include "retrait.h"
#include "ui_retrait.h"
#include <QMessageBox>
#include "comptes.h"
comptes *co;
retrait::retrait(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::retrait)
{
    ui->setupUi(this);
    ui -> date -> setPlaceholderText("Entrer le date de retrait");
    ui ->montant ->setPlaceholderText("Entrer le montant de retrait ");
    ui -> numCheque ->setPlaceholderText("Entrer le numero de cheque");
    ui -> numComptes -> setPlaceholderText("Entrer le numero de compte");
    ui -> compteSearch -> setPlaceholderText("Numero a chercher");
    setFixedSize(955,512);
}

retrait::~retrait()
{
    delete ui;
}

void retrait::on_retirer_clicked()
{
    myDataBase =  QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString date,compte,cheque,clientIndex;
    int montant;
    date = ui ->date -> text();
    compte = ui -> numComptes -> text();
    cheque = ui -> numCheque -> text();
    montant = ui -> montant -> text().toInt();
    clientIndex = compte;
    if(myDataBase.open()){
       QMessageBox::information(this,"dataBase","Open success");
       QSqlQuery query;
       query.prepare("INSERT INTO retrait (compte,cheque,motantRetrait,dateRetrait,clientR_compte)"
                     "VALUES(:compte,:cheque,:montant,:date,:clientIndex)");
       query.bindValue(":compte", compte);
       query.bindValue(":cheque", cheque);
       query.bindValue(":montant", montant);
       query.bindValue(":date", date);
       query.bindValue(":clientIndex",clientIndex);
       if(query.exec()){
           QMessageBox::information(this,"Retrait","Retrait reussi");
           querymodel = new QSqlQueryModel();
           querymodel->setQuery("SELECT solde FROM clients WHERE compte = '"+ compte +"' ");
           int ancienSolde;
           for (int i = 0 ; i < querymodel->rowCount();i++) {
               ancienSolde = querymodel->record(i).value("solde").toInt();
               qDebug() << ancienSolde;
           }
           ancienSolde = ancienSolde - montant;
           QSqlQuery query1;
           query1.prepare("UPDATE clients SET solde =  :ancienSolde WHERE compte = :compte ");
           query1.bindValue(":ancienSolde", ancienSolde);
           query1.bindValue(":compte", compte);
           if(query1.exec()){
               QMessageBox::information(this,"UPDATE","reussi");
           }else{
               QMessageBox::information(this,"UPDATE", "echec");
           }
       }else{
           QMessageBox::warning(this,"Retrait","Echec du retrait");
       }
    }else{
        QMessageBox::warning(this,"Retrait","Failed");
    }
}

void retrait::on_supprimer_clicked()
{
    myDataBase =  QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte,cheque,date,montant;
    compte = ui -> numComptes -> text();
    cheque = ui -> numCheque -> text();
    date = ui -> date -> text();
    montant = ui -> montant -> text();
    QSqlQuery query;
    if(myDataBase.open()){
        QMessageBox::information(this,"myDataBase","OPEN");
        query.prepare("DELETE FROM retrait WHERE compte = :compte AND cheque = :cheque AND  dateRetrait = :date AND motantRetrait = :montant ");
        query.bindValue(":compte", compte);
        query.bindValue(":cheque", cheque);
        query.bindValue(":montant", montant);
        query.bindValue(":date", date);
        if(query.exec()){
             QMessageBox::information(this,"Suppression","reussi");
        }else{
            QMessageBox::warning(this,"Suppression","Echec");
        }
    }else{
        QMessageBox::warning(this,"myDataBase","can't Open");
    }

}

void retrait::on_afficheRetrait_clicked()
{
    QString rechercher;
    rechercher = ui -> compteSearch -> text();
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    if(myDataBase.open()){
        QMessageBox::information(this,"myDataBase","OPEN");
        querymodel = new QSqlQueryModel();
        querymodel->setQuery("SELECT compte,cheque,motantRetrait,dateRetrait FROM retrait WHERE compte = '"+rechercher +"' ");
        ui -> tableView ->setModel(querymodel);
         ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QSqlQuery query;
        int row_count(0);
        query.exec("SELECT COUNT(*) FROM retrait WHERE compte = '"+ rechercher +"' ");
        if(query.first()){
            row_count = query.value(0).toInt();
        }
        qDebug() << row_count;
        ui -> listeNumber -> setText(QString::number(row_count));
    }else{
        QMessageBox::warning(this,"myDataBase","can't Open");
    }
}

void retrait::on_modifier_clicked()
{
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte,date,cheque;
    int montant;
    compte = ui -> numComptes -> text();
    cheque = ui -> numCheque -> text();
    date = ui -> date -> text();
    montant = ui -> montant -> text().toInt();
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
        queryupdatemodel->setQuery("SELECT motantRetrait FROM retrait WHERE compte ='"+ qstr1 +"' AND dateRerait =  '"+ date +"' ");
        int ancienVersement;
        QString qstrupdate = compte;
        for(int i =0 ; i < queryupdatemodel->rowCount(); i++){
             ancienVersement = queryupdatemodel->record(i).value("motantVersement").toInt();
             qDebug() << ancienVersement;
        }
        QSqlQuery query1,query2;
        int nouvelleSolde;
        nouvelleSolde = ancienSolde + ancienVersement - montant;
        query2.prepare("UPDATE clients SET solde = :nouvelleSolde WHERE compte = :compte");
        query2.bindValue(":compte", compte);
        query2.bindValue(":nouvelleSolde", nouvelleSolde);
        if(query2.exec()){
            QMessageBox::information(this,"SOLDE","Le solde est mis a jour");
        }else{
          QMessageBox::warning(this,"SOLDE","Erreur du mise a jour du Solde ");
        }
        query1.prepare("UPDATE retrait SET motantRetrait =  :montant WHERE compte = :compte AND dateRetrait  = :date AND cheque = :cheque ");
        query1.bindValue(":montant", montant);
        query1.bindValue(":compte", compte);
        query1.bindValue(":cheque", cheque);
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

void retrait::on_back_clicked()
{
    hide();
    co = new comptes(this);
    co->show();
}

void retrait::on_actualiser_clicked()
{
    QString rechercher;
    rechercher = ui -> compteSearch -> text();
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    if(myDataBase.open()){
        QMessageBox::information(this,"myDataBase","OPEN");
        querymodel = new QSqlQueryModel();
        querymodel->setQuery("SELECT compte,cheque,motantRetrait,dateRetrait FROM retrait WHERE compte = '"+rechercher +"' ");
        ui -> tableView ->setModel(querymodel);
         ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QSqlQuery query;
        int row_count(0);
        query.exec("SELECT COUNT(*) FROM retrait WHERE compte = '"+ rechercher +"' ");
        if(query.first()){
            row_count = query.value(0).toInt();
        }
        qDebug() << row_count;
        ui -> listeNumber -> setText(QString::number(row_count));
    }else{
        QMessageBox::warning(this,"myDataBase","can't Open");
    }
}

void retrait::on_tableView_doubleClicked(const QModelIndex &index)
{
    QVariant compte = index.sibling(index.row(),0).data();
    QVariant cheque= index.sibling(index.row(),1).data();
    QVariant montant = index.sibling(index.row(),2).data();
    QVariant date = index.sibling(index.row(),3).data();
    ui->montant->setText(montant.toString());
    ui->numComptes->setText(compte.toString());
    ui->date->setText(date.toString());
    ui -> numCheque -> setText(cheque.toString());

}

void retrait::on_modifierDate_clicked()
{
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte,date,cheque;
    int montant;
    compte = ui -> numComptes -> text();
    cheque = ui -> numCheque -> text();
    date = ui -> date -> text();
    montant = ui -> montant -> text().toInt();
    if(myDataBase.open()){
        QSqlQuery query1;
        query1.prepare("UPDATE retrait SET dateRetrait =  :date WHERE compte = :compte AND motantRetrait  = :montant AND cheque = :cheque ");
        query1.bindValue(":montant", montant);
        query1.bindValue(":compte", compte);
        query1.bindValue(":cheque", cheque);
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
