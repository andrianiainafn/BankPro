#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include <QMainWindow>

namespace Ui {
class histogramme;
}

class histogramme : public QMainWindow
{
    Q_OBJECT

public:
    explicit histogramme(QWidget *parent = nullptr);
    ~histogramme();

private:
    Ui::histogramme *ui;
};

#endif // HISTOGRAMME_H
