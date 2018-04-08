#include "etcview.h"
#include <QKeyEvent>
#include <QVBoxlayout>
#include <QDebug>


etcView::etcView()
{

	initWidget();
	initConnect();
}

etcView::~etcView()
{

}

void etcView::initConnect()
{
	//connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
	//connect(btn_Snapshout, &QPushButton::clicked, camera, &etcCamera::onBtnSnapshot);
	//connect(btn_Snapshout, SIGNAL(QPushButton::clicked), camera, SLOT(etcCamera::onBtnSnapshot));
}

void etcView::initWidget()
{
	this->resize(1920, 1015);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene;  //背景地图
	scene->setSceneRect(0, 0, 1920, 1015);
	scene->setBackgroundBrush(QPixmap("./background.png").scaled(1920, 1015));

	etcCar*car1 = new etcCar;  //车辆 
	scene->addItem(car1);
	car1->setPos(50, 50);

	this->setScene(scene);//添加背景地图

	lab_CurrentTime = new QLabel(this);  //时间
	lab_CurrentTime->setText("Current Time is:" +
		QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
	lab_CurrentTime->move(0, 10);

	btn_SerialPort = new QPushButton(this);  //串口
	btn_SerialPort->setText("串口");
	btn_SerialPort->move(1812, 715);
	btn_SerialPort->resize(100, 75);

	btn_Dbmanger = new QPushButton(this);  //数据库
	btn_Dbmanger->setText("数据");
	btn_Dbmanger->move(1812, 790);
	btn_Dbmanger->resize(100, 75);

	btn_Charge = new QPushButton(this);  //收费
	btn_Charge->setText("收费");
	btn_Charge->move(1812, 865);
	btn_Charge->resize(100, 75);

	btn_Snapshout = new QPushButton(this);  //拍照按钮
	btn_Snapshout->setText("拍照");
	btn_Snapshout->move(1812, 940);
	btn_Snapshout->resize(100, 75);


	etcCamera *camera = new etcCamera(this); //相机
	camera->move(1410, 715);
	camera->setWindowFlags(Qt::FramelessWindowHint);

	connect(btn_Snapshout, &QPushButton::clicked, camera, &etcCamera::onBtnSnapshot);

	timer = new  QTimer;  //运动
	timer->start(100);

	//QPropertyAnimation*animation = new QPropertyAnimation(car1, "rotation"); //动画
	//animation->setDuration(10000);
	//animation->setStartValue(0);
	//animation->setEndValue(1800);
	//animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void etcView::onBtnSnapshot()
{
	qDebug() << "xsaxsaxsa";
}