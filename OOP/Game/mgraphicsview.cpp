#include "mgraphicsview.h"
#include <QDebug>
#include <QScreen>
#include <QApplication>

MGraphicsView::MGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignCenter);
    this->setDragMode(DragMode::ScrollHandDrag);

    scene = new QGraphicsScene();
    this->setScene(scene);

    setMouseTracking(true);
}

MGraphicsView::~MGraphicsView(){}

void MGraphicsView::update(QPixmap pixmap){
    foreach (QGraphicsItem *item, scene->items()) {
        if(typeid (*item) == typeid (QGraphicsPixmapItem))
            scene->removeItem(item);
    }
    scene->addPixmap(pixmap);
}

void MGraphicsView::mousePressEvent(QMouseEvent *event){
    QPoint point = mapToScene(event->pos()).toPoint();
    pressed.x = point.x();
    pressed.y = point.y();
    released.x = point.x();
    released.y = point.y();
    emit square_clicked(pressed.x, pressed.y);
}

void MGraphicsView::mouseMoveEvent(QMouseEvent *event){

}

void MGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    QPoint point = mapToScene(event->pos()).toPoint();
    released.x = point.x();
    released.y = point.y();
    if(event->button() == Qt::RightButton){
        emit level_up(pressed.x, pressed.y, released.x, released.y);
        return;
    }
    emit hero_event(pressed.x, pressed.y, released.x, released.y);
}

void MGraphicsView::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        return;
    }
    QPoint point = mapToScene(event->pos()).toPoint();
    emit add_hero(point.x(), point.y());
}
