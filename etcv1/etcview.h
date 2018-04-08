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

	QPushButton*btn_Snapshout;  //����
	QPushButton*btn_SerialPort;  //����
	QPushButton*btn_Dbmanger;  //���ݿ�
	QPushButton*btn_Charge;  //�շ�
private:
	void initWidget();
	void initConnect();
	QVBoxLayout *p_Vlayout;
	etcCamera *camera;
	QGraphicsScene *scene;  //������ͼ
	QTimer* timer;  //��ʱ��
	QLabel*lab_CurrentTime;  //��ʾʱ��
	QLabel*lab_Background;  //������Ϣ ETC����ϵͳ
};

#endif // ETCVIEW_H
