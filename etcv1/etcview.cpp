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

	scene = new QGraphicsScene;  //������ͼ
	scene->setSceneRect(0, 0, 1920, 1015);
	scene->setBackgroundBrush(QPixmap("./background.png").scaled(1920, 1015));

	etcCar*car1 = new etcCar;  //���� 
	scene->addItem(car1);
	car1->setPos(50, 50);

	this->setScene(scene);//��ӱ�����ͼ

	lab_CurrentTime = new QLabel(this);  //ʱ��
	lab_CurrentTime->setText("Current Time is:" +
		QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
	lab_CurrentTime->move(0, 10);

	btn_SerialPort = new QPushButton(this);  //����
	btn_SerialPort->setText("����");
	btn_SerialPort->move(1812, 715);
	btn_SerialPort->resize(100, 75);

	btn_Dbmanger = new QPushButton(this);  //���ݿ�
	btn_Dbmanger->setText("����");
	btn_Dbmanger->move(1812, 790);
	btn_Dbmanger->resize(100, 75);

	btn_Charge = new QPushButton(this);  //�շ�
	btn_Charge->setText("�շ�");
	btn_Charge->move(1812, 865);
	btn_Charge->resize(100, 75);

	btn_Snapshout = new QPushButton(this);  //���հ�ť
	btn_Snapshout->setText("����");
	btn_Snapshout->move(1812, 940);
	btn_Snapshout->resize(100, 75);


	etcCamera *camera = new etcCamera(this); //���
	camera->move(1410, 715);
	camera->setWindowFlags(Qt::FramelessWindowHint);

	connect(btn_Snapshout, &QPushButton::clicked, camera, &etcCamera::onBtnSnapshot);

	timer = new  QTimer;  //�˶�
	timer->start(100);

	//QPropertyAnimation*animation = new QPropertyAnimation(car1, "rotation"); //����
	//animation->setDuration(10000);
	//animation->setStartValue(0);
	//animation->setEndValue(1800);
	//animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void etcView::onBtnSnapshot()
{
	qDebug() << "xsaxsaxsa";
}