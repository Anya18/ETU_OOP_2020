#include "heroselect.h"
#include "ui_heroselect.h"

HeroSelect::HeroSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HeroSelect)
{
    ui->setupUi(this);

    QRect rect(0,0,95,95);
    QRegion region(rect, QRegion::Ellipse);

    ui->unit_1->setFixedHeight(100);
    ui->unit_1->setFixedWidth(100);
    ui->unit_1->setMask(region);

    ui->unit_2->setFixedHeight(100);
    ui->unit_2->setFixedWidth(100);
    ui->unit_2->setMask(region);

    ui->unit_3->setFixedHeight(100);
    ui->unit_3->setFixedWidth(100);
    ui->unit_3->setMask(region);

}

HeroSelect::~HeroSelect()
{
    delete ui;
}

void HeroSelect::on_unit_1_clicked()
{
    done(1);
}

void HeroSelect::on_unit_2_clicked()
{
    done(2);
}

void HeroSelect::on_unit_3_clicked()
{
    done(3);
}
