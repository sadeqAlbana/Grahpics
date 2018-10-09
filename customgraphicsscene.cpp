#include "customgraphicsscene.h"
#include <QDebug>
CustomGraphicsScene::CustomGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{

}

void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //qDebug()<<mouseEvent->scenePos().rx();
    emit geometryChanged(mouseEvent->scenePos());

    QGraphicsScene::mouseMoveEvent(mouseEvent);

}
