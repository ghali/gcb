
#include "MyGraphicsScene.h"

#include <QtGui>
#include "Node.h"

// public:
MyGraphicsScene::MyGraphicsScene()
    : manipulated_node(false)
{
    setSceneRect(QRectF(QPointF(-2.0,-2.0), QPointF(2.0,2.0)));
    setBackgroundBrush(Qt::black);

    // Items are defined relative to their own center (pos).

    add_node_and_dual(QPointF( 0.8, 1.0));
    add_node_and_dual(QPointF(-1.0, 0.3));
    add_node_and_dual(QPointF(-0.5,- 1.0));
}

Node * MyGraphicsScene::add_node_and_dual(const QPointF & p)
{
    QGraphicsLineItem * dual = new QGraphicsLineItem();
    addItem(dual);
    Node * node = new Node(p, dual);
    addItem(node);
    return node;
}

// protected:
void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    if(!mouseEvent->isAccepted())
    {
        manipulated_node = add_node_and_dual(mouseEvent->scenePos());
        update();
    }
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if(manipulated_node)
        sendEvent(manipulated_node, mouseEvent);
    else
        QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    manipulated_node = false;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void MyGraphicsScene::drawAxes(QPainter * painter, const QRectF & rect)
{
    painter->setPen(Qt::gray);
    painter->drawLine( QPointF(rect.left(), 0.0),
                       QPointF(rect.right(), 0.0) );

    painter->drawLine( QPointF(0.0, rect.bottom()),
                       QPointF(0.0, rect.top()) );

    painter->drawEllipse(-1,-1,2,2);
}

void MyGraphicsScene::drawBackground(QPainter * painter, const QRectF & rect)
{
    Q_UNUSED(rect);

    QGraphicsScene::drawBackground(painter, rect);
    drawAxes(painter, rect);
}
