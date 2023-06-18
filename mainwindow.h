#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "secondewindow.h"
#include "login.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_seConnecter_clicked();

    void on_inscrire_clicked();

private:
    Ui::MainWindow *ui;
     QSqlDatabase myDataBase;
    secondewindow *secondeWindow;
    Login *myLogin;
};
#endif // MAINWINDOW_H
