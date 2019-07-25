
#include "MyGraphicsScene.h"
#include "Node.h"

const qreal W = 0.1;

Node::Node(const QPointF & pos, QGraphicsLineItem * _dual)
    : QGraphicsEllipseItem(QRectF(QPointF(-W/2,-W/2), QSizeF(W,W))),
      dual(_dual)
{
    setBrush(QBrush(Qt::cyan));
    setPen(QPen(Qt::NoPen));
    setPos(pos);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(2);

    // Node is not parent item of QGraphicsLineItem, since QGraphicsLineItem's coordinates are global.
    dual->setLine(find_dual());
    dual->setPen(QPen(Qt::white));
    dual->setFlag(QGraphicsItem::ItemStacksBehindParent);
    dual->setZValue(1);
}

QLineF Node::find_dual() const
{
    QPointF pd1, pd2;

    const QPointF pos = scenePos();

    // Point(a,b) has as dual the line: a.x + b.y = 1
    if(fabs(pos.x()) > fabs(pos.y())) { // point is closer to vertical
        pd1 = QPointF(( -1.0 + 3.0 * pos.y()) / pos.x(), -3.0);
        pd2 = QPointF(( -1.0 - 3.0 * pos.y()) / pos.x(),  3.0);
    }
    else {
        pd1 = QPointF(-3.0, ( -1.0 + 3.0 * pos.x()) / pos.y());
        pd2 = QPointF( 3.0, ( -1.0 - 3.0 * pos.x()) / pos.y());
    }

    return QLineF(pd1, pd2);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionHasChanged)
        dual->setLine(find_dual());

    return QGraphicsItem::itemChange(change, value);
}
