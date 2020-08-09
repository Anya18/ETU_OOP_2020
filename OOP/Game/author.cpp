#include "author.h"
#include "ui_author.h"

Author::Author(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Author)
{
    ui->setupUi(this);

    std::string s;
    s.append("Автор: \nСамойлова Анна Сергеевна\nстудентка группы 8303\nСПБГТУ ЛЭТИ");
    ui->label->setText(QString::fromStdString(s));
    ui->label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
}

Author::~Author()
{
    delete ui;
}
