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

	QApplication app(argc, argv); //数据库
	g_pDBManage = DBManager::getInstance();
	g_pDBManage->start();

	dbWidget*dbwidget = new dbWidget;//进出检测记录窗口
	etcPortWidget*portWidget = new etcPortWidget;//串口界面
	chargeWidget *chargewidget = new chargeWidget;//收费管理界面

	etcView view;  //主窗口
	view.showMaximized(); //最大化
	view.show(); //显示窗口

	QObject::connect(view.btn_Dbmanger, &QPushButton::clicked, dbwidget, &dbWidget::on_btnShowClick);
	QObject::connect(view.btn_SerialPort, &QPushButton::clicked, portWidget, &etcPortWidget::on_btnShowClick);
	QObject::connect(view.btn_Charge, &QPushButton::clicked, chargewidget, &chargeWidget::on_btnShowClick);
	QObject::connect(portWidget, &etcPortWidget::PositionSignal, &view, &etcView::PositonSlot);

	return app.exec();
}
