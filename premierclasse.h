#ifndef PREMIERCLASSE_H
#define PREMIERCLASSE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlQueryModel>


namespace Ui {
class premierclasse;
}

class premierclasse : public QMainWindow
{
    Q_OBJECT

public:
    explicit premierclasse(QWidget *parent = nullptr);
    ~premierclasse();

private slots:
    void on_pushButton_clicked();
    void affichageDonneClient();
    void openDatbase();
    bool estDejaClient();
    void modifie_donne_client();
    void viderChamp();


    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();


    void on_precedent_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_toutModifier_clicked();



private:
    Ui::premierclasse *ui;
    QStandardItemModel *modele;
    QSqlQueryModel *model;



};

#endif // PREMIERCLASSE_H
