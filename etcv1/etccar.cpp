#include "etccar.h"
#include <QPainter>
#include <QDebug>
#include <QCursor>

static int mypos = 1;

etcCar::etcCar(QString pixmapDir, QString carname, QString username,int myflag)
	: carflag(myflag)
	, activeFlag(0)
	, CarNumber(carname)
	, userName(username)
{
	clock = 0;
	pixmapstr = pixmapDir;
	resetFlag = false;
	//setFlags(QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);
	saveImg = "";
}

QPainterPath etcCar::shape()
{
	QPainterPath path;
	path.addRect(-25, -25, 50, 50);
	return path;
}

//void etcCar::advance(int phase)
//{
//	if (!phase)
//	{
//		return;
//	}
//	clock++;
//	if (clock == 1)
//	{
//		if (carflag == 1)
//		{
//			setRotation(-135);
//		}
//	}
//	if (clock == 2)
//	{
//		if (carflag == 1)
//		{
//			setRotation(-180);
//		}
//	}	
//	if (clock == 3)
//	{
//		if (carflag == 1)
//		{
//			setRotation(-240);
//		}
//	}
//	if (clock == 4)
//	{
//		if (carflag == 1)
//		{
//			setRotation(90);
//		}
//	}
//	//mypos += 10;
//	//if (mypos < 1700)
//	//{
//	//	moveBy(10, 0);
//	//}
//	//else if (mypos < 2500)
//	//{
//	//	moveBy(0, 10);
//	//}
//	//else if (mypos < 4200)
//	//{
//	//	moveBy(-10, 0);
//	//}
//	//else if (mypos < 5000)
//	//{
//	//	moveBy(0, -10);
//	//}
//	//else if (mypos > 5000)
//	//{
//	//	mypos = 1;
//	//}
//}

QRectF etcCar::boundingRect() const
{
	return QRectF(-25 - 0.5, -25 - 0.5, 50 + 1, 50 + 1);
}

void etcCar::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPixmap pix(pixmapstr);
	painter->drawPixmap(-25, -25, pix);
}

void etcCar::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
	setCursor(Qt::OpenHandCursor);
	setToolTip(CarNumber);
}

//void etcCar::mousePressEvent(QGraphicsSceneMouseEvent *myevent)
//{
//	emit carFlag(carflag);
//}
