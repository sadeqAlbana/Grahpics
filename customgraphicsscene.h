#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomGraphicsScene(QObject *parent=0);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};

#endif // CUSTOMGRAPHICSSCENE_H
