#include "final.h"
#include "ui_final.h"

#include <string>
#include <QString>

Final::Final(int type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Final)
{
    ui->setupUi(this);

    std::string s;
    s.append("Игрок №");
    s.append(std::to_string(type));
    s.append(" проиграл. Все его герои убиты. \nИгра окончена!");
    ui->label->setText(QString::fromStdString(s));
    ui->label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

}

Final::~Final()
{
    delete ui;
}

void Final::on_pushButton_clicked()
{
    done(1);
}
