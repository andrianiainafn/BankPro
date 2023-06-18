#include <QVector>
#include "comptes.h"
#include "ui_comptes.h"
#include <QMessageBox>
#include "secondewindow.h"
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLegend>
#include <QtCharts/QCategoryAxis>

QT_CHARTS_USE_NAMESPACE
secondewindow *com;
comptes::comptes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::comptes)
{
    ui->setupUi(this);
    ui->datef->setPlaceholderText("Entrer la date finale");
    ui->datei->setPlaceholderText("Entrer la date initiale");
    ui-> searchClients->setPlaceholderText("Votre numero ici SVP");
    ui->histogramme->setPlaceholderText("Entrer une annee pour afficher l' histogramme");
    setFixedSize(1116,640);
}

comptes::~comptes()
{
    delete ui;
}

void comptes::on_retrait_clicked()
{
    hide();
    soldeRetrait = new retrait(this);
    soldeRetrait->show();
}

void comptes::on_versement_clicked()
{
    hide();
    soldeVersement = new versement(this);
    soldeVersement->show();
}


void comptes::on_search_clicked()
{
    myDataBase =  QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString compte,date1,date2,soldeAffiche,nameAffiche ;
    compte = ui -> searchClients-> text();
    date1 = ui -> datei -> text();
    date2 = ui -> datef -> text();
    if(myDataBase.open()){
        QSqlQuery query,secondequery,debitquery,creditquery;
        QSqlQuery fquery;
        int row_countV(0),row_countR(0),ligne(0);
       //affichade appropos du clients
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

        ui->soldeAffiche->setText(soldeAffiche);
        ui->nameAfiiche->setText(nameAffiche);
        ui->compteAffiche->setText(compte);
        //Afficahge de nombre de Versement
        query.exec("SELECT COUNT(*) FROM versement WHERE   compte  = '"+ compte +"' AND (dateVersement >= '"+ date1 +"' AND dateVersement <= '"+ date2 +"')");
        if(query.first()){
              row_countV = query.value(0).toInt();
              qDebug()  << row_countV;
        }

        ui->numberVersement->setText(QString::number(row_countV));

        //Afficahge du nombre de Retrait
        secondequery.exec("SELECT COUNT(*) FROM retrait WHERE compte = '"+ compte+"' AND (dateRetrait >  '"+ date1+ "' AND  dateRetrait < '"+ date2 +"')");
        if(secondequery.first()){
            row_countR = secondequery.value(0).toInt();
//            qDebug()  << row_countR;
        }
        ui->numberRetrait->setText(QString::number(row_countR));

        //Calcule  de debit
        int sommedebit(0);
        debitquery.exec("SELECT montantVersement  FROM versement WHERE compte  = '"+ compte +"' AND (dateVersement >  '"+ date1 +"' AND dateVersement <  '"+ date2 +"')");
        while (debitquery.next()) {
                sommedebit = sommedebit + debitquery.value(0).toInt();
//                qDebug() << sommedebit;
        }
        ui->debitTotal->setText(QString::number(sommedebit)+ " Ariary");

        //Calcule de credit
        int sommecredit(0);
        creditquery.exec("SELECT motantRetrait FROM retrait WHERE compte = '"+ compte +"' AND (dateRetrait > '"+ date1 +"' AND dateRetrait <  '"+ date2 +"')");
        while(creditquery.next()){
            sommecredit = sommecredit + creditquery.value(0).toInt();
        }
        ui->creditTotal->setText(QString::number(sommecredit) + " Ariary");
        if(sommedebit<sommecredit){
            ui->alerte->setText("ATTENTION VOUS AVEZ FAIT BEAUCOUP DE RETRAIT QUE DE VERSEMENT");
        }
        //Affichage des retrait et versement entre deux date
        ligne= row_countR+row_countV;
        int row(0);
        int j(0);
        model=new QStandardItemModel(ligne,4);
        query.exec("SELECT montantVersement,dateVersement  FROM versement WHERE compte  = '"+ compte +"' AND (dateVersement >'"+ date1 +"' AND dateVersement <'"+ date2 +"')");
        while(query.next()){
             for (int i=1;i<4;i+=2) {
                 QStandardItem *item=new QStandardItem(query.value(j).toString());
                 model->setItem(row,i,item);
                 j++;
                }
             j=0;
             row++;
         }
       QSqlQuery query1;
       query1.exec("SELECT cheque,motantRetrait,dateRetrait FROM retrait WHERE compte = '"+ compte +"' AND (dateRetrait > '"+date1 +"' AND dateRetrait < '"+ date2 +"')");
       while(query1.next()){
           for (int i=0;i<4;i++) {
               if(i!=1){
                   QStandardItem *item=new QStandardItem(query1.value(j).toString());
                   model->setItem(row,i,item);
                    j++;
               }
              }
           j=0;
           row++;
       }
         model->setHeaderData(0,Qt::Horizontal,"Cheque");
          model->setHeaderData(1,Qt::Horizontal,"montantVersment");
           model->setHeaderData(2,Qt::Horizontal,"montantRetrait");
            model->setHeaderData(3,Qt::Horizontal,"Date");
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableView->setModel(model);
    }else{
        QMessageBox::warning(this,"DATABASE","Data Base can' t open");
    }
    QSqlQuery query;
}

void comptes::on_transferer_clicked()
{
  hide();
  soldeTransfert = new transfert();
  soldeTransfert->show();
}

void comptes::on_back_clicked()
{
    hide();
    com = new secondewindow(this);
    com->show();
}

void comptes::on_download_clicked()
{
  myDataBase =  QSqlDatabase::addDatabase("QSQLITE");
  myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
  QString annee,comptes,debutDebit,finDebit,fin,debut;
  QSqlQuery query,queryc;
  comptes = ui->searchClients->text();
  annee = ui->histogramme->text();;
//             ui -> tableView  ->setModel(querymodel);
  int newdebit(0);
  int newcredit(0);
   QVector<int>listDebit;
   QVector<int>listCredit;
   QString u;
   fin = "-31";
   debut ="-01";
 if(myDataBase.open()){
     for (int i = 1;i<=12;i++) {
              u = QString::number(i);
                if(i<10){
                    debutDebit = annee + '-' + '0' + u + debut;
                    finDebit = annee + '-' + '0' + u + fin;
                }else{
                    debutDebit = annee + '-'  + u + debut;
                    finDebit = annee + '-'  + u + fin;
                }
                queryc.prepare("SELECT SUM(motantRetrait) FROM retrait WHERE compte = '"+comptes+"' AND dateRetrait >= '"+debutDebit+"' AND dateRetrait <= '"+finDebit+"' ");
               if(queryc.exec()){
                   if(queryc.first()){
                       newcredit = queryc.value(0).toInt();
//                        qDebug()<<newcredit;
                       listCredit.push_back(newcredit);
                   }
               }else{
                   QMessageBox::warning(this,"CREDIT","ERROR");
               }
               query.prepare("SELECT SUM(montantVersement) FROM versement WHERE compte = '"+comptes+"' AND dateVersement >= '"+debutDebit+"' AND dateVersement <= '"+finDebit+"' ");
              if(query.exec()){
                  if(query.first()){
                      newdebit = query.value(0).toInt();
    //                  qDebug()<<newdebit;
                      listDebit.push_back(newdebit);
                  }
              }else{
                  QMessageBox::warning(this,"DEBIT","ERROR");
              }

     }
  //    hide();
      QLineSeries *series = new QLineSeries();
      series->append(0,0);
      for(int i=0;i < listDebit.length();i++){
//         qDebug()<< listDebit[i];
          series->append(i+1,listDebit[i]);
      }
      QLineSeries *credit = new QLineSeries();
      credit->append(0,0);
      for(int i =0;i<listCredit.length();i++){
          qDebug() << listCredit[i];
          credit->append(i+1,listCredit[i]);
      }

      QChart *chart;
      chart = new QChart;
      chart->legend()->hide();
      chart->addSeries(series);
      chart->addSeries(credit);
      chart->createDefaultAxes();
      QFont font;
      font.setPixelSize(18);
      chart->setFont(font);
      chart->setTitleBrush(QBrush(Qt::black));
      chart->setTitle("Les Debits(jaune) et credits(Rouge) en un an");
      QPen pen(QRgb(0xfdb157));
      QPen pen2(QRgb(0xff0000));
      pen.setWidth(3);
      pen2.setWidth(3);
      credit->setPen(pen2);
      series->setPen(pen);
      chart->setAnimationOptions(QChart::AllAnimations);
      QCategoryAxis *axeX = new QCategoryAxis();
      axeX->append("Janvier",1);
      axeX->append("Fevrier",2);
      axeX->append("Mars",3);
      axeX->append("Avril",4);
      axeX->append("Mai",5);
      axeX->append("Juin",6);
      axeX->append("Juillet",7);
      axeX->append("Aout",8);
      axeX->append("Septembre",9);
      axeX->append("Octobre",10);
      axeX->append("Novembre",11);
      axeX->append("Decembre",12);
      chart->setAxisX(axeX,series);
      QChartView *chartview = new QChartView(chart);
      chartview->setRenderHint(QPainter::Antialiasing);
       histo = new  histogramme(this);
      histo->setCentralWidget(chartview);
      histo->show();
 }else{
     QMessageBox::warning(this,"DB","Error");
 }
}
