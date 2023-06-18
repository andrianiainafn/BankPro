#ifndef RETRAIT_H
#define RETRAIT_H
#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
namespace Ui {
class retrait;
}

class retrait : public QMainWindow
{
    Q_OBJECT

public:
    explicit retrait(QWidget *parent = nullptr);
    ~retrait();

private slots:
    void on_retirer_clicked();

    void on_supprimer_clicked();

    void on_afficheRetrait_clicked();

    void on_modifier_clicked();

    void on_back_clicked();

    void on_actualiser_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_modifierDate_clicked();

private:
    Ui::retrait *ui;
    QSqlDatabase myDataBase;
    QSqlQueryModel *querymodel,*queryupdatemodel;
};

#endif // RETRAIT_H
