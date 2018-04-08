#ifndef DBWIDGET_H
#define DBWIDGET_H

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



class dbWidget : public QWidget
{
	Q_OBJECT

public Q_SLOTS:
	void on_btnShowClick();
	void on_btnSearchClick();
	void on_btnInsertClick();
	void onCellChange(int row, int col);
	void onMenuRequested(const QPoint & pos);
	void onActionDeleteItm();
	void onTableRecordItemClicked(QTableWidgetItem *pItem);

public:
	dbWidget();
	~dbWidget();
	void showTable(UpOrDown);

private:

	void initWidget(void);
	void initConnect(void);

	int m_begingIndex;      //查询起点
	int m_stepCount;        //单次查询长度
	int m_RemoveItemSize;
	int m_lastCliskItemId;

	QList<etcRecord> *m_pRecordList;

	QTableWidget  *m_pTableRecord;
	QDateEdit	*m_pStartTime;
	QDateEdit	*m_pEndTime;
	QComboBox	*m_pStationId;
	QLineEdit	*m_pPlateNumber;
	QLineEdit	*m_pUserName;
	QComboBox	*m_pResult;
	QComboBox   *m_pDirection;

	QLabel		*m_pLabelScanImage;
	QMenu       *m_pMenu;
	QAction     *m_pActionDeleteItm;

	QPushButton	*m_pBtnSearch;
	QPushButton *m_pBtnIndex;
protected:
	//void paintEvent(QPaintEvent *mPaintEvent);
	void wheelEvent(QWheelEvent *mWhellEvent);
};

#endif // DBWIDGET_H
