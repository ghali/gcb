#ifndef NODE_H
#define NODE_H

#include <QtGui>

class Node : public QGraphicsEllipseItem
{
public:
    Node(const QPointF & pos, QGraphicsLineItem * _dual);

protected:
    QLineF find_dual() const;

    QVariant itemChange(GraphicsItemChange change, const QVariant & value);

private:
    QGraphicsLineItem * dual;
};

#endif // NODE_H
