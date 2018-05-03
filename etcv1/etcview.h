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

	QPushButton*btn_Snapshout;  //����
	QPushButton*btn_SerialPort;  //����
	QPushButton*btn_Dbmanger;  //���ݿ�
	QPushButton*btn_Charge;  //�շ�
protected:
	void mousePressEvent(QMouseEvent *myevent);
private:
	void initWidget();
	void initConnect();
	void initAnimal();
	QVBoxLayout *p_Vlayout;
	etcCamera *camera;
	etcCar*smartCar1; //С��1
	etcCar*smartCar2; //С��2
	etcCar*smartCar3; //С��3
	etcCar*smartCar4; //С��4

	QLabel *labpos;  //��������
	QSequentialAnimationGroup* group;

	QLabel*lab1;
	QLabel*lab2;
	QLabel*lab3;
	QLabel*lab4;
	QLabel*lab5;
	QLabel*lab6;
	QGraphicsScene *scene;  //������ͼ
	QTimer* timer;  //��ʱ��
	QLabel*lab_CurrentTime;  //��ʾʱ��
	QLabel*lab_Background;  //������Ϣ ETC����ϵͳ
};
#endif // ETCVIEW_H
