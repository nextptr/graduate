#include "etcview.h"
#include <QKeyEvent>
#include <QVBoxlayout>
#include <QDebug>
#include <QPixmap>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>


void etcView::PositonSlot(pocket pok)
{
	if (pok.roadnam == 'L')
	{
		if (pok.roadid == '1')
		{
			switch (pok.roidpos)
			{
			case 1:
			{
				lab1->setPixmap(QPixmap("./Resources/anidog01.jpg"));
				lab1->move(1400, 65);
				lab1->resize(50, 50);
				lab1->show();
				qDebug() << " get 1 ";
			}break;
			case 2:
			{
				lab2->setPixmap(QPixmap("./Resources/anidog02.jpg"));
				lab2->move(1250, 65);
				lab2->resize(50, 50);
				lab2->show();
				qDebug() << " get 2 ";
			}break;
			case 3:
			{
				lab3->setPixmap(QPixmap("./Resources/anidog03.jpg"));
				lab3->move(1100, 65);
				lab3->resize(50, 50);
				lab3->show();
				qDebug() << " get 3 ";
			}break;
			case 4:
			{
				lab4->setPixmap(QPixmap("./Resources/anidog04.jpg"));
				lab4->move(950, 65);
				lab4->resize(50, 50);
				lab4->show();
				qDebug() << " get 4 ";
			}break;
			case 5:
			{
				lab5->setPixmap(QPixmap("./Resources/anidog05.jpg"));
				lab5->move(800, 65);
				lab5->resize(50, 50);
				lab5->show();
				qDebug() << " get 5 ";
			}break;
			case 6:
			{
				lab6->setPixmap(QPixmap("./Resources/anidog06.jpg"));
				lab6->move(650, 65);
				lab6->resize(50, 50);
				lab6->show();
				qDebug() << " get 6 ";
			}break;
			}
		}
	}
}

void etcView::EtcClock()
{
	lab_CurrentTime->setText("当前时间:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
}

void etcView::AutoMove(int flag)
{
	//QPropertyAnimation*animation = new QPropertyAnimation(smartCar1, "rotation"); //动画
	//animation->setDuration(1000);
	//animation->setStartValue(0);
	//animation->setEndValue(180);
	//animation->start(QAbstractAnimation::DeleteWhenStopped);
	QPropertyAnimation*animation3 = new QPropertyAnimation(smartCar1, "pos"); //动画
	animation3->setDuration(1000);
	animation3->setStartValue(QPointF(1350, 65));
	animation3->setEndValue(QPointF(400, 65));
	animation3->start();
	if (flag == 1)
	{

		//QPropertyAnimation*animation1 = new QPropertyAnimation(smartCar1, "pos"); //动画
		//animation1->setDuration(10);
		//animation1->setStartValue(QPointF(1350, 65));
		//animation1->setEndValue(QPointF(1349, 65));

		emit carRota(1, -90);

		QPropertyAnimation*animation1 = new QPropertyAnimation(smartCar1, "pos"); //动画
		animation1->setDuration(10000);
		animation1->setStartValue(QPointF(1350, 93));
		animation1->setEndValue(QPointF(340, 93));
		
		connect(animation1, &QPropertyAnimation::finished, scene, &QGraphicsScene::advance);

		QPropertyAnimation*animation2 = new QPropertyAnimation(smartCar1, "pos"); //动画
		animation2->setDuration(10000);
		animation2->setStartValue(QPointF(340, 93));
		animation2->setEndValue(QPointF(160, 248));

		connect(animation2, &QPropertyAnimation::finished, scene, &QGraphicsScene::advance);
		QPropertyAnimation*animation3 = new QPropertyAnimation(smartCar1, "pos"); //动画
		animation3->setDuration(10000);
		animation3->setStartValue(QPointF(160, 248));
		animation3->setEndValue(QPointF(160, 707));

		connect(animation3, &QPropertyAnimation::finished, scene, &QGraphicsScene::advance);
		QPropertyAnimation*animation4 = new QPropertyAnimation(smartCar1, "pos"); //动画
		animation4->setDuration(10000);
		animation4->setStartValue(QPointF(160, 707));
		animation4->setEndValue(QPointF(470, 910));

		connect(animation4, &QPropertyAnimation::finished, scene, &QGraphicsScene::advance);
		QPropertyAnimation*animation5 = new QPropertyAnimation(smartCar1, "pos"); //动画
		animation5->setDuration(10000);
		animation5->setStartValue(QPointF(470, 910));
		animation5->setEndValue(QPointF(1350, 910));

		group = new QSequentialAnimationGroup;
		group->addAnimation(animation1);
		group->addAnimation(animation2);
		group->addAnimation(animation3);
		group->addAnimation(animation4);
		group->addAnimation(animation5);
		group->start();

		//QPropertyAnimation*animation = new QPropertyAnimation(smartCar1, "rotation"); //动画
		//animation->setDuration(100);
		//animation->setStartValue();
		//animation->setEndValue(QRect(500, 65, 50, 50));
	}
}

void etcView::AutoRota(int flag,int rota)
{
	smartCar1->setRotation(rota);

	//QPropertyAnimation*animation2 = new QPropertyAnimation(smartCar1, "rotation"); //动画
	//animation2->setDuration(10000);
	//animation2->setStartValue(0);
	//animation2->setEndValue(360);
}

etcView::etcView()
{
	lab1 = new QLabel(this);
	lab2 = new QLabel(this);
	lab3 = new QLabel(this);
	lab4 = new QLabel(this);
	lab5 = new QLabel(this);
	lab6 = new QLabel(this);
	
	lab6->show();
	initWidget();
	initConnect();
	initAnimal();
}

etcView::~etcView()
{

}

void etcView::initConnect()
{
	//connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
	connect(timer, &QTimer::timeout, this, &etcView::EtcClock);
	connect(this, &etcView::carFlag, this, &etcView::AutoMove);
	connect(this, &etcView::carRota, this, &etcView::AutoRota);
	//connect(btn_Snapshout, &QPushButton::clicked, camera, &etcCamera::onBtnSnapshot);
	//connect(btn_Snapshout, SIGNAL(QPushButton::clicked), camera, SLOT(etcCamera::onBtnSnapshot));
}

void etcView::initAnimal()
{
	
}

void etcView::mousePressEvent(QMouseEvent * myevent)
{
	QPoint viewPos = myevent->pos();
	labpos->setText("当前坐标x:" + QString::number(viewPos.x()-25, 10)+" y:" + QString::number(viewPos.y()-25, 10));

	if (viewPos.y() > 70 && viewPos.y() < 120)
	{
		if (viewPos.x() > 1640 && viewPos.x() < 1690)
		{
			emit carFlag(1);
		}
		if (viewPos.x() > 1700 && viewPos.x() < 1750)
		{
			emit carFlag(1);
		}
		if (viewPos.x() > 1760 && viewPos.x() < 1810)
		{
			emit carFlag(1);
		}
		if (viewPos.x() > 1820 && viewPos.x() < 1870)
		{
			emit carFlag(1);
		}
	}
}

void etcView::initWidget()
{
	this->resize(1920, 1015);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene;  //背景地图
	scene->setSceneRect(0, 0, 1920, 1015);
	scene->setBackgroundBrush(QPixmap("./background.png").scaled(1920, 1015));

	smartCar1 = new etcCar("./Resources/img/car1.png",1);  //车辆 
	scene->addItem(smartCar1);
	smartCar1->setPos(1640, 70);

	smartCar2 = new etcCar("./Resources/img/car2.png",1);  //车辆 
	scene->addItem(smartCar2);
	smartCar2->setPos(1700, 70);

	smartCar3 = new etcCar("./Resources/img/car3.png",1);  //车辆 
	scene->addItem(smartCar3);
	smartCar3->setPos(1760, 70);

	smartCar4 = new etcCar("./Resources/img/car4.png",1);  //车辆 
	scene->addItem(smartCar4);
	smartCar4->setPos(1820, 70);

	labpos = new QLabel(this);
	labpos->move(0, 160);
	labpos->setFixedWidth(400);
	labpos->setText("当前坐标 ");

	this->setScene(scene);//添加背景地图

	lab_CurrentTime = new QLabel(this);  //时间
	lab_CurrentTime->setText("当前时间:" +
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

	timer = new  QTimer;  //时钟
	timer->start(1000);

	//QPropertyAnimation*animation3 = new QPropertyAnimation(smartCar1, "pos"); //动画
	//animation3->setDuration(1000);
	//animation3->setStartValue(QPointF(1350, 65));
	//animation3->setEndValue(QPointF(400, 65));
	//animation3->start();

	//QPropertyAnimation*animation = new QPropertyAnimation(smartCar1, "rotation"); //动画
	//animation->setDuration(5000);
	//animation->setStartValue(-5);
	//animation->setEndValue(90);
	//animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void etcView::onBtnSnapshot()
{
	qDebug() << "xsaxsaxsa";
}