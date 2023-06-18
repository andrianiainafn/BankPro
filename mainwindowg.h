#ifndef MAINWINDOWG_H
#define MAINWINDOWG_H

#include <QMainWindow>

namespace Ui {
class MainWindowG;
}

class MainWindowG : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowG(QWidget *parent = nullptr);
    ~MainWindowG();

private:
    Ui::MainWindowG *ui;
};

#endif // MAINWINDOWG_H
