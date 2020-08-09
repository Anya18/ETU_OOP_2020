#ifndef HEROSELECT_H
#define HEROSELECT_H

#include <QDialog>

namespace Ui {
class HeroSelect;
}

class HeroSelect : public QDialog
{
    Q_OBJECT

public:
    explicit HeroSelect(QWidget *parent = nullptr);
    ~HeroSelect();

private slots:
    void on_unit_1_clicked();

    void on_unit_2_clicked();

    void on_unit_3_clicked();

private:
    Ui::HeroSelect *ui;
};

#endif // HEROSELECT_H
