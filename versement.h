#ifndef VERSEMENT_H
#define VERSEMENT_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
namespace Ui {
class versement;
}

class versement : public QMainWindow
{
    Q_OBJECT

public:
    explicit versement(QWidget *parent = nullptr);
    ~versement();

private slots:
    void on_verser_clicked();

    void on_supprimer_clicked();

    void on_affiche_clicked();

    void on_modifier_clicked();

    void on_back_clicked();

    void on_actualiser_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_modifierDate_clicked();

private:
    Ui::versement *ui;
    QSqlDatabase myDataBase;
    QSqlQueryModel *querymodel,*queryupdatemodel;
};

#endif // VERSEMENT_H
