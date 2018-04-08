#ifndef CHARGEWIDGET_H
#define CHARGEWIDGET_H

#pragma execution_character_set("utf-8")  

#include "etcrecord.h"
#include "dbmanger.h"

#include <qscrollbar.h>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTimeEdit>
#include <QTableWidget>
#include <QWheelevent>
#include <QPushButton>
#include <QHeaderView>
#include <QCompleter>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QPainter>
#include <QACtion>
#include <QLabel>
#include <QMenu>

class chargeWidget : public QWidget
{
	Q_OBJECT
public Q_SLOTS:
	void on_btnShowClick(void);
	void on_btnSearchClick(void);
	void on_btnChargeClick(void);
	void onCellChange(int row, int col);
	void onMenuRequested(const QPoint & pos);
	void onActionDeleteItm();
	void onTableRecordItemClicked(QTableWidgetItem *pItem);

public:
	chargeWidget();
	~chargeWidget();
	void showTable(UpOrDown);
private:
	void initWidget(void);
	void initConnect(void);

	int m_begingIndex;      //查询起点
	int m_stepCount;        //单次查询长度
	int m_RemoveItemSize;
	int m_lastCliskItemId;

	QList<chargeRecord> *m_pRecordList;

	QTableWidget  *m_pTableRecord;
	QDateEdit	  *m_pStartTime;
	QDateEdit	  *m_pEndTime;
	QLineEdit	  *m_pPlateNumber;
	QLineEdit	  *m_pUserName;

	QMenu         *m_pMenu;
	QAction       *m_pActionDeleteItm;

	QPushButton   *m_pBtnSearch;
	QPushButton	  *m_pBtnCharge;
	QPushButton   *m_pBtnIndex;
protected:
	void wheelEvent(QWheelEvent *mWhellEvent);

};

#endif // CHARGEWIDGET_H
