#ifndef MYLOGIN_H
#define MYLOGIN_H

#include <QMainWindow>

namespace Ui {
class myLogin;
}

class myLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit myLogin(QWidget *parent = nullptr);
    ~myLogin();

private:
    Ui::myLogin *ui;
};

#endif // MYLOGIN_H
