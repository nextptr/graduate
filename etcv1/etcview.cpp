#include "etcview.h"
#include <QKeyEvent>
#include <QVBoxlayout>
#include <QDebug>
#include <QPixmap>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QBitmap>

//智能车定位
void etcView::PositonSlot(pocket pok)
{
	int pos = pok.roidpos;//字符转int
	qDebug() << "nam " << pok.roadnam << "id " << pok.roadid << "pos " << pos;
	if (pok.roadnam == 'L')
	{
		if (pok.roadid == '1')
		{
			if (pos == 1)
			{
				labPositionCar->move(1346, 41);
			}
			if (pos == 2)
			{
				labPositionCar->move(1267, 41);
			}
			if (pos == 3)
			{
				labPositionCar->move(1130, 41);
			}
			if (pos == 4)
			{
				labPositionCar->move(1000, 41);
			}
			if (pos == 5)
			{
				labPositionCar->move(726, 41);
			}
			if (pos == 6)
			{
				labPositionCar->move(644, 41);
			}
			if (pos == 7)
			{
				labPositionCar->move(567, 41);
			}
		}
		if (pok.roadid == '2')
		{
			if (pos == 1)
			{
				labPositionCar->move(456, 895);
			}
			if (pos == 2)
			{
				labPositionCar->move(544, 895);
			}
			if (pos == 3)
			{
				labPositionCar->move(655, 895);
			}
			if (pos == 4)
			{
				labPositionCar->move(706, 895);
			}
			if (pos == 5)
			{
				labPositionCar->move(823, 895);
			}
			if (pos == 6)
			{
				labPositionCar->move(998, 895);
			}
			if (pos == 7)
			{
				labPositionCar->move(1138, 895);
			}
			if (pos == 8)
			{
				labPositionCar->move(1275, 895);
			}
			if (pos == 9)
			{
				labPositionCar->move(1364, 895);
			}
		}
	}
	if (pok.roadnam == 'E')
	{
		if (pok.roadid == 'T')
		{
			if (pos == 3)
			{
				labPositionCar->move(460, 41);
			}
			if (pos == 2)
			{
				labPositionCar->move(302, 807);
			}
		}
	}
	if (pok.roadnam == 'G')
	{
		if (pok.roadid == '1')
		{
			if (pos == 1)
			{
				labPositionCar->move(318, 46);
			}
			if (pos == 2)
			{
				labPositionCar->move(193, 121);
			}
			if (pos > 2 && pos < 8)
			{
				labPositionCar->move(109, 236 + (pos-3) * 85);
			}
			if (pos == 8)
			{
				labPositionCar->move(155, 706);
			}
			if (pos == 9)
			{
				labPositionCar->move(234, 760);
			}
		}
	}

	PositionGif->start();
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
	G_anima0->setDuration(5000 - 320 * (carNum->activeFlag));            //根据不同的排队情况，决定不同的用时
	G_anima0->setStartValue(QPointF(1350, 78));
	G_anima0->setEndValue(QPointF(570 + 60 * (carNum->activeFlag), 78));//根据不同的排队情况，决定不同的终点	

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
	animalArive(G_animaPark, carNum);//到达收费站

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

	//到达收费站
	animalArive(P_anima2, carNum);

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

	//通行记录，抓拍
	if (3 != m_pcar->clock)
	{
		etcRecord mOption;
		mOption.DetectionTime = QDate::currentDate().toString("yyyy - MM - dd");
		mOption.PlateNumber = m_pcar->CarNumber;
		mOption.UserName = m_pcar->userName;
		mOption.Result = "正常";
		if (0 == m_pcar->clock)
		{
			mOption.StationId = "001";
			mOption.Direction = "进入";
		}
		else
		{
			mOption.StationId = "003";
			mOption.Direction = "离开";
		}
		mOption.Money = QString::number(m_pcar->money, 10);
		mOption.Remark = "仿真ETC通行";
		//图片存储索引信息
		QString TimStr = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
		QStringList TimStrList = TimStr.split("-");
		QString ImgSaveName;//图片存储名
		for (int i = 0;i < 6;i++)
		{
			ImgSaveName += TimStrList[i];
		}
		ImgSaveName += m_pcar->CarNumber + ".jpg";
		//完成车辆通行的记录
		mOption.ImgDir = "./EtcInfo/" + TimStrList[0] + "/" + TimStrList[1] + "/" + TimStrList[2] + "/" + ImgSaveName;
		DBManager::getInstance()->insertinspectRecord(&mOption);
		//抓拍图片存储
		screen = QGuiApplication::primaryScreen();
		QPixmap pixmap = screen->grabWindow(0);
		QPixmap camera;
		if (0 == m_pcar->clock)
		{
			camera = pixmap.copy(364, 43, 400, 300);
		}
		else
		{
			camera = pixmap.copy(140, 720, 400, 300);
		}
		if (!camera.save(mOption.ImgDir, "jpg"))
		{
			qDebug() << "cut save png failed";
		}
	}
	else //离开
	{
		//计算扣费信息
		chargeRecord tmpRecord;
		tmpRecord.PlateNumber = m_pcar->CarNumber;
		tmpRecord.UserName = m_pcar->userName;
		tmpRecord.Time = QDate::currentDate().toString("yyyy - MM - dd");
		tmpRecord.Payout = QString::number(30, 10);
		if ((m_pcar->money - 30) < 30)
		{
			tmpRecord.Income = QString::number(100, 10);
			tmpRecord.Balance = QString::number(m_pcar->money + 70, 10);
			m_pcar->money = 70 + m_pcar->money;
		}
		else
		{
			tmpRecord.Income = QString::number(0, 10);
			tmpRecord.Balance = QString::number(m_pcar->money - 30, 10);
			m_pcar->money = m_pcar->money - 30;
		}
		tmpRecord.Remark = "仿真ETC收费";
		//显示车辆通行信息
		labCarnum2->setText(" " + m_pcar->CarNumber);
		labUsername2->setText(" " + m_pcar->userName);
		labBalance2->setText(" " + QString::number(m_pcar->money, 10));
		labDirection2->setText(" 离开");
		labCharge->setText(" 30");
		//存储数据
		DBManager::getInstance()->insertChargeRecord(&tmpRecord);
	}
}

void etcView::onbtn_ItcClock()
{
	QScreen *screen = QGuiApplication::primaryScreen();
	QString filePathName = "cut-";
	filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
	filePathName += ".png";
	QPixmap pixmap = screen->grabWindow(0);
	QPixmap camera = pixmap.copy(364, 43, 400, 300);
	if (!camera.save(filePathName, "png"))
	{
		qDebug() << "cut save png failed" ;
	}

	if (itcFlag == false)
	{
		itcFlag = true;
		btn_Itc->setText("ETC模式");
	}
	else
	{
		btn_Itc->setText("ITC模式");
		itcFlag = false;
	}
}

void etcView::EtcClock()
{
	lab_CurrentTime->setText("当前时间:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
}

etcView::etcView()
{
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
	connect(btn_Itc, &QPushButton::clicked, this, &etcView::onbtn_ItcClock);
	
}
void etcView::initConfig()
{
	itcFlag = false;
	//生成文件夹
	{
		QString TimStr = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
		QStringList TimStrList = TimStr.split("-");
		QDir mDir(QDir::currentPath());
		if (!mDir.exists("EtcInfo")) //确保文件夹存在
		{
			mDir.mkdir("EtcInfo");
		}
		QDir mDirYear("./EtcInfo");
		if (!mDirYear.exists(TimStrList[0])) //年
		{
			mDirYear.mkdir(TimStrList[0]);
		}
		QDir mDirMon("./EtcInfo/" + TimStrList[0]);
		if (!mDirMon.exists(TimStrList[1])) //月
		{
			mDirMon.mkdir(TimStrList[1]);
		}
		QDir mDirDay("./EtcInfo/" + TimStrList[0] + "/" + TimStrList[1]);
		if (!mDirDay.exists(TimStrList[2])) //日
		{
			mDirDay.mkdir(TimStrList[2]);
		}
	}
	//车辆定位动画
	{
		labPositionCar = new QLabel(this);
		labPositionCar->setAlignment(Qt::AlignCenter);
		labPositionCar->resize(80, 80);
		PositionGif = new QMovie(this);
		PositionGif->setFileName("./Resources/img/gif5新文件.gif");
		PositionGif->setScaledSize(labPositionCar->size());
		labPositionCar->setMovie(PositionGif);
		PositionGif->setScaledSize(QSize(80,80));
		/*labPositionCar->move(567, 41);
		PositionGif->start();*/
	}
	//车辆信息显示牌
	{
		QLabel *carlab5 = new QLabel(this);
		QLabel *carlab6 = new QLabel(this);
		QLabel *carlab7 = new QLabel(this);
		QLabel *carlab8 = new QLabel(this);
		QLabel *carlab9 = new QLabel(this);
		carlab9->setText("方  向:");
		carlab5->setText("车牌号:");
		carlab6->setText("用户名:");
		carlab7->setText("缴  费:");
		carlab8->setText("余  额:");
		carlab5->setFixedHeight(25);
		carlab6->setFixedHeight(25);
		carlab7->setFixedHeight(25);
		carlab8->setFixedHeight(25);
		carlab9->setFixedHeight(25);
		carlab5->setFixedWidth(40);
		carlab6->setFixedWidth(40);
		carlab7->setFixedWidth(40);
		carlab8->setFixedWidth(40);
		carlab9->setFixedWidth(40);
		carlab5->move(170, 870);
		carlab6->move(170, 890);
		carlab7->move(170, 910);
		carlab8->move(170, 930);
		carlab9->move(170, 950);
		carlab5->setAutoFillBackground(true);
		carlab6->setAutoFillBackground(true);
		carlab7->setAutoFillBackground(true);
		carlab8->setAutoFillBackground(true);
		carlab9->setAutoFillBackground(true);
		carlab5->setStyleSheet("color:rgb(255,170,0);background-color:rgb(0,0,127)");
		carlab6->setStyleSheet("color:rgb(255,170,0);background-color:rgb(0,0,127)");
		carlab7->setStyleSheet("color:rgb(255,170,0);background-color:rgb(0,0,127)");
		carlab8->setStyleSheet("color:rgb(255,170,0);background-color:rgb(0,0,127)");
		carlab9->setStyleSheet("color:rgb(255,170,0);background-color:rgb(0,0,127)");

		labCarnum2 = new QLabel(this);
		labUsername2 = new QLabel(this);
		labBalance2 = new QLabel(this);
		labDirection2 = new QLabel(this);
		labCharge = new QLabel(this);

		labCarnum2->setFixedHeight(25);
		labUsername2->setFixedHeight(25);
		labBalance2->setFixedHeight(25);
		labDirection2->setFixedHeight(25);
		labCharge->setFixedHeight(25);
		labCarnum2->setFixedWidth(60);
		labUsername2->setFixedWidth(60);
		labBalance2->setFixedWidth(60);
		labDirection2->setFixedWidth(60);
		labCharge->setFixedWidth(60);
		labCarnum2->move(210, 870);
		labUsername2->move(210, 890);
		labCharge->move(210, 910);
		labBalance2->move(210, 930);
		labDirection2->move(210, 950);
		//Qt::cyan
		labCarnum2->setStyleSheet("color:cyan;background-color:rgb(0,0,127)");
		labUsername2->setStyleSheet("color:cyan;background-color:rgb(0,0,127)");
		labCharge->setStyleSheet("color:cyan;background-color:rgb(0,0,127)");
		labBalance2->setStyleSheet("color:cyan;background-color:rgb(0,0,127)");
		labDirection2->setStyleSheet("color:cyan;background-color:rgb(0,0,127)");
		//labDirection2->setStyleSheet("color:rgb(255,170,0);background-color:rgb(0,0,127)");
	}
	//计算车辆余额
	{
		DBManager::getInstance()->initCarBalance(smartCar1);
		DBManager::getInstance()->initCarBalance(smartCar2);
		DBManager::getInstance()->initCarBalance(smartCar3);
		DBManager::getInstance()->initCarBalance(smartCar4);
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
	//labpos->setText("当前坐标 ");

	this->setScene(scene);//添加背景地图

	lab_CurrentTime = new QLabel(this);  //时间
	lab_CurrentTime->setText("当前时间:" +
		QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
	lab_CurrentTime->move(10, 1);
	lab_CurrentTime->setFixedHeight(30);

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

	btn_Itc = new QPushButton(this);  //模式转换
	btn_Itc->setText("ITC模式");
	btn_Itc->move(1812, 940);
	btn_Itc->resize(100, 75);

	etcCamera *camera = new etcCamera(this); //相机
	camera->move(1408, 715);
	camera->setWindowFlags(Qt::FramelessWindowHint);
	connect(this, &etcView::etcPicture, camera, &etcCamera::onCameraSave);

	timer = new  QTimer;  //时钟
	timer->start(1000);
}
