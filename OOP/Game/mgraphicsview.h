#ifndef MGRAPHICSVIEW_H
#define MGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QMouseEvent>

#include "config.h"


typedef struct{
    int x = 0;
    int y = 0;
} coordinate;

class MGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    coordinate pressed;
    coordinate released;

    explicit MGraphicsView(QWidget *parent = nullptr);
    void update(QPixmap);
    ~MGraphicsView();

signals:
    void hero_event(int, int, int, int);
    void square_clicked(int, int);
    void add_hero(int, int);
    void level_up(int, int, int, int);

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QGraphicsScene *scene;
    QGraphicsItemGroup *item;
};

#endif // MGRAPHICSVIEW_H
