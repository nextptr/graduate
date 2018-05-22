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
//虚拟小车移动
void etcView::AutoMove(etcCar*carNum)
{
	//QPropertyAnimation*animation = new QPropertyAnimation(smartCar1, "rotation"); //动画
	//animation->setDuration(1000);
	//animation->setStartValue(0);
	//animation->setEndValue(180);
	//animation->start(QAbstractAnimation::DeleteWhenStopped);

	carNum->setRotation(-90);


	QPropertyAnimation*G_anima0 = new QPropertyAnimation(carNum, "pos"); //动画
	G_anima0->setDuration(5000-320*(carNum->activeFlag));            //根据不同的排队情况，决定不同的用时
	G_anima0->setStartValue(QPointF(1350, 78));
	G_anima0->setEndValue(QPointF(570+ 60*(carNum->activeFlag), 78));//根据不同的排队情况，决定不同的终点
	
	//车辆到达收费站
	animalArive(G_anima0, carNum);

	QPropertyAnimation*G_animaPark = new QPropertyAnimation(carNum, "pos");    //动画
	G_animaPark->setDuration(10 + (2600+320) * (carNum->activeFlag));          //根据不同的排队情况，决定不同的用时
	G_animaPark->setKeyValueAt(0, QPointF(570 + 60 * (carNum->activeFlag), 78));
	if (carNum->activeFlag == 1)
	{
		G_animaPark->setKeyValueAt(0.547, QPointF(630, 78));
		G_animaPark->setKeyValueAt(0.657, QPointF(570,78));
	}
	if (carNum->activeFlag == 2)
	{
		G_animaPark->setKeyValueAt(0.328, QPointF(690, 78));
		G_animaPark->setKeyValueAt(0.383, QPointF(630, 78));
		G_animaPark->setKeyValueAt(0.719, QPointF(630, 78));
		G_animaPark->setKeyValueAt(0.774, QPointF(570, 78));
	}
	if (carNum->activeFlag == 3)
	{
		G_animaPark->setKeyValueAt(0.2257, QPointF(750, 78));
		G_animaPark->setKeyValueAt(0.292, QPointF(690, 78));
		G_animaPark->setKeyValueAt(0.516, QPointF(690, 78));
		G_animaPark->setKeyValueAt(0.5525, QPointF(630, 78));
		G_animaPark->setKeyValueAt(0.776, QPointF(630, 78));
		G_animaPark->setKeyValueAt(0.8127, QPointF(570, 78));
	}
	G_animaPark->setKeyValueAt(1, QPointF(570,78));

	QPropertyAnimation*P_animBrakeBarUp1 = new QPropertyAnimation(brakeBarIn, "geometry"); //抬杆
	P_animBrakeBarUp1->setDuration(2600);
	P_animBrakeBarUp1->setKeyValueAt(0, QRect(468, 62, 4, 8));
	P_animBrakeBarUp1->setKeyValueAt(0.38, QRect(468, 62, 4, 38));//抬起
	P_animBrakeBarUp1->setKeyValueAt(0.8, QRect(468, 62, 4, 38)); //等车通过
	P_animBrakeBarUp1->setKeyValueAt(1, QRect(468, 62, 4, 8));    //放下

	QPropertyAnimation*P_anima1 = new QPropertyAnimation(carNum, "pos"); //动画
	P_anima1->setDuration(2600);
	P_anima1->setKeyValueAt(0, QPointF(570, 78));
	P_anima1->setKeyValueAt(0.38, QPointF(570, 78));
	P_anima1->setKeyValueAt(1, QPointF(325, 78));

	QParallelAnimationGroup *P_GroupAnima1 = new QParallelAnimationGroup;
	P_GroupAnima1->addAnimation(P_animBrakeBarUp1);
	P_GroupAnima1->addAnimation(P_anima1);

	animalClock(P_anima1, carNum);  //为车辆添加动画
	
	QPropertyAnimation*G_anima1 = new QPropertyAnimation(carNum, "pos"); //动画
	G_anima1->setDuration(4000);
	G_anima1->setStartValue(QPointF(325, 93));
	G_anima1->setEndValue(QPointF(145, 248));
	animalClock(G_anima1, carNum);

	QPropertyAnimation*G_anima2 = new QPropertyAnimation(carNum, "pos"); //动画
	G_anima2->setDuration(4000);
	G_anima2->setStartValue(QPointF(145, 248));
	G_anima2->setEndValue(QPointF(145, 715));
	animalClock(G_anima2, carNum);

	QPropertyAnimation*G_anima3 = new QPropertyAnimation(carNum, "pos"); //动画
	G_anima3->setDuration(4000);
	G_anima3->setStartValue(QPointF(145, 715));
	G_anima3->setEndValue(QPointF(270, 800));

	//到达收费站
	animalArive(G_anima3, carNum);

	QPropertyAnimation*P_animaBrakeBarUp2 = new QPropertyAnimation(brakeBarOut, "geometry"); //抬杆
	P_animaBrakeBarUp2->setDuration(2600);
	P_animaBrakeBarUp2->setKeyValueAt(0, QRect(350, 845, 30, 30));
	P_animaBrakeBarUp2->setKeyValueAt(0.38, QRect(373, 815, 1, 1));//抬起
	P_animaBrakeBarUp2->setKeyValueAt(0.8, QRect(373, 815, 1, 1));
	P_animaBrakeBarUp2->setKeyValueAt(1, QRect(350, 845, 30, 30));

	QPropertyAnimation*P_anima2 = new QPropertyAnimation(carNum, "pos"); //动画
	P_anima2->setDuration(2600);
	P_anima2->setKeyValueAt(0, QPointF(270, 800));
	P_anima2->setKeyValueAt(0.38, QPointF(270, 800));
	P_anima2->setKeyValueAt(1, QPointF(470, 940));

	QParallelAnimationGroup *P_GroupAnima2 = new QParallelAnimationGroup;
	P_GroupAnima2->addAnimation(P_animaBrakeBarUp2);
	P_GroupAnima2->addAnimation(P_anima2);

	animalClock(P_anima2, carNum);

	QPropertyAnimation*G_anima4 = new QPropertyAnimation(carNum, "pos"); //动画
	G_anima4->setDuration(6000);
	G_anima4->setStartValue(QPointF(470, 940));
	G_anima4->setEndValue(QPointF(1350, 940));
	animalClock(G_anima4, carNum);

	QPropertyAnimation*G_anima5 = new QPropertyAnimation(carNum, "pos"); //动画
	G_anima5->setDuration(10);
	G_anima5->setStartValue(QPointF(1350, 940));
	if (carNum->carflag == 1)
	{
		G_anima5->setEndValue(QPointF(1640, 70));
	}
	if (carNum->carflag == 2)
	{
		G_anima5->setEndValue(QPointF(1700, 70));
	}
	if (carNum->carflag == 3)
	{
		G_anima5->setEndValue(QPointF(1760, 70));
	}
	if (carNum->carflag == 4)
	{
		G_anima5->setEndValue(QPointF(1820, 70));
	}
	animalClock(G_anima5, carNum);

	QSequentialAnimationGroup* group = new QSequentialAnimationGroup;
	group->addAnimation(G_anima0);
	group->addAnimation(G_animaPark);
	group->addAnimation(P_GroupAnima1);
	group->addAnimation(G_anima1);
	group->addAnimation(G_anima2);
	group->addAnimation(G_anima3);
	group->addAnimation(P_GroupAnima2);
	group->addAnimation(G_anima4);
	group->addAnimation(G_anima5);
	group->start();
	
}
//虚拟小车转弯
void etcView::AutoRota(etcCar*CarNum)
{
	if (1 == CarNum->clock)
	{
		park--;
		CarNum->setRotation(-130);
	}
	if (2 == CarNum->clock)
	{
		CarNum->setRotation(-180);
	}
	if (3 == CarNum->clock)
	{
		CarNum->setRotation(-240);
	}
	if (4 == CarNum->clock)
	{
		CarNum->setRotation(90);
	}
	if (5 == CarNum->clock)
	{
		CarNum->setRotation(0);
	}
	if (6 == CarNum->clock)
	{
		CarNum->clock = 0;
		CarNum->resetFlag = false;
		//park = 0;
	}
}

void etcView::animalClock(QPropertyAnimation*animation, etcCar * carNum)
{
	if (carNum == smartCar1)
	{
		connect(animation, &QPropertyAnimation::finished, this, &etcView::car1Clock);
	}
	if (carNum == smartCar2)
	{
		connect(animation, &QPropertyAnimation::finished, this, &etcView::car2Clock);
	}
	if (carNum == smartCar3)
	{
		connect(animation, &QPropertyAnimation::finished, this, &etcView::car3Clock);
	}
	if (carNum == smartCar4)
	{
		connect(animation, &QPropertyAnimation::finished, this, &etcView::car4Clock);
	}
}
void etcView::animalArive(QPropertyAnimation * animation, etcCar * carNum)
{
	if (carNum == smartCar1)
	{
		connect(animation, &QPropertyAnimation::finished, this, &etcView::car1Arive);
	}
	if (carNum == smartCar2)
	{
		connect(animation, &QPropertyAnimation::finished, this, &etcView::car2Arive);
	}
	if (carNum == smartCar3)
	{
		connect(animation, &QPropertyAnimation::finished, this, &etcView::car3Arive);
	}
	if (carNum == smartCar4)
	{
		connect(animation, &QPropertyAnimation::finished, this, &etcView::car4Arive);
	}
}

void etcView::car1Clock()
{
	smartCar1->clock++;
	emit carRota(smartCar1);
}
void etcView::car2Clock()
{
	smartCar2->clock++;
	emit carRota(smartCar2);
}
void etcView::car3Clock()
{
	smartCar3->clock++;
	emit carRota(smartCar3);
}
void etcView::car4Clock()
{
	smartCar4->clock++;
	emit carRota(smartCar4);
}

void etcView::car1Arive()
{
	emit carCharge(smartCar1);
}
void etcView::car2Arive()
{
	emit carCharge(smartCar2);
}
void etcView::car3Arive()
{
	emit carCharge(smartCar3);
}
void etcView::car4Arive()
{
	emit carCharge(smartCar4);
}
//到达ETC收费和抓拍
void etcView::arriveStation(etcCar*m_pcar)
{
	if (0 == m_pcar->clock) //到达
	{
		etcRecord mOption;
		mOption.DetectionTime = QDate::currentDate().toString("yyyy - MM - dd");
		mOption.StationId = "001";
		mOption.PlateNumber = m_pcar->CarNumber;
		mOption.UserName = m_pcar->userName;
		mOption.Result = "正常";
		mOption.Direction = "进入";
		mOption.Money = QString::number(m_pcar->money, 10);
		mOption.Remark = "仿真ETC通行";
		//DBManager::getInstance()->insertinspectRecord(&mOption);
	
	}
	if (3 == m_pcar->clock)  //离开
	{
		chargeRecord tmpRecord;
		tmpRecord.PlateNumber = m_pcar->CarNumber;
		tmpRecord.UserName = m_pcar->userName;
		tmpRecord.Time = QDate::currentDate().toString("yyyy - MM - dd");
		tmpRecord.Payout = QString::number(30, 10);
		if ((m_pcar->money - 30) < 30)
		{
			tmpRecord.Income = QString::number(100, 10);
			tmpRecord.Balance = QString::number(m_pcar->money +70, 10);
			m_pcar->money = 70 + m_pcar->money ;
		}
		else
		{
			tmpRecord.Income = QString::number(0, 10);
			tmpRecord.Balance = QString::number(m_pcar->money - 30, 10);
			m_pcar->money = m_pcar->money - 30;
		}
		tmpRecord.Remark = "仿真ETC收费";
		//DBManager::getInstance()->insertChargeRecord(&tmpRecord);

		labCarnum2->setText(m_pcar->CarNumber);
		labUsername2->setText(m_pcar->userName);
		labBalance2->setText(QString::number(m_pcar->money, 10));
		labDirection2->setText("离开");
		labCharge->setText("30");

		emit etcPicture(m_pcar);
	}
	
}

void etcView::onBtnSnapshot()
{
	qDebug() << "xsaxsaxsa";
}
void etcView::EtcClock()
{
	lab_CurrentTime->setText("当前时间:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
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
	park = -1;
	lastClickTime = new QTime;
	nowClickTime = new QTime;
	initWidget();
	initConnect();
	initConfig();
}
etcView::~etcView()
{

}
//虚拟小车启动
void etcView::mousePressEvent(QMouseEvent * myevent)
{
	QPoint viewPos = myevent->pos();
	labpos->setText("当前坐标x:" + QString::number(viewPos.x() - 25, 10) + " y:" + QString::number(viewPos.y() - 25, 10));
	if (park<0)//是否第一次点击
	{
		*lastClickTime = QTime::currentTime();
		park++;  //park==0
	}
	else//点击是否属于有效区域
	{
		if (viewPos.y() > 55 && viewPos.y() < 105)
		{
			if ((viewPos.x() > 1625 && viewPos.x() < 1675)|| (viewPos.x() > 1685 && viewPos.x() < 1735)\
				|| (viewPos.x() > 1745 && viewPos.x() < 1795)|| (viewPos.x() > 1805 && viewPos.x() < 1855))
			{
				*nowClickTime = QTime::currentTime();
				if (lastClickTime->msecsTo(*nowClickTime) < 2600)
				{
					park++;
				}
				*lastClickTime = *nowClickTime;
			}
		}
	}
	if (viewPos.y() > 55 && viewPos.y() < 105)
	{
		if (viewPos.x() > 1625 && viewPos.x() < 1675)
		{
			if (!smartCar1->resetFlag)
			{
				smartCar1->resetFlag = true;
				smartCar1->activeFlag = park;
				emit carFlag(smartCar1);
			}
		}
		if (viewPos.x() > 1685 && viewPos.x() < 1735)
		{
			if (!smartCar2->resetFlag)
			{
				smartCar2->resetFlag = true;
				smartCar2->activeFlag = park;
				emit carFlag(smartCar2);
			}
		}
		if (viewPos.x() > 1745 && viewPos.x() < 1795)
		{
			if (!smartCar3->resetFlag)
			{
				smartCar3->resetFlag = true;
				smartCar3->activeFlag = park;
				emit carFlag(smartCar3);
			}
		}
		if (viewPos.x() > 1805 && viewPos.x() < 1855)
		{
			if (!smartCar4->resetFlag)
			{
				smartCar4->resetFlag = true;
				smartCar4->activeFlag = park;
				emit carFlag(smartCar4);
			}
		}
	}
}
void etcView::initConnect()
{
	connect(timer, &QTimer::timeout, this, &etcView::EtcClock);
	connect(this, &etcView::carFlag, this, &etcView::AutoMove);
	connect(this, &etcView::carRota, this, &etcView::AutoRota);
	connect(this, &etcView::carCharge, this, &etcView::arriveStation);

}
void etcView::initConfig()
{
	{
		/*QLabel *carlab1 = new QLabel(this);
		carlab1->move(400, 160);
		carlab1->setFixedWidth(60);
		carlab1->setText("车牌号");
		QLabel *carlab2 = new QLabel(this);
		carlab2->move(400, 180);
		carlab2->setFixedWidth(60);
		carlab2->setText("用户名");
		QLabel *carlab3 = new QLabel(this);
		carlab3->move(400, 200);
		carlab3->setFixedWidth(60);
		carlab3->setText("余额");
		QLabel *carlab4 = new QLabel(this);
		carlab4->move(400, 220);
		carlab4->setFixedWidth(60);
		carlab4->setText("方向");*/

		//labCarnum1 = new QLabel(this);
		//labUsername1 = new QLabel(this);
		//labBalance1 = new QLabel(this);
		//labDirection1 = new QLabel(this);
		/*labCarnum1->setFixedWidth(60);
		labUsername1->setFixedWidth(60);
		labBalance1->setFixedWidth(60);
		labDirection1->setFixedWidth(60);
		labCarnum1->move(460, 160);
		labUsername1->move(460, 180);
		labBalance1->move(460, 200);
		labDirection1->move(460, 220);*/

	}
	
	{
		QLabel *carlab5 = new QLabel(this);
		carlab5->move(170, 870);
		carlab5->setFixedWidth(60);
		carlab5->setText("车牌号");
		QLabel *carlab6 = new QLabel(this);
		carlab6->move(170, 890);
		carlab6->setFixedWidth(60);
		carlab6->setText("用户名");
		QLabel *carlab7 = new QLabel(this);
		carlab7->move(170, 910);
		carlab7->setFixedWidth(60);
		carlab7->setText("缴费");
		QLabel *carlab8 = new QLabel(this);
		carlab8->move(170, 930);
		carlab8->setFixedWidth(60);
		carlab8->setText("余额");
		QLabel *carlab9 = new QLabel(this);
		carlab9->move(170, 950);
		carlab9->setFixedWidth(60);
		carlab9->setText("方向");
		labCarnum2 = new QLabel(this);
		labUsername2 = new QLabel(this);
		labBalance2 = new QLabel(this);
		labDirection2 = new QLabel(this);
		labCharge = new QLabel(this);
		labCarnum2->setFixedWidth(60);
		labUsername2->setFixedWidth(60);
		labBalance2->setFixedWidth(60);
		labDirection2->setFixedWidth(60);
		labCharge->setFixedWidth(60);
		labCarnum2->move(230, 870);
		labUsername2->move(230, 890);
		labCharge->move(230, 910);
		labBalance2->move(230, 930);
		labDirection2->move(230, 950);
	}
		
	DBManager::getInstance()->initCarBalance(smartCar1);
	DBManager::getInstance()->initCarBalance(smartCar2);
	DBManager::getInstance()->initCarBalance(smartCar3);
	DBManager::getInstance()->initCarBalance(smartCar4);
}
void etcView::initWidget()
{
	this->resize(1920, 1015);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene;  //背景地图
	scene->setSceneRect(0, 0, 1920, 1015);
	scene->setBackgroundBrush(QPixmap("./background.png").scaled(1920, 1015));

	smartCar1 = new etcCar("./Resources/img/car1.png", "新X051","zjw",1);  //车辆 
	smartCar1->money = 50;
	scene->addItem(smartCar1);
	smartCar1->setPos(1640, 70);

	smartCar2 = new etcCar("./Resources/img/car2.png", "川F022","zfy",2);  //车辆 
	smartCar2->money = 170;
	scene->addItem(smartCar2);
	smartCar2->setPos(1700, 70);

	smartCar3 = new etcCar("./Resources/img/car3.png", "浙J486","ycg",3);  //车辆 
	smartCar3->money = 500;
	scene->addItem(smartCar3);
	smartCar3->setPos(1760, 70);

	smartCar4 = new etcCar("./Resources/img/car4.png", "琼C531","xql",4);  //车辆 
	smartCar4->money = 300;
	scene->addItem(smartCar4);
	smartCar4->setPos(1820, 70);

	brakeBarIn = new QLabel(this);
	QPixmap labmap = QPixmap("./Resources/img/labBack.png"); //进入闸杆
	brakeBarIn->setPixmap(labmap);
	brakeBarIn->move(1800, 330);
	
	brakeBarOut = new QLabel(this);
	QPixmap brakeBarmap = QPixmap("./Resources/img/bakerbar.png"); //离开闸杆
	brakeBarOut->setPixmap(brakeBarmap);
	brakeBarOut->move(350, 845);

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
	connect(this, &etcView::etcPicture, camera, &etcCamera::onCameraSave);


	timer = new  QTimer;  //时钟
	timer->start(1000);

	//QPropertyAnimation*G_anima2 = new QPropertyAnimation(smartCar1, "pos"); //动画
	//G_anima2->setDuration(1000);
	//G_anima2->setStartValue(QPointF(1350, 65));
	//G_anima2->setEndValue(QPointF(400, 65));
	//G_anima2->start();

	//QPropertyAnimation*animation = new QPropertyAnimation(smartCar1, "rotation"); //动画
	//animation->setDuration(5000);
	//animation->setStartValue(-5);
	//animation->setEndValue(90);
	//animation->start(QAbstractAnimation::DeleteWhenStopped);
}
