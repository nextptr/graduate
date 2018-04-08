#ifndef ETCVIEW_H
#define ETCVIEW_H
#pragma execution_character_set("utf-8")  

#include "etccar.h"
#include "etccamera.h"

#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QVBoxlayout>


class etcView : public QGraphicsView
{
	Q_OBJECT
public Q_SLOTS:
	void onBtnSnapshot();
public:
	etcView();
	~etcView();

	QPushButton*btn_Snapshout;  //拍照
	QPushButton*btn_SerialPort;  //串口
	QPushButton*btn_Dbmanger;  //数据库
	QPushButton*btn_Charge;  //收费
private:
	void initWidget();
	void initConnect();
	QVBoxLayout *p_Vlayout;
	etcCamera *camera;
	QGraphicsScene *scene;  //背景地图
	QTimer* timer;  //计时器
	QLabel*lab_CurrentTime;  //显示时间
	QLabel*lab_Background;  //背景信息 ETC拍照系统
};

#endif // ETCVIEW_H
