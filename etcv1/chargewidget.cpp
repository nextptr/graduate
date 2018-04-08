#include "chargewidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

void chargeWidget::on_btnSearchClick(void)
{
	chargeRecord option;
	option.PlateNumber = m_pPlateNumber->text();
	option.Time = m_pStartTime->text();
	option.Remark = m_pEndTime->text();
	option.UserName = m_pUserName->text();
	DBManager::getInstance()->getChargeRecordList(option, 0, m_stepCount, m_pRecordList);
	if (m_pRecordList->size()>0)
	{
		showTable(up);        //显示
		qDebug() << "ok";
	}
	else
	{
		showTable(deful);
		qDebug() << "fail";
	}
}

void chargeWidget::on_btnChargeClick(void)
{
	QString ChoiseFileName = QFileDialog::getOpenFileName(this, tr("GroupIn"));
	if (ChoiseFileName.isEmpty())
	{
		return;
	}

	QFile GroupInFile(ChoiseFileName);
	if (!GroupInFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << GroupInFile.errorString();
	}

	QTextStream wrierOut(&GroupInFile);
	while (!wrierOut.atEnd())
	{
		QString line = wrierOut.readLine();
		QStringList tmpList = line.split(",", QString::SkipEmptyParts);
		if (7 != tmpList.size())
		{
			QMessageBox::warning(this, tr("waring"), tr("invalid file!!"), QMessageBox::Abort);
			return;
		}
		chargeRecord tmpRecord;
		if (NULL != tmpList.at(0))
		{
			tmpRecord.PlateNumber = tmpList.at(0);
			tmpRecord.UserName = tmpList.at(1);
			tmpRecord.Time = tmpList.at(2);
			tmpRecord.Payout = tmpList.at(3);
			tmpRecord.Income = tmpList.at(4);
			tmpRecord.Balance = tmpList.at(5);
			tmpRecord.Remark = tmpList.at(6);
			DBManager::getInstance()->insertChargeRecord(&tmpRecord);
		}
	}
}

void chargeWidget::onCellChange(int row, int col)
{
	int id = m_pTableRecord->item(row, 0)->text().toInt();
	chargeRecord *tmpRecord = NULL;
	tmpRecord = getChargeRecord(m_pRecordList, id);
	if (NULL == tmpRecord)
	{
		return;
	}
	if (1 == col) //查找修改了哪一项
	{
		tmpRecord->PlateNumber = m_pTableRecord->item(row, col)->text();
	}
	if (2 == col)
	{
		tmpRecord->UserName = m_pTableRecord->item(row, col)->text();
	}
	if (3 == col)
	{
		tmpRecord->Time = m_pTableRecord->item(row, col)->text();
	}
	if (4 == col)
	{
		tmpRecord->Payout = m_pTableRecord->item(row, col)->text();
	}
	if (5 == col)
	{
		tmpRecord->Income = m_pTableRecord->item(row, col)->text();
	}
	if (6 == col)
	{
		tmpRecord->Balance = m_pTableRecord->item(row, col)->text();
	}
	if (7 == col)
	{
		tmpRecord->Remark = m_pTableRecord->item(row, col)->text();
	}
	modifyList(m_pRecordList, *tmpRecord);   //修改record
	DBManager::getInstance()->modifyinspectRecord(tmpRecord);//修改数据库
}

void chargeWidget::onMenuRequested(const QPoint & pos)
{
	m_pMenu->clear();
	if (m_pTableRecord->itemAt(pos) != NULL)
	{
		m_pMenu->addAction(m_pActionDeleteItm);
		m_pMenu->setContextMenuPolicy(Qt::DefaultContextMenu);
		m_pMenu->exec(QCursor::pos());
	}
}

void chargeWidget::onActionDeleteItm()
{
	int row = m_pTableRecord->currentRow();
	DBManager::getInstance()->deleteChargeRecord(m_pTableRecord->item(row, 0)->text().toInt());        //数据库删除记录
	eraseArecord(m_pRecordList, row);       				//删除list相应record
	m_pTableRecord->removeRow(row);                         //删除表格部件相应行
}

void chargeWidget::onTableRecordItemClicked(QTableWidgetItem * pItem)
{
	int id = m_pTableRecord->item(pItem->row(), 0)->text().toInt();
	if (m_lastCliskItemId != id)
	{
		m_lastCliskItemId = id;
		//显示图片
		/*HistoryRecord tmpRecord;
		if (m_HisManager.getAutomobRecord(&m_HisManager.m_HistoryRecordList, id, &tmpRecord))
		{
		showRecord(tmpRecord);
		}*/
	}
}

chargeWidget::chargeWidget()
{
	m_begingIndex = 0;      //查询起点
	m_stepCount = 36;        //单次查询长度
	m_RemoveItemSize = 0;
	m_lastCliskItemId = 0;
	initWidget();
	initConnect();
}

chargeWidget::~chargeWidget()
{
}

void chargeWidget::showTable(UpOrDown upordown)
{
	disconnect(m_pTableRecord, &QTableWidget::cellChanged, this, &chargeWidget::onCellChange); //断开修改槽连接
	
	m_pTableRecord->clear();
	m_pTableRecord->setRowCount(m_pRecordList->size());
	QStringList header;
	header << tr("索引")
		<< tr("车牌号")
		<< tr("用户名")
		<< tr("时间")
		<< tr("扣费")
		<< tr("充值")
		<< tr("余额")
		<< tr("备注");
	m_pTableRecord->setHorizontalHeaderLabels(header);
	for (int count = 0;count < m_pRecordList->size();count++)
	{
		chargeRecord tmp = m_pRecordList->at(count);
		/*索引被隐藏 用于修改数据库*/
		QTableWidgetItem *item_Recordid = new QTableWidgetItem();
		item_Recordid->setText(QString::number(tmp.id, 10));
		m_pTableRecord->setItem(count, 0, item_Recordid);

		QTableWidgetItem *item_PlateNumber = new QTableWidgetItem();
		item_PlateNumber->setText(tmp.PlateNumber);
		m_pTableRecord->setItem(count, 1, item_PlateNumber);

		QTableWidgetItem *item_Name = new QTableWidgetItem();
		item_Name->setText(tmp.UserName);
		m_pTableRecord->setItem(count, 2, item_Name);

		QTableWidgetItem *item_Time = new QTableWidgetItem();
		item_Time->setText(tmp.Time);
		m_pTableRecord->setItem(count, 3, item_Time);

		QTableWidgetItem *item_Payout = new QTableWidgetItem();
		item_Payout->setText(tmp.Payout);
		m_pTableRecord->setItem(count, 4, item_Payout);

		QTableWidgetItem *item_Income = new QTableWidgetItem();
		item_Income->setText(tmp.Income);
		m_pTableRecord->setItem(count, 5, item_Income);

		QTableWidgetItem *item_Balance = new QTableWidgetItem();
		item_Balance->setText(tmp.Balance);
		m_pTableRecord->setItem(count, 6, item_Balance);

		QTableWidgetItem *item_Remark = new QTableWidgetItem();
		item_Remark->setText(tmp.Remark);
		m_pTableRecord->setItem(count, 7, item_Remark);
	}

	if (upordown == down)
	{
		m_pTableRecord->scrollToBottom();
	}

	if (upordown == up)
	{
		m_pTableRecord->scrollToTop();
	}
	connect(m_pTableRecord, &QTableWidget::cellChanged, this, &chargeWidget::onCellChange);
}

void chargeWidget::initWidget(void)
{
	this->setFixedSize(640, 417);
	m_pRecordList = new QList<chargeRecord>();
	//搜索框
	QGridLayout *pGridCondition = new QGridLayout();
	{
		QLabel *pLabelCondition1 = new QLabel(this);
		m_pPlateNumber = new QLineEdit();
		m_pPlateNumber->setFixedWidth(70);
		QLabel *pLabelCondition2 = new QLabel(this);
		m_pUserName = new QLineEdit();
		m_pUserName->setFixedWidth(70);

		QLabel *pLabelCondition3 = new QLabel(this);
		m_pStartTime = new QDateEdit();
		m_pStartTime->setFixedWidth(110);
		m_pStartTime->setCalendarPopup(true);
		m_pStartTime->setDisplayFormat("yyyy - MM - dd");
		QLabel *pLabelCondition4 = new QLabel(this);
		m_pEndTime = new QDateEdit();
		m_pEndTime->setFixedWidth(110);
		m_pEndTime->setCalendarPopup(true);
		m_pEndTime->setDisplayFormat("yyyy - MM - dd");

		m_pBtnSearch = new QPushButton();
		m_pBtnSearch->setFixedHeight(50);
		m_pBtnSearch->setFixedWidth(80);
		m_pBtnCharge = new QPushButton();
		m_pBtnCharge->setFixedHeight(50);
		m_pBtnCharge->setFixedWidth(80);
		m_pBtnIndex = new QPushButton();
		m_pBtnIndex->setFixedWidth(80);

		pLabelCondition1->setText(tr("车牌号"));
		pLabelCondition2->setText(tr("用户名"));
		pLabelCondition3->setText(tr("开始时间"));
		pLabelCondition4->setText(tr("结束时间"));
		m_pBtnSearch->setText(tr("搜索"));
		m_pBtnCharge->setText(tr("充值"));

		pGridCondition->addWidget(pLabelCondition1, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pPlateNumber,   0, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition2, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pUserName,      1, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition3, 0, 2, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pStartTime,     0, 3, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition4, 1, 2, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pEndTime,       1, 3, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pBtnSearch,     0, 4, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pBtnCharge,     0, 5, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

		pGridCondition->setHorizontalSpacing(6);
		pGridCondition->setVerticalSpacing(6);
		pGridCondition->setContentsMargins(0, 4, 4, 4);
	}
	//表格
	QHBoxLayout *pLayoutRecord = new QHBoxLayout();
	{
		m_pTableRecord = new QTableWidget();
		{
			m_pTableRecord->setColumnCount(8); //设置列数
			m_pTableRecord->horizontalHeader()->setDefaultSectionSize(150);
			//设置表头内容
			QStringList header;
			header << tr("索引")
				<< tr("车牌号")
				<< tr("用户名")
				<< tr("时间")
				<< tr("扣费")
				<< tr("充值")
				<< tr("余额")
				<< tr("备注");
			m_pTableRecord->setHorizontalHeaderLabels(header);
			m_pTableRecord->horizontalHeader()->setFixedHeight(32);											//设置表头的高度
			m_pTableRecord->verticalHeader()->setDefaultSectionSize(32);									//设置行高
			m_pTableRecord->verticalHeader()->setVisible(false);											//设置垂直头（行号）不可见
			//m_pTableRecord->setFrameShape(QFrame::NoFrame);												//设置无边框
			m_pTableRecord->setShowGrid(true);																//设置显示格子线
			m_pTableRecord->setSelectionMode(QAbstractItemView::ExtendedSelection);							//可多选（Ctrl、Shift、  Ctrl+A都可以）
			m_pTableRecord->setSelectionBehavior(QAbstractItemView::SelectRows);							//设置选择行为时每次选择一行
			//m_pTableRecord->setSelectionMode(QAbstractItemView::SingleSelection);                         //设置为可以选中单个
			m_pTableRecord->setEditTriggers(QAbstractItemView::DoubleClicked);                              //双击编辑
			m_pTableRecord->setStyleSheet("selection-background-color:lightblue;");							//设置选中背景色
			m_pTableRecord->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");	//设置表头背景色
																											// column width
			//m_pTableRecord->horizontalHeader()->resizeSection(0, 150);									//设置表头第一列的宽度为150
            //m_pTableRecord->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);				//表格等宽
			m_pTableRecord->setColumnHidden(10, true);
			m_pTableRecord->horizontalHeader()->setStretchLastSection(true);								//设置充满表宽度
			m_pTableRecord->setColumnWidth(0, 100);
			m_pTableRecord->setColumnWidth(1, 70);
			m_pTableRecord->setColumnWidth(2, 70);
			m_pTableRecord->setColumnWidth(3, 110);
			m_pTableRecord->setColumnWidth(4, 90);
			m_pTableRecord->setColumnWidth(5, 90);
			m_pTableRecord->setColumnWidth(6, 90);
			m_pTableRecord->setColumnWidth(7, 90);
			m_pTableRecord->hideColumn(0);                                                                  //隐藏第一列索引
			m_pTableRecord->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);                           //关闭水平滚动条
			m_pTableRecord->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);                              //打开垂直滚动条 
			m_pTableRecord->setContextMenuPolicy(Qt::CustomContextMenu);                                    //设置右键菜单
		}
		pLayoutRecord->addWidget(m_pTableRecord);
	}
	QGridLayout *m_pGridLayout = new QGridLayout(); //布局器
	{
		m_pGridLayout->addLayout(pGridCondition, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addLayout(pLayoutRecord, 1, 0, 9, 1, Qt::AlignLeft | Qt::AlignTop);
	}
	this->setLayout(m_pGridLayout);

	m_pGridLayout->setHorizontalSpacing(4);// 设置水平间距
	m_pGridLayout->setVerticalSpacing(4);	// 设置垂直间距
	m_pGridLayout->setContentsMargins(0, 0, 0, 0);

	{
		m_pMenu = new QMenu();               //右键菜单初始化
		m_pActionDeleteItm = new QAction(this);
		m_pActionDeleteItm->setText(tr("删除"));
	}
}

void chargeWidget::initConnect(void)
{
	connect(m_pBtnSearch, &QPushButton::clicked, this, &chargeWidget::on_btnSearchClick);
	connect(m_pBtnCharge, &QPushButton::clicked, this, &chargeWidget::on_btnChargeClick);

}

void chargeWidget::wheelEvent(QWheelEvent * mWhellEvent)
{
	chargeRecord option;
	option.PlateNumber = m_pPlateNumber->text();
	option.Time = m_pStartTime->text();
	option.Remark = m_pEndTime->text();
	option.UserName = m_pUserName->text();
	int pos = m_stepCount - 10 - m_RemoveItemSize; //触发下翻滚轮信号的值，9是一个表格视窗的大小
	if (pos == m_pTableRecord->verticalScrollBar()->value())//下翻查看
	{
		m_begingIndex = m_begingIndex + pos; //更新
		if (mWhellEvent->delta() < 0) //下滑滚轮
		{
			m_RemoveItemSize = 0;
			bool bRet = DBManager::getInstance()->getChargeRecordList(option, m_begingIndex, m_stepCount, m_pRecordList);
			if (bRet && m_pRecordList->size() > 0)
			{
				showTable(up);
			}
			else
			{
				qDebug() << "down fail" << endl;
			}
		}
	}
	if (0 == m_pTableRecord->verticalScrollBar()->value())  //上翻查看
	{
		if (m_begingIndex > 0) //m_begingIndex>0曾经下翻过
		{
			if (mWhellEvent->delta() > 0)  //向上滚轮
			{
				m_begingIndex = m_begingIndex - pos - m_RemoveItemSize;
				m_RemoveItemSize = 0;
				if (m_begingIndex < 0)
				{
					m_begingIndex = 0;
				}
				DBManager::getInstance()->getChargeRecordList(option, m_begingIndex, m_stepCount, m_pRecordList);
				if (m_pRecordList->size()>0)
				{
					showTable(down);
				}
				else
				{
					qDebug() << "up fail" << endl;
				}
			}
		}
	}
}

void chargeWidget::on_btnShowClick()
{
	this->hide();
	this->show();
}