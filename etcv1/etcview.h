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


class etcView : public QGraphicsView
{
	Q_OBJECT
signals :
	void carFlag(etcCar*car);
	void carRota(etcCar*car);
	void carCharge(etcCar*car);
	void etcPicture(etcCar*car);
public Q_SLOTS:
	void onBtnSnapshot();
	void PositonSlot(pocket);
	void EtcClock();
	void AutoMove(etcCar*);
	void AutoRota(etcCar*);
	void car1Clock();
	void car2Clock();
	void car3Clock();
	void car4Clock();

	void car1Arive();
	void car2Arive();
	void car3Arive();
	void car4Arive();
	void arriveStation(etcCar*);
public:
	etcView();
	~etcView();
	void animalClock(QPropertyAnimation*animation,etcCar*carNum);
	void animalArive(QPropertyAnimation*animation, etcCar*carNum);//���������շ�վ
	QPushButton*btn_Snapshout;  //����
	QPushButton*btn_SerialPort; //����
	QPushButton*btn_Dbmanger;   //���ݿ�
	QPushButton*btn_Charge;     //�շ�
protected:
	void mousePressEvent(QMouseEvent *myevent);
private:
	void initWidget();
	void initConnect();
	void initConfig();
private:
	QVBoxLayout *p_Vlayout;
	etcCamera *camera;
	etcCar*smartCar1; //С��1
	etcCar*smartCar2; //С��2
	etcCar*smartCar3; //С��3
	etcCar*smartCar4; //С��4
	QLabel*brakeBarIn;  //բ��
	QLabel*brakeBarOut;  //բ��

	QLabel *labpos;           //��������
	QTime* lastClickTime; //�ϴε��ʱ��
	QTime* nowClickTime; //�ϴε��ʱ��
	int park;                //�Ŷ���Դ

	QLabel*lab1;
	QLabel*lab2;
	QLabel*lab3;
	QLabel*lab4;
	QLabel*lab5;
	QLabel*lab6;

	/*QLabel*labCarnum1;
	QLabel*labUsername1;
	QLabel*labBalance1;
	QLabel*labDirection1;*/
	QLabel*labCarnum2;
	QLabel*labUsername2;
	QLabel*labBalance2;
	QLabel*labDirection2;
	QLabel*labCharge;

	QGraphicsScene *scene;  //������ͼ
	QTimer* timer;          //��ʱ��
	QLabel*lab_CurrentTime; //��ʾʱ��
	QLabel*lab_Background;  //������Ϣ ETC����ϵͳ
};
#endif // ETCVIEW_H
