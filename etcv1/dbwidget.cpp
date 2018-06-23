#include "dbwidget.h"
#include "dbmanger.h"
#include <QDebug>

dbWidget::dbWidget()
{

	m_begingIndex = 0;       //查询起点
	m_stepCount = 36;        //单次查询长度
	m_RemoveItemSize = 0;    //已经删除条目长度
	m_lastCliskItemId = 0;   //最后点击条目id
	initWidget();
	initConnect();
}

dbWidget::~dbWidget()
{

}

void dbWidget::on_btnSearchClick()
{
	//m_begingIndex = 0;     //按钮按下则初始化开始点    
	//m_RemoveItemSize = 0;//初始化已删除条目数量
	SearchOption mOption;
	mOption.StartTime   = m_pStartTime->text();
	mOption.EndTime     = m_pEndTime->text();
	mOption.StationId   = m_pStationId->currentText();
	mOption.PlateNumber = m_pPlateNumber->text();
	mOption.UserName    = m_pUserName->text();
	mOption.Result      = m_pResult->currentText();
	mOption.Direction   = m_pDirection->currentText();

	DBManager::getInstance()->getinspectRecordList(mOption, 0, m_stepCount, m_pRecordList);
	if (m_pRecordList->size()>0)
	{
		showTable(up);        //显示
		qDebug() << "ok" << endl;
	}
	else
	{
		showTable(deful);
		qDebug() << "fail" << endl;
	}
}

void dbWidget::on_btnInsertClick()
{
	etcRecord mOption;
	mOption.DetectionTime = m_pStartTime->text();
	mOption.StationId = m_pStationId->currentText();
	mOption.PlateNumber = m_pPlateNumber->text();
	mOption.UserName = m_pUserName->text();
	mOption.Result = m_pResult->currentText();
	mOption.Direction = m_pDirection->currentText();

	DBManager::getInstance()->insertinspectRecord(&mOption);
}

void dbWidget::onCellChange(int row, int col)
{
	int id = m_pTableRecord->item(row, 0)->text().toInt();
	etcRecord *tmpRecord = NULL;
	tmpRecord = getInspectRecord(m_pRecordList, id);
	if (NULL == tmpRecord)
	{
		return;
	}
	if (1 == col) //查找修改了哪一项
	{   
		tmpRecord->StationId = m_pTableRecord->item(row, col)->text();
	}
	if (2 == col) //查找修改了哪一项
	{
		tmpRecord->Direction = m_pTableRecord->item(row, col)->text();
	}
	if (3 == col)
	{
		tmpRecord->PlateNumber = m_pTableRecord->item(row, col)->text();
	}
	if (4 == col)
	{
		tmpRecord->UserName = m_pTableRecord->item(row, col)->text();
	}
	if (5 == col)
	{
		tmpRecord->Money = m_pTableRecord->item(row, col)->text();
	}
	if (6 == col)
	{
		tmpRecord->Result = m_pTableRecord->item(row, col)->text();
	}
	if (7 == col)
	{
		tmpRecord->DetectionTime = m_pTableRecord->item(row, col)->text();
	}
	if (8 == col)
	{
		tmpRecord->Remark = m_pTableRecord->item(row, col)->text();
	}

	modifyList(m_pRecordList, *tmpRecord);   //修改record

	DBManager::getInstance()->modifyinspectRecord(*tmpRecord);//修改数据库

}

void dbWidget::onMenuRequested(const QPoint & pos)
{
	m_pMenu->clear();
	if (m_pTableRecord->itemAt(pos) != NULL)
	{
		m_pMenu->addAction(m_pActionDeleteItm);
		m_pMenu->setContextMenuPolicy(Qt::DefaultContextMenu);
		m_pMenu->exec(QCursor::pos());
	}
}

void dbWidget::onActionDeleteItm()
{
	int row = m_pTableRecord->currentRow();
	DBManager::getInstance()->deleteinspectRecord(m_pTableRecord->item(row, 0)->text().toInt());        //数据库删除记录
	eraseArecord(m_pRecordList, row);       				//删除list相应record
	m_pTableRecord->removeRow(row);                         //删除表格部件相应行
}

void dbWidget::onTableRecordItemClicked(QTableWidgetItem * pItem)
{
	int id = m_pTableRecord->item(pItem->row(), 0)->text().toInt();
	if (m_lastCliskItemId != id)
	{
		m_lastCliskItemId = id;
		etcRecord*tmp = getInspectRecord(m_pRecordList, id);
		m_pLabelScanImage->setPixmap(QPixmap(tmp->ImgDir));
	
	}
}

void dbWidget::showTable(UpOrDown upordown)
{
	disconnect(m_pTableRecord, &QTableWidget::cellChanged, this, &dbWidget::onCellChange); //断开修改槽连接

	m_pTableRecord->clear();
	m_pTableRecord->setRowCount(m_pRecordList->size());
	QStringList header;
	header << tr("索引")
		<< tr("站点")
		<< tr("方向")
		<< tr("车牌号")
		<< tr("用户名")
		<< tr("余额")
		<< tr("检测")
		<< tr("时间")
		<< tr("备注");
	m_pTableRecord->setHorizontalHeaderLabels(header);

	for (int count = 0;count < m_pRecordList->size();count++)
	{
		etcRecord tmp = m_pRecordList->at(count);
		/*索引被隐藏 用于修改数据库*/
		QTableWidgetItem *item_Recordid = new QTableWidgetItem();
		item_Recordid->setText(QString::number(tmp.id, 10));
		m_pTableRecord->setItem(count, 0, item_Recordid);

		QTableWidgetItem *item_Stationid = new QTableWidgetItem();
		item_Stationid->setText(tmp.StationId);
		m_pTableRecord->setItem(count, 1, item_Stationid);

		QTableWidgetItem *item_Direction = new QTableWidgetItem();
		item_Direction->setText(tmp.Direction);
		m_pTableRecord->setItem(count, 2, item_Direction);

		QTableWidgetItem *item_PlateNumber = new QTableWidgetItem();
		item_PlateNumber->setText(tmp.PlateNumber);
		m_pTableRecord->setItem(count, 3, item_PlateNumber);

		QTableWidgetItem *item_Name = new QTableWidgetItem();
		item_Name->setText(tmp.UserName);
		m_pTableRecord->setItem(count, 4, item_Name);

		QTableWidgetItem *item_Money = new QTableWidgetItem();
		item_Money->setText(tmp.Money);
		m_pTableRecord->setItem(count, 5, item_Money);

		QTableWidgetItem *item_Result = new QTableWidgetItem();
		item_Result->setText(tmp.Result);
		m_pTableRecord->setItem(count, 6, item_Result);

		QTableWidgetItem *item_Time = new QTableWidgetItem();
		item_Time->setText(tmp.DetectionTime);
		m_pTableRecord->setItem(count, 7, item_Time);

		QTableWidgetItem *item_Remark = new QTableWidgetItem();
		item_Remark->setText(tmp.Remark);
		m_pTableRecord->setItem(count, 8, item_Remark);

	}

	if (upordown == down)
	{
		m_pTableRecord->scrollToBottom();
	}

	if (upordown == up)
	{
		m_pTableRecord->scrollToTop();
	}
	connect(m_pTableRecord, &QTableWidget::cellChanged, this, &dbWidget::onCellChange);
}

void dbWidget::on_btnShowClick(void)
{
	this->hide();
	this->show();
}

void dbWidget::initWidget(void)
{
	this->setFixedSize(1070, 547);
	m_pRecordList = new QList<etcRecord>();
	//搜索框
	QGridLayout *pGridCondition = new QGridLayout();
	{
		QLabel *pLabelCondition1 = new QLabel(this);
		m_pStartTime = new QDateEdit();
		m_pStartTime->setFixedWidth(140);
		m_pStartTime->setCalendarPopup(true);
		m_pStartTime->setDisplayFormat("yyyy - MM - dd");
		m_pStartTime->setDate(QDate::currentDate());

		QLabel *pLabelCondition2 = new QLabel(this);
		m_pEndTime = new QDateEdit();
		m_pEndTime->setFixedWidth(140);
		m_pEndTime->setCalendarPopup(true);
		m_pEndTime->setDisplayFormat("yyyy - MM - dd");
		m_pEndTime->setDate(QDate::currentDate());

	
		QLabel *pLabelCondition3 = new QLabel(this);
		m_pStationId = new QComboBox();
		m_pStationId->setFixedWidth(140);
		QStringList strings;
		strings << tr("") << tr("001") << tr("002") << tr("003") << tr("004");
		m_pStationId->addItems(strings);

		QLabel *pLabelCondition4 = new QLabel(this);
		m_pDirection = new QComboBox();
		m_pDirection->setFixedWidth(140);
		strings.clear();
		strings << tr("") << tr("进入") << tr("离开");
		m_pDirection->addItems(strings);

		QLabel *pLabelCondition5 = new QLabel(this);
		m_pPlateNumber = new QLineEdit();
		m_pPlateNumber->setFixedWidth(140);

		QLabel *pLabelCondition6 = new QLabel(this);
		m_pUserName = new QLineEdit();
		m_pUserName->setFixedWidth(140);

		QLabel *pLabelCondition7 = new QLabel(this);
		m_pResult = new QComboBox();
		m_pResult->setFixedWidth(140);
		strings.clear();
		strings << tr("") << tr("正常") << tr("异常");
		m_pResult->addItems(strings);

		m_pBtnSearch = new QPushButton();
		m_pBtnSearch->setFixedHeight(60);
		m_pBtnSearch->setFixedWidth(80);

		m_pBtnIndex= new QPushButton();
		m_pBtnIndex->setFixedHeight(60);
		m_pBtnIndex->setFixedWidth(80);

		pLabelCondition1->setText(tr("开始时间"));
		pLabelCondition2->setText(tr("结束时间"));
		pLabelCondition3->setText(tr("通行窗口"));
		pLabelCondition4->setText(tr("通行方向"));
		pLabelCondition5->setText(tr("车牌号码"));
		pLabelCondition6->setText(tr("用户名"));
		pLabelCondition7->setText(tr("检查结果"));
		m_pBtnSearch->setText(tr("搜索"));
		m_pBtnIndex->setText(tr("添加"));

		pGridCondition->addWidget(pLabelCondition1, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pStartTime,     0, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition2, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pEndTime,       1, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition3, 2, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pStationId,     2, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition5, 3, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pPlateNumber,   3, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition6, 4, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pUserName,      4, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition7, 5, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pResult,        5, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabelCondition4, 6, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(m_pDirection,     6, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		//pGridCondition->addWidget(m_pBtnIndex,      6, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

		pGridCondition->setHorizontalSpacing(6);
		pGridCondition->setVerticalSpacing(6);
		pGridCondition->setContentsMargins(0, 4, 4, 4);
	}
	//表格
	QHBoxLayout *pLayoutRecord = new QHBoxLayout();
	{
		m_pTableRecord = new QTableWidget();
		{
			m_pTableRecord->setColumnCount(9); //设置列数
			m_pTableRecord->horizontalHeader()->setDefaultSectionSize(150);
			//设置表头内容
			QStringList header;
			header << tr("索引")
				<< tr("站点")
				<< tr("方向")
				<< tr("车牌号")
				<< tr("用户名")
				<< tr("余额")
				<< tr("检测")
				<< tr("时间")
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
			m_pTableRecord->setColumnWidth(0, 50);
			m_pTableRecord->setColumnWidth(1, 50);
			m_pTableRecord->setColumnWidth(2, 50);
			m_pTableRecord->setColumnWidth(3, 60);
			m_pTableRecord->setColumnWidth(4, 60);
			m_pTableRecord->setColumnWidth(5, 50);
			m_pTableRecord->setColumnWidth(6, 100);
			m_pTableRecord->setColumnWidth(7, 120);
			m_pTableRecord->setColumnWidth(8, 70);
			m_pTableRecord->hideColumn(0);                                                                  //隐藏第一列索引
			m_pTableRecord->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);                           //关闭水平滚动条
			m_pTableRecord->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);                              //打开垂直滚动条                                                                        
			m_pTableRecord->setContextMenuPolicy(Qt::CustomContextMenu);                                    //设置右键菜单
		}
		pLayoutRecord->addWidget(m_pTableRecord);
	}
	//图片
	QWidget *pWidgetScanImage = new QWidget(this);
	{
		pWidgetScanImage->setFixedSize(400, 316);
		QGroupBox *pGroupScanImage = new QGroupBox(pWidgetScanImage);
		{
			pGroupScanImage->setGeometry(0, 0, 400, 316);
			pGroupScanImage->setTitle(tr("抓拍"));
			pGroupScanImage->setStyleSheet(QLatin1String("QGroupBox {\n"
				"		border-width:2px;\n"
				"		border-style:solid;\n"
				"		border-color:lightGray;\n"
				"		margin-top:0.5ex;\n"
				"		}\n"
				"QGroupBox::title{\n"
				"		subcontrol-origin: margin;\n"
				"		subcontrol-position: top left;\n"
				"		left:25px;\n"
				"		margin-left: 0px;\n"
				"		padding:0 1px;\n"
				"		}"));
			m_pLabelScanImage = new QLabel(pGroupScanImage);
			m_pLabelScanImage->setText(tr("抓拍"));
			m_pLabelScanImage->setGeometry(0, 16, 400, 300);
			QPixmap pixmap("./EtcInfo/123.jpg");
			pixmap = pixmap.scaled(400, 300);
			//m_pLabelScanImage->setPixmap(QPixmap("./EtcInfo/123.jpg"));
			//m_pLabelScanImage->setPixmap(QPixmap("./EtcInfo/123.jpg"));
			m_pLabelScanImage->setPixmap(QPixmap("./Resources/anidog01.jpg"));
		}
	}
	QGridLayout *m_pGridLayout = new QGridLayout(); //布局器
	{
		m_pGridLayout->addLayout(pLayoutRecord,    0, 0, 9, 9, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(pWidgetScanImage, 0, 9, 6, 6, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addLayout(pGridCondition,   6, 9, 3, 3, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(m_pBtnSearch,     7, 13, 1, 1, Qt::AlignLeft | Qt::AlignTop);
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

void dbWidget::initConnect(void)
{
	connect(m_pBtnIndex, &QPushButton::clicked, this, &dbWidget::on_btnInsertClick);
	connect(m_pBtnSearch, &QPushButton::clicked, this, &dbWidget::on_btnSearchClick);
	connect(m_pTableRecord, &QTableWidget::customContextMenuRequested, this, &dbWidget::onMenuRequested);
	connect(m_pActionDeleteItm, &QAction::triggered, this, &dbWidget::onActionDeleteItm);
	connect(m_pTableRecord, &QTableWidget::itemClicked, this, &dbWidget::onTableRecordItemClicked);
}

void dbWidget::wheelEvent(QWheelEvent * mWhellEvent)
{
	SearchOption mOption;
	mOption.StartTime = m_pStartTime->text();
	mOption.EndTime = m_pEndTime->text();
	mOption.StationId = m_pStationId->currentText();
	mOption.PlateNumber = m_pPlateNumber->text();
	mOption.UserName = m_pUserName->text();
	mOption.Result = m_pResult->currentText();
	mOption.Direction = m_pDirection->currentText();

	int pos = m_stepCount - 16 - m_RemoveItemSize; //触发下翻滚轮信号的值，16是一个表格视窗的大小
	if (pos == m_pTableRecord->verticalScrollBar()->value())//下翻查看
	{
		m_begingIndex = m_begingIndex + pos; //更新
		if (mWhellEvent->delta() < 0) //下滑滚轮
		{
			m_RemoveItemSize = 0;
			bool bRet = DBManager::getInstance()->getinspectRecordList(mOption, m_begingIndex, m_stepCount, m_pRecordList);
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
				DBManager::getInstance()->getinspectRecordList(mOption, m_begingIndex, m_stepCount, m_pRecordList);
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
