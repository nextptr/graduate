#ifndef ETCVIEW_H
#define ETCVIEW_H
#pragma execution_character_set("utf-8")  

#include "etccar.h"
#include "etccamera.h"
#include "etcconfiger.h"
#include "dbmanger.h"

#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QVBoxlayout>
#include <QLineEdit>
#include <QDir>
#include <QPalette>
#include <QMovie>
#include <QGuiApplication>
#include <QScreen>

class etcView : public QGraphicsView
{
	Q_OBJECT
signals :
	void carFlag(etcCar*car);
	void carRota(etcCar*car);
	void carCharge(etcCar*car);
	void etcPicture(etcCar*car);
public Q_SLOTS:
	void PositonSlot(pocket);//车辆定位函数
	void EtcClock();         //系统时钟
	void AutoMove(etcCar*);  //自动驾驶函数
	void AutoRota(etcCar*);  //自动转弯函数
	void car1Clock();
	void car2Clock();
	void car3Clock();
	void car4Clock();

	void car1Arive();
	void car2Arive();
	void car3Arive();
	void car4Arive();
	void arriveStation(etcCar*); //车辆到达收费站处理函数

	void onbtn_ItcClock();

public:
	etcView();
	~etcView();
	void animalClock(QPropertyAnimation*animation,etcCar*carNum); //动画时钟
	void animalArive(QPropertyAnimation*animation, etcCar*carNum);//车辆到达收费站
	QPushButton*btn_Itc;        //Itc模式转换
	QPushButton*btn_SerialPort; //串口
	QPushButton*btn_Dbmanger;   //数据库
	QPushButton*btn_Charge;     //收费
protected:
	void mousePressEvent(QMouseEvent *myevent);
private:
	void initWidget();  //初始化窗口部件
	void initConnect(); //初始化部件间信号槽连接
	void initConfig();  //初始化参数
private:
	QVBoxLayout *p_Vlayout;
	etcCamera *camera;
	etcCar*smartCar1; //小车1
	etcCar*smartCar2; //小车2
	etcCar*smartCar3; //小车3
	etcCar*smartCar4; //小车4
	QLabel*brakeBarIn;  //闸杆
	QLabel*brakeBarOut;  //闸杆

	QLabel *labpos;       //场景坐标
	QTime* lastClickTime; //上次点击时间
	QTime* nowClickTime;  //上次点击时间
	int park;             //排队资源

	QLabel*labPositionCar;
	QMovie*PositionGif;


	QLabel*labCarnum2;
	QLabel*labUsername2;
	QLabel*labBalance2;
	QLabel*labDirection2;
	QLabel*labCharge;

	bool itcFlag;  //ITC与ETC之间的转换标识

	QScreen *screen;//截屏图片

	QGraphicsScene *scene;  //背景地图
	QTimer* timer;          //计时器


	QLabel*lab_CurrentTime; //显示时间
	QLabel*lab_Background;  //背景信息 ETC拍照系统
};
#endif // ETCVIEW_H
