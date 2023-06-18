#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit_password->setPlaceholderText("Entrer votre mots de passe");
    ui->lineEdit_username->setPlaceholderText("Entrer votre nom d' utilisateur");
    setFixedSize(667,401);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    myDataBase =  QSqlDatabase::addDatabase("QSQLITE");
    myDataBase.setDatabaseName("D:/Briefing/Projetqt/db.sqlite");
    QString username,password;
    username = ui -> lineEdit_username -> text();
    password = ui -> lineEdit_password -> text();
    if(myDataBase.open()){
         QSqlQuery query;
         query.prepare("SELECT * FROM admins   WHERE  username = :username AND password = :password");
         query.bindValue(":username",username);
         query.bindValue(":password",password);
         if(!query.exec()){
//            QMessageBox::information(this,"Query","Failed");
             QMessageBox::warning(this,"Sign IN ","Verifier votre mots de passe ou username ");         }
         else{
             bool test(true);
            while(query.next()){
                test = false;
                QString passwordFromDb,usernameFromDb;
                usernameFromDb = query.value(1).toString();
                passwordFromDb = query.value(2).toString();
                if(usernameFromDb == username && passwordFromDb == password){
                         QMessageBox::information(this,"Login","user name and password is correcte");
                         hide();
                         secondeWindow = new secondewindow(this);
                         secondeWindow->show();
                }
                else {
                    QMessageBox::warning(this,"Login","Username and password is not correcte ");

                }
            }
            if(test){
                 QMessageBox::warning(this,"Login","Username and password is not correcte ");
            }
         }
    }else
    {
        QMessageBox::warning(this,"Login","Failed");
    }
//    query.prepare("SELECT * FROM admins WHERE username='"+ username +"' AND password='"+  password +"'");
//    if(!query.exec()){
//         QMessageBox::warning(this,"Login","Username and password is not correcte ");
//    }
//    else{
//      query.exec("CREATE TABLE IF NOT EXISTS TEST (testtt VARCHAR(255),num INTEGER)");
//    }



//    if(qry.exec("SELECT * FROM admins WHERE username='"+ username +"' AND password='"+  password +"'")){
//           QMessageBox::information(this,"Login","user name and password is correcte");
//            hide();
//            secondeWindow = new secondewindow(this);
//            secondeWindow->show();
//    }
//    else{
//              QMessageBox::warning(this,"Login","Username and password is not correcte ");
//    }
}
