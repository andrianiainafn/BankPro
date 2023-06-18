#ifndef TRANSFERT_H
#define TRANSFERT_H
#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
namespace Ui {
class transfert;
}

class transfert : public QMainWindow
{
    Q_OBJECT

public:
    explicit transfert(QWidget *parent = nullptr);
    ~transfert();

private slots:
    void on_transferer_clicked();

    void on_back_clicked();

private:
    Ui::transfert *ui;
    QSqlDatabase myDataBase;
    QSqlQueryModel *querymodel,*queryupdatemodel;
};

#endif // TRANSFERT_H
