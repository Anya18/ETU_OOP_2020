#include "initial.h"
#include "ui_initial.h"

Initial::Initial(Config *conf, QWidget *parent) :
    QDialog(parent), ui(new Ui::Initial), conf(conf)
{
    ui->setupUi(this);
    ui->spinBox_x->setMinimum(5);
    ui->spinBox_y->setMinimum(5);
}

Initial::~Initial()
{
    delete ui;
}

void Initial::on_Okey_clicked()
{
    conf->set_x(ui->spinBox_x->value());
    conf->set_y(ui->spinBox_y->value());
    done(1);
}

