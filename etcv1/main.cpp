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
	etcPortWidget*portWidget = new etcPortWidget;
	chargeWidget *chargewidget = new chargeWidget;

	etcView view;  //主窗口
	view.showMaximized();
	view.show();

	QObject::connect(view.btn_Dbmanger, &QPushButton::clicked, dbwidget, &dbWidget::on_btnShowClick);
	QObject::connect(view.btn_SerialPort, &QPushButton::clicked, portWidget, &etcPortWidget::on_btnShowClick);
	QObject::connect(view.btn_Charge, &QPushButton::clicked, chargewidget, &chargeWidget::on_btnShowClick);

	return app.exec();
}
