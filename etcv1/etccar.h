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
	etcCar(QString pixmapDir, QString carname, QString username, int flag);
	QPainterPath shape();
	//void advance(int phase);
	QRectF boundingRect()const; //画图区域
	void paint(QPainter*painter, const QStyleOptionGraphicsItem*option, QWidget*widget);//画图方法
	void etcCar::hoverEnterEvent(QGraphicsSceneHoverEvent*);
	int clock;         //根据clock改变车值辆状态
	int activeFlag;    //防止碰撞,用于排队
	bool resetFlag;     //车辆重新启动标志      
public:
	QString pixmapstr; //车辆贴图
	QString CarNumber; //车牌
	QString userName; //用户名
	int carflag;    //车辆代号	
	int money;      //车辆余额 
protected:
	//void mousePressEvent(QGraphicsSceneMouseEvent*myevent);
	
};

#endif // ECAR_H
