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
	QRectF boundingRect()const; //��ͼ����
	void paint(QPainter*painter, const QStyleOptionGraphicsItem*option, QWidget*widget);//��ͼ����
	void etcCar::hoverEnterEvent(QGraphicsSceneHoverEvent*);
private:
	
};

#endif // ECAR_H
