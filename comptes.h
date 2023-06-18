#ifndef COMPTES_H
#define COMPTES_H

#include <QMainWindow>
#include "retrait.h"
#include "versement.h"
#include <histogramme.h>
#include "transfert.h"
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QStandardItemModel>
namespace Ui {
class comptes;
}

class comptes : public QMainWindow
{
    Q_OBJECT

public:
    explicit comptes(QWidget *parent = nullptr);
    ~comptes();

private slots:
    void on_retrait_clicked();

    void on_versement_clicked();

    void on_search_clicked();

    void on_transferer_clicked();

    void on_back_clicked();

    void on_download_clicked();

private:
    Ui::comptes *ui;
    QSqlDatabase myDataBase;
    QSqlQueryModel *querymodel,*queryupdatemodel;
    retrait *soldeRetrait;
    versement *soldeVersement;
    histogramme *histo;
    transfert *soldeTransfert;
    QStandardItemModel *model;
};

#endif // COMPTES_H
