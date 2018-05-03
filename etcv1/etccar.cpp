#include "etccar.h"
#include <QPainter>
#include <QDebug>
#include <QCursor>

static int mypos = 1;

etcCar::etcCar(QString pixmapDir,int myflag)
	:carflag(myflag)
{
	clock = 0;
	pixstr = pixmapDir;
	//setFlags(QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);
}

void etcCar::advance(int phase)
{
	if (!phase)
	{
		return;
	}
	clock++;
	if (clock == 1)
	{
		if (carflag == 1)
		{
			setRotation(-135);
		}
	}
	if (clock == 2)
	{
		if (carflag == 1)
		{
			setRotation(-180);
		}
	}	
	if (clock == 3)
	{
		if (carflag == 1)
		{
			setRotation(-240);
		}
	}
	if (clock == 4)
	{
		if (carflag == 1)
		{
			setRotation(90);
		}
	}
	//mypos += 10;
	//if (mypos < 1700)
	//{
	//	moveBy(10, 0);
	//}
	//else if (mypos < 2500)
	//{
	//	moveBy(0, 10);
	//}
	//else if (mypos < 4200)
	//{
	//	moveBy(-10, 0);
	//}
	//else if (mypos < 5000)
	//{
	//	moveBy(0, -10);
	//}
	//else if (mypos > 5000)
	//{
	//	mypos = 1;
	//}
}

QRectF etcCar::boundingRect() const
{
	return QRectF(-10 - 0.5, -10 - 0.5, 50 + 1, 50 + 1);
}

void etcCar::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPixmap pix(pixstr);
	painter->drawPixmap(-10, -10, pix);
}

void etcCar::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
	setCursor(Qt::OpenHandCursor);
	setToolTip("i am car");
}

//void etcCar::mousePressEvent(QGraphicsSceneMouseEvent *myevent)
//{
//	emit carFlag(carflag);
//}
