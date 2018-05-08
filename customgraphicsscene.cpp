#include "customgraphicsscene.h"
#include <QDebug>
CustomGraphicsScene::CustomGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{

}

void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<mouseEvent->scenePos();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
