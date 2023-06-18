#ifndef MYCOMPTES_H
#define MYCOMPTES_H

#include <QDialog>
#include "secondewindow.h"

namespace Ui {
class mycomptes;
}

class mycomptes : public QDialog
{
    Q_OBJECT

public:
    explicit mycomptes(QWidget *parent = nullptr);
    ~mycomptes();

private slots:
    void on_retrait_clicked();

private:
    Ui::mycomptes *ui;
};

#endif // MYCOMPTES_H
