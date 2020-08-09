#include <QPalette>
#include <QApplication>

#include "mainwindow.h"
#include "initial.h"
#include "config.h"
#include "gamefield.h"
#include "mgraphicsview.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Config conf;

    MainWindow w(&conf);
    w.setCursor(Qt::PointingHandCursor);
    w.setWindowTitle("Game");
    w.setMinimumWidth(575);
    w.setMinimumHeight(350);
    w.setGeometry(200,200,750,575);
    w.setStyleSheet("background-color:rgb(204,204,204);");
    w.showMaximized();

    Initial *in = new Initial(&conf);
    in->setStyleSheet("background-color:rgb(102,51,102);");
    in->setFixedSize(350,175);
    in->exec();
    if(in->result()==1){
        delete in;
        w.del_Pict();
        w.create_field();
    }

    return a.exec();
}
