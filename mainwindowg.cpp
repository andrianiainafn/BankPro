#include "mainwindowg.h"
#include "ui_mainwindowg.h"

MainWindowG::MainWindowG(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowG)
{
    ui->setupUi(this);
}

MainWindowG::~MainWindowG()
{
    delete ui;
}
