#ifndef SECONDEWINDOW_H
#define SECONDEWINDOW_H

#include <QDialog>
#include "premierclasse.h"
#include "comptes.h"
namespace Ui {
class secondewindow;
}

class secondewindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondewindow(QWidget *parent = nullptr);
    ~secondewindow();
private slots:
    void on_pushButton_comptes_clicked();

    void on_pushButton_clients_clicked();

private:
    Ui::secondewindow *ui;
    comptes *clientsComptes;
    premierclasse *classepremier;
};

#endif // SECONDEWINDOW_H
