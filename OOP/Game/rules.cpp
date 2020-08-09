#include "rules.h"
#include "ui_rules.h"

Rules::Rules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rules)
{
    ui->setupUi(this);

    std::ifstream t("../rules.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                         std::istreambuf_iterator<char>());
    ui->textBrowser->setText(QString::fromStdString(str));
}

Rules::~Rules()
{
    delete ui;
}
