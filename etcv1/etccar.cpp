#include "etccar.h"
#include <QPainter>
#include <QDebug>
#include <QCursor>

static int mypos = 1;

etcCar::etcCar()
{
	setAcceptHoverEvents(true);
}

void etcCar::advance(int phase)
{
	if (!phase)
	{
		return;
	}
	mypos += 10;
	if (mypos < 1700)
	{
		moveBy(10, 0);
	}
	else if (mypos < 2500)
	{
		moveBy(0, 10);
	}
	else if (mypos < 4200)
	{
		moveBy(-10, 0);
	}
	else if (mypos < 5000)
	{
		moveBy(0, -10);
	}
	else if (mypos > 5000)
	{
		mypos = 1;
	}
}

QRectF etcCar::boundingRect() const
{
	return QRectF(-10 - 0.5, -10 - 0.5, 50 + 1, 50 + 1);
}

void etcCar::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setBrush(Qt::red);
	painter->drawRect(-10, -10, 51, 51);
}

void etcCar::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
	setCursor(Qt::OpenHandCursor);
	setToolTip("i am car");
}
