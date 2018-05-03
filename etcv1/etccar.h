#ifndef ETCCAR_H
#define ETCCAR_H

#include <QGraphicsObject>
#include <QGraphicsSceneHoverEvent>

class etcCar : public QGraphicsObject
{
	Q_OBJECT
signals :
	void carFlag(int flag);
public:
	etcCar(QString pixmapDir,int flag);
	void advance(int phase);
	QRectF boundingRect()const; //»­Í¼ÇøÓò
	void paint(QPainter*painter, const QStyleOptionGraphicsItem*option, QWidget*widget);//»­Í¼·½·¨
	void etcCar::hoverEnterEvent(QGraphicsSceneHoverEvent*);
protected:
	//void mousePressEvent(QGraphicsSceneMouseEvent*myevent);
private:
	int clock;
	QString pixstr;
	int carflag;
};

#endif // ECAR_H
