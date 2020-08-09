#ifndef INITIAL_H
#define INITIAL_H

#include <QDialog>
#include "config.h"

namespace Ui {
class Initial;
}

class Initial : public QDialog
{
    Q_OBJECT

public:
    explicit Initial(Config *conf, QWidget *parent = nullptr);
    ~Initial();


private slots:
    void on_Okey_clicked();

private:
    Ui::Initial *ui;
    Config *conf = nullptr;
};

#endif // INITIAL_H
