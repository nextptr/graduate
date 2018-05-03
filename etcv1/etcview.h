#ifndef ETCVIEW_H
#define ETCVIEW_H
#pragma execution_character_set("utf-8")  

#include "etccar.h"
#include "etccamera.h"
#include "etcconfiger.h"

#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QVBoxlayout>
#include <QLineEdit>


class etcView : public QGraphicsView
{
	Q_OBJECT
signals :
	void carFlag(int flag);
	void carRota(int flag,int rota);
public Q_SLOTS:
	void onBtnSnapshot();
	void PositonSlot(pocket);
	void EtcClock();
	void AutoMove(int flag);
	void AutoRota(int flag,int rota);
public:
	etcView();
	~etcView();

	QPushButton*btn_Snapshout;  //拍照
	QPushButton*btn_SerialPort;  //串口
	QPushButton*btn_Dbmanger;  //数据库
	QPushButton*btn_Charge;  //收费
protected:
	void mousePressEvent(QMouseEvent *myevent);
private:
	void initWidget();
	void initConnect();
	void initAnimal();
	QVBoxLayout *p_Vlayout;
	etcCamera *camera;
	etcCar*smartCar1; //小车1
	etcCar*smartCar2; //小车2
	etcCar*smartCar3; //小车3
	etcCar*smartCar4; //小车4

	QLabel *labpos;  //场景坐标
	QSequentialAnimationGroup* group;

	QLabel*lab1;
	QLabel*lab2;
	QLabel*lab3;
	QLabel*lab4;
	QLabel*lab5;
	QLabel*lab6;
	QGraphicsScene *scene;  //背景地图
	QTimer* timer;  //计时器
	QLabel*lab_CurrentTime;  //显示时间
	QLabel*lab_Background;  //背景信息 ETC拍照系统
};
#endif // ETCVIEW_H
