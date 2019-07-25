#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QtGui>
class Node;
class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT;
public:
    MyGraphicsScene();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void drawBackground(QPainter * painter, const QRectF & rect);
    Node * add_node_and_dual(const QPointF & p);
private:
    void drawAxes(QPainter * painter, const QRectF & rect);
    Node * manipulated_node;
};

#endif // MYGRAPHICSSCENE_H
