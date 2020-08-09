#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>

#include "config.h"
#include "gamefield.h"
#include "mgraphicsview.h"
#include "heroselect.h"
#include "final.h"
#include "author.h"
#include "rules.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Config *conf, QWidget *parent = nullptr);
    ~MainWindow();
    void del_Pict();
    void create_field();
    void change_heros1_count(int count);
    void change_heros2_count(int count);
    void lose();

private slots:
    void hero_event(int, int, int, int);
    void start_light(int, int);
    void add_hero(int, int);
    void level_up(int, int, int, int);

    void on_new_game_triggered();

    void on_actionAbout_author_triggered();

    void on_actionRules_triggered();

private:
    Ui::MainWindow *ui;
    Gamefield *game = nullptr;
    MGraphicsView *view = nullptr;
    QLabel *lab = nullptr;
    Config *conf = nullptr;

    void show_info();
};
#endif // MAINWINDOW_H
