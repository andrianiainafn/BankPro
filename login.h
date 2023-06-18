#ifndef LOGIN_H
#define LOGIN_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "secondewindow.h"
#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
    QSqlDatabase myDataBase;
    secondewindow *secondeWindow;
};

#endif // LOGIN_H
