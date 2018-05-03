#include "etccar.h"
#include "etcview.h"
#include "dbmanger.h"
#include "etccamera.h"
#include "dbwidget.h"
#include "etcport.h"
#include "chargewidget.h"

#include <QtWidgets/QApplication>
#include <QPixmap>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QTime>

DBManager *g_pDBManage;

int main(int argc, char *argv[])
{

	QApplication app(argc, argv); //���ݿ�
	g_pDBManage = DBManager::getInstance();
	g_pDBManage->start();

	dbWidget*dbwidget = new dbWidget;//��������¼����
	etcPortWidget*portWidget = new etcPortWidget;//���ڽ���
	chargeWidget *chargewidget = new chargeWidget;//�շѹ������

	etcView view;  //������
	view.showMaximized();
	view.show();

	QObject::connect(view.btn_Dbmanger, &QPushButton::clicked, dbwidget, &dbWidget::on_btnShowClick);
	QObject::connect(view.btn_SerialPort, &QPushButton::clicked, portWidget, &etcPortWidget::on_btnShowClick);
	QObject::connect(view.btn_Charge, &QPushButton::clicked, chargewidget, &chargeWidget::on_btnShowClick);
	QObject::connect(portWidget, &etcPortWidget::PositionSignal, &view, &etcView::PositonSlot);

	return app.exec();
}
