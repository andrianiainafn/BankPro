#include "premierclasse.h"
#include "ui_premierclasse.h"
#include "QTableView"
#include<QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "secondewindow.h"

secondewindow *sec;
premierclasse::premierclasse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::premierclasse)
{
    ui->setupUi(this);
    ui->montant->setPlaceholderText("Entrer le montant");
    ui->compte->setPlaceholderText("Entrer votre numero de compte");
    ui->lineEdit_lastname->setPlaceholderText("Entrer votre nom");
    ui->lineEdit_4->setPlaceholderText("Entrer le numero de compte");
    setFixedSize(1142,640);
   // affichageDonneClient();

    openDatbase();
   // vrai_connexionBD();
}

premierclasse::~premierclasse()
{
    delete ui;
}

void premierclasse::on_pushButton_clicked()
{


  QString lastname= ui->lineEdit_lastname->text();
  QString compte= ui->compte->text();
  QString montant= ui->montant->text();

      QSqlQuery requete;
      qDebug()<<lastname;

      if(lastname!=""&& montant!=""){
          if(!estDejaClient()){
              requete.prepare("INSERT INTO clients(name,compte,solde) "
                              "VALUES(:name,:compte,:solde)");
              requete.bindValue(":name",lastname);
              requete.bindValue(":compte",compte);
              requete.bindValue(":solde",montant);
              if(requete.exec()){

               }else{
                QMessageBox::warning(this,"INsertion","Error");
               }
          } else
          {
               QMessageBox::warning(this,"Message","Client dejà dans la base de donné");
          }


      }else{
            QMessageBox::warning(this,"Attention","veuiller completer convenablement tout les champs");
      }



     // requete.exec();
      /*if(requete.exec())
      {
           QMessageBox::warning(this,"Message","Data inserted succefully");

      }*/
  viderChamp();

  //QMessageBox::warning(this,"Message de Bienvenu","Tongasoa "+firstName+" "+lastname+", vous avez Ar "+montant+" dans votre compte "+compte);

}
void premierclasse::openDatbase(){
    QSqlDatabase m_bd = QSqlDatabase::addDatabase("QSQLITE");
    m_bd.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    if(m_bd.open()){
        QMessageBox::information(this,"DB","reussi");
    }else{
        QMessageBox::warning(this,"DB","echec");
    }
}
void premierclasse::affichageDonneClient()
{

   QSqlQuery req;
   int ligne(0); int row(0);
   req.exec("SELECT count(*) from clients");
   while (req.next()) {
       ligne= req.value(0).toInt();
   }
   modele = new QStandardItemModel(ligne,3);
   req.exec("SELECT name,compte,solde FROM clients");
   while(req.next()){
       for (int j=0; j<3 ;j++) {
           QStandardItem *item= new QStandardItem(req.value(j).toString());
           modele->setItem(row,j,item);
       }
       row++;
   }
   modele->setHeaderData(0,Qt::Horizontal,"Nom");
   modele->setHeaderData(1,Qt::Horizontal,"N° compte");
   modele->setHeaderData(2,Qt::Horizontal,"Solde");
   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// equally stretch each columns
   ui->tableView->setModel(modele);
   QSqlQuery query;
   int row_count(0);
   query.exec("SELECT COUNT(*) FROM clients  ");
   if(query.first()){
       row_count = query.value(0).toInt();
   }
   ui->totaleclient->setText(QString::number(row_count));
}

void premierclasse::on_pushButton_5_clicked()
{
    affichageDonneClient();
    viderChamp();

}

void premierclasse::on_pushButton_2_clicked()
{
      modifie_donne_client();
      viderChamp();
}
bool premierclasse::estDejaClient(){
    QString compte = ui->compte->text();
     //QMessageBox::warning(this,"Message",compte);
    QSqlQuery query;

    query.exec("SELECT compte FROM clients where compte='"+compte+"'");
    while(query.next()){

             return true;
        }
    return  false;
}

void premierclasse::modifie_donne_client()
{
    QString lastname= ui->lineEdit_lastname->text();
    QString newName= lastname;
    QString compte =ui->compte->text();

    QSqlQuery query;

    query.exec(" UPDATE clients SET name='"+newName+"' where compte='"+compte+"'  ");
    viderChamp();


}

void premierclasse::on_pushButton_4_clicked()
{
    QString compte,nameAffiche,soldeAffiche;
    compte = ui->lineEdit_4->text();
    model = new QSqlQueryModel();
    model->setQuery("SELECT name,compte,solde FROM clients WHERE compte='"+compte+"'");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// equally stretch each columns
    QSqlQuery fquery;
    fquery.prepare("SELECT * FROM clients WHERE compte = '"+ compte +"'");
    if(fquery.exec()){
       while(fquery.next()){
           nameAffiche = fquery.value(1).toString();
            soldeAffiche = fquery.value(2).toString();
       }
    }
    else{
        QMessageBox::warning(this,"Affiche","Erreur");
    }
    ui->montant->setText(soldeAffiche);
    ui->lineEdit_lastname->setText(nameAffiche);
    ui->compte->setText(compte);

}
void premierclasse::viderChamp(){
    ui->lineEdit_lastname->setText("");
    ui->compte->setText("");
    ui->montant->setText("");
}
void premierclasse::on_pushButton_3_clicked()
{
     QString compte =ui->compte->text();
     QSqlQuery query;

     query.prepare("DELETE  FROM clients WHERE compte='"+compte+"'");{
         if(query.exec()){
                  viderChamp();
         }else{
             QMessageBox::warning(this,"Suppression","Error");
         }
     }
}
void premierclasse::on_precedent_clicked()
{
    hide();
    sec = new secondewindow(this);
    sec->show();
}

void premierclasse::on_tableView_doubleClicked(const QModelIndex &index)
{

    QVariant Nom = index.sibling(index.row(),0).data();
    QVariant compte= index.sibling(index.row(),1).data();
    QVariant solde = index.sibling(index.row(),2).data();
    ui->lineEdit_lastname->setText(Nom.toString());
    ui->compte->setText(compte.toString());
    ui->montant->setText(solde.toString());
}

void premierclasse::on_toutModifier_clicked()
{
    QString lastname= ui->lineEdit_lastname->text();
    QString newName= lastname;
    QString compte =ui->compte->text();
    QString montant =ui->montant->text();

    QSqlQuery query;

    query.exec(" UPDATE clients SET compte='"+compte+"',solde='"+montant+"'  WHERE name='"+newName+"'  ");
    viderChamp();
}

