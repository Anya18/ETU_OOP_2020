#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initial.h"
#include "logging.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(Config *conf, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), conf(conf)
{

    ui->setupUi(this);

    ui->menubar->setStyleSheet("background-color:rgb(153,0,51);");

    view = new MGraphicsView;//(ui->frame);
    ui->field_layout->addWidget(view);

    QPixmap myPix("../image.png");
    lab = new QLabel(this);
    lab->setScaledContents(true);
    lab->setPixmap(myPix);
    double pixWidth = myPix.width();
    double layoutWidth = ui->frame->geometry().width();
    double factor = layoutWidth/pixWidth;
    QRect rect = QApplication::desktop()->screenGeometry();
    lab->setFixedWidth(rect.width());
    lab->setFixedHeight(rect.height());
//    lab->setFixedWidth(factor * lab->pixmap()->width()*19);
//    lab->setFixedHeight(factor * lab->pixmap()->height()*18);

    ui->label_1->setText("Количество героев игрока 1:");
    ui->label_2->setText("Количество героев игрока 2:");
    QPalette palette = ui->heros_1->palette();
    palette.setColor(palette.WindowText, QColor(0, 0, 0));
    palette.setColor(palette.Background, QColor(0, 0, 0));
    palette.setColor(palette.Light, QColor(0, 0, 0));
    palette.setColor(palette.Dark, QColor(0, 0, 0));
    ui->heros_1->setPalette(palette);
    ui->heros_2->setPalette(palette);


    connect(view, SIGNAL(hero_event(int, int, int, int)), this, SLOT(hero_event(int, int, int, int)));
    connect(view, SIGNAL(square_clicked(int, int)), this, SLOT(start_light(int, int)));
    connect(view, SIGNAL(add_hero(int, int)), this, SLOT(add_hero(int, int)));
    connect(view, SIGNAL(level_up(int, int, int, int)), this, SLOT(level_up(int, int, int, int)));
}

void MainWindow::del_Pict(){
    lab->deleteLater();
}

void MainWindow::create_field(){
    game = new Gamefield(conf);
    view->update(game->getMap());
    ui->heros_1->display(game->count_hero_base1());
    ui->heros_2->display(game->count_hero_base2());
}

void MainWindow::change_heros1_count(int count){
    ui->heros_1->display(count);
}

void MainWindow::change_heros2_count(int count){
    ui->heros_2->display(count);
}

void MainWindow::hero_event(int start_x, int start_y, int finish_x, int finish_y){
    if(start_x < 0 || start_y < 0 || start_x > conf->get_x()*50-1 || start_y > conf->get_y()*50-1){
        return;
    }
    if(finish_x < 0 || finish_y < 0 || finish_x > conf->get_x()*50-1 || finish_y > conf->get_y()*50-1){
        return;
    }
    game->hero_event(start_x, start_y, finish_x, finish_y);
    view->update(game->getMap());
    ui->heros_1->display(game->count_hero_base1());
    ui->heros_2->display(game->count_hero_base2());
    show_info();
    lose();
}

void MainWindow::start_light(int x, int y){
    ui->statusbar->clearMessage();
    if(x < 0 || y < 0 || x > conf->get_x()*50-1 || y > conf->get_y()*50-1){
        game->del_light();
    }else{
        game->start_light(x, y);
    }
    view->update(game->getMap());
    show_info();
}

void MainWindow::add_hero(int x, int y){
    ui->statusbar->clearMessage();
    if(x < 0 || y < 0 || x > conf->get_x()*50-1 || y > conf->get_y()*50-1){
        return;
    }
    HeroSelect *select = new HeroSelect;
    select->setStyleSheet("background-color:rgb(102,51,102);");
    select->setFixedSize(350,175);
    select->exec();
    game->add_hero(select->result(), x, y);
    view->update(game->getMap());
    ui->heros_1->display(game->count_hero_base1());
    ui->heros_2->display(game->count_hero_base2());
    show_info();
}
void MainWindow::level_up(int start_x, int start_y, int finish_x, int finish_y){
    if(start_x < 0 || start_y < 0 || start_x > conf->get_x()*50-1 || start_y > conf->get_y()*50-1){
        return;
    }
    if(finish_x < 0 || finish_y < 0 || finish_x > conf->get_x()*50-1 || finish_y > conf->get_y()*50-1){
        return;
    }
    bool flag = game->hero_level_up(start_x, start_y, finish_x, finish_y);
    if(flag == true){
        ui->statusbar->showMessage("Уровень героя увеличен", 5000);
        view->update(game->getMap());
    }
}

void MainWindow::show_info(){
    std::string *s = game->show_info();
    if(s == nullptr)
        return;
    ui->statusbar->showMessage(QString::fromStdString(*s));
}

void::MainWindow::lose(){
    if(game->lose() <= 0 || game->lose() > 2){
        return;
    }
    if(game->lose() == 1){
        Logging::user_log("№1 проиграл");
    }
    if(game->lose() == 2){
        Logging::user_log("№2 проиграл");
    }

    ui->field_layout->removeWidget(view);
    view = new MGraphicsView;
    ui->field_layout->addWidget(view);

    connect(view, SIGNAL(hero_event(int, int, int, int)), this, SLOT(hero_event(int, int, int, int)));
    connect(view, SIGNAL(square_clicked(int, int)), this, SLOT(start_light(int, int)));
    connect(view, SIGNAL(add_hero(int, int)), this, SLOT(add_hero(int, int)));
    connect(view, SIGNAL(level_up(int, int, int, int)), this, SLOT(level_up(int, int, int, int)));

    QPixmap myPix("../image.png");
    lab = new QLabel(this);
    lab->setScaledContents(true);
    lab->setPixmap(myPix);
    QRect rect = QApplication::desktop()->screenGeometry();
    lab->setFixedWidth(rect.width());
    lab->setFixedHeight(rect.height());
    lab->show();

    Final f(game->lose());
    f.setStyleSheet("background-color:rgb(102,51,102);");
    f.setFixedSize(350,175);
    f.exec();
    if(f.result() == 1){
        Initial *in = new Initial(conf);
        in->setStyleSheet("background-color:rgb(102,51,102);");
        in->setFixedSize(350,175);
        in->exec();
        if(in->result()==1){
            delete in;
            del_Pict();
            create_field();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_new_game_triggered()
{
    ui->field_layout->removeWidget(view);
    view = new MGraphicsView;
    ui->field_layout->addWidget(view);

    connect(view, SIGNAL(hero_event(int, int, int, int)), this, SLOT(hero_event(int, int, int, int)));
    connect(view, SIGNAL(square_clicked(int, int)), this, SLOT(start_light(int, int)));
    connect(view, SIGNAL(add_hero(int, int)), this, SLOT(add_hero(int, int)));
    connect(view, SIGNAL(level_up(int, int, int, int)), this, SLOT(level_up(int, int, int, int)));

    QPixmap myPix("../image.png");
    lab = new QLabel(this);
    lab->setScaledContents(true);
    lab->setPixmap(myPix);
    QRect rect = QApplication::desktop()->screenGeometry();
    lab->setFixedWidth(rect.width());
    lab->setFixedHeight(rect.height());
    lab->show();

    Initial *in = new Initial(conf);
    in->setStyleSheet("background-color:rgb(102,51,102);");
    in->setFixedSize(350,175);
    in->exec();
    if(in->result()==1){
        delete in;
        del_Pict();
        create_field();
    }
}

void MainWindow::on_actionAbout_author_triggered()
{
    Author *a = new Author;
    a->setStyleSheet("background-color:rgb(102,51,102);");
    a->setFixedSize(350,175);
    a->exec();
}

void MainWindow::on_actionRules_triggered()
{
    Rules* r = new Rules;
    r->setStyleSheet("background-color:rgb(102,51,102);");
    r->setFixedSize(650,375);
    r->exec();
}
