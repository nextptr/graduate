#ifndef ETCCAR_H
#define ETCCAR_H

#include <QGraphicsObject>
#include <QGraphicsSceneHoverEvent>

class etcCar : public QGraphicsObject
{
	Q_OBJECT

public:
	etcCar();
	void advance(int phase);
	QRectF boundingRect()const; //»­Í¼ÇøÓò
	void paint(QPainter*painter, const QStyleOptionGraphicsItem*option, QWidget*widget);//»­Í¼·½·¨
	void etcCar::hoverEnterEvent(QGraphicsSceneHoverEvent*);
private:
	
};

#endif // ECAR_H
