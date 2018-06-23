#include "dbwidget.h"
#include "dbmanger.h"
#include <QDebug>

dbWidget::dbWidget()
{

	m_begingIndex = 0;       //��ѯ���
	m_stepCount = 36;        //���β�ѯ����
	m_RemoveItemSize = 0;    //�Ѿ�ɾ����Ŀ����
	m_lastCliskItemId = 0;   //�������Ŀid
	initWidget();
	initConnect();
}

dbWidget::~dbWidget()
{

}

void dbWidget::on_btnSearchClick()
{
	//m_begingIndex = 0;     //��ť�������ʼ����ʼ��    
	//m_RemoveItemSize = 0;//��ʼ����ɾ����Ŀ����
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
		showTable(up);        //��ʾ
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
	if (1 == col) //�����޸�����һ��
	{   
		tmpRecord->StationId = m_pTableRecord->item(row, col)->text();
	}
	if (2 == col) //�����޸�����һ��
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

	modifyList(m_pRecordList, *tmpRecord);   //�޸�record

	DBManager::getInstance()->modifyinspectRecord(*tmpRecord);//�޸����ݿ�

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
	DBManager::getInstance()->deleteinspectRecord(m_pTableRecord->item(row, 0)->text().toInt());        //���ݿ�ɾ����¼
	eraseArecord(m_pRecordList, row);       				//ɾ��list��Ӧrecord
	m_pTableRecord->removeRow(row);                         //ɾ����񲿼���Ӧ��
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
	disconnect(m_pTableRecord, &QTableWidget::cellChanged, this, &dbWidget::onCellChange); //�Ͽ��޸Ĳ�����

	m_pTableRecord->clear();
	m_pTableRecord->setRowCount(m_pRecordList->size());
	QStringList header;
	header << tr("����")
		<< tr("վ��")
		<< tr("����")
		<< tr("���ƺ�")
		<< tr("�û���")
		<< tr("���")
		<< tr("���")
		<< tr("ʱ��")
		<< tr("��ע");
	m_pTableRecord->setHorizontalHeaderLabels(header);

	for (int count = 0;count < m_pRecordList->size();count++)
	{
		etcRecord tmp = m_pRecordList->at(count);
		/*���������� �����޸����ݿ�*/
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
	//������
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
		strings << tr("") << tr("����") << tr("�뿪");
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
		strings << tr("") << tr("����") << tr("�쳣");
		m_pResult->addItems(strings);

		m_pBtnSearch = new QPushButton();
		m_pBtnSearch->setFixedHeight(60);
		m_pBtnSearch->setFixedWidth(80);

		m_pBtnIndex= new QPushButton();
		m_pBtnIndex->setFixedHeight(60);
		m_pBtnIndex->setFixedWidth(80);

		pLabelCondition1->setText(tr("��ʼʱ��"));
		pLabelCondition2->setText(tr("����ʱ��"));
		pLabelCondition3->setText(tr("ͨ�д���"));
		pLabelCondition4->setText(tr("ͨ�з���"));
		pLabelCondition5->setText(tr("���ƺ���"));
		pLabelCondition6->setText(tr("�û���"));
		pLabelCondition7->setText(tr("�����"));
		m_pBtnSearch->setText(tr("����"));
		m_pBtnIndex->setText(tr("���"));

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
	//���
	QHBoxLayout *pLayoutRecord = new QHBoxLayout();
	{
		m_pTableRecord = new QTableWidget();
		{
			m_pTableRecord->setColumnCount(9); //��������
			m_pTableRecord->horizontalHeader()->setDefaultSectionSize(150);
			//���ñ�ͷ����
			QStringList header;
			header << tr("����")
				<< tr("վ��")
				<< tr("����")
				<< tr("���ƺ�")
				<< tr("�û���")
				<< tr("���")
				<< tr("���")
				<< tr("ʱ��")
				<< tr("��ע");
			m_pTableRecord->setHorizontalHeaderLabels(header);
			m_pTableRecord->horizontalHeader()->setFixedHeight(32);											//���ñ�ͷ�ĸ߶�
			m_pTableRecord->verticalHeader()->setDefaultSectionSize(32);									//�����и�
			m_pTableRecord->verticalHeader()->setVisible(false);											//���ô�ֱͷ���кţ����ɼ�
			//m_pTableRecord->setFrameShape(QFrame::NoFrame);												//�����ޱ߿�
			m_pTableRecord->setShowGrid(true);																//������ʾ������
			m_pTableRecord->setSelectionMode(QAbstractItemView::ExtendedSelection);							//�ɶ�ѡ��Ctrl��Shift��  Ctrl+A�����ԣ�
			m_pTableRecord->setSelectionBehavior(QAbstractItemView::SelectRows);							//����ѡ����Ϊʱÿ��ѡ��һ��
			//m_pTableRecord->setSelectionMode(QAbstractItemView::SingleSelection);                         //����Ϊ����ѡ�е���
			m_pTableRecord->setEditTriggers(QAbstractItemView::DoubleClicked);                              //˫���༭
			m_pTableRecord->setStyleSheet("selection-background-color:lightblue;");							//����ѡ�б���ɫ
			m_pTableRecord->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");	//���ñ�ͷ����ɫ
			// column width
			//m_pTableRecord->horizontalHeader()->resizeSection(0, 150);									//���ñ�ͷ��һ�еĿ��Ϊ150
			//m_pTableRecord->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);				//���ȿ�
			m_pTableRecord->setColumnHidden(10, true);
			m_pTableRecord->horizontalHeader()->setStretchLastSection(true);								//���ó�������
			m_pTableRecord->setColumnWidth(0, 50);
			m_pTableRecord->setColumnWidth(1, 50);
			m_pTableRecord->setColumnWidth(2, 50);
			m_pTableRecord->setColumnWidth(3, 60);
			m_pTableRecord->setColumnWidth(4, 60);
			m_pTableRecord->setColumnWidth(5, 50);
			m_pTableRecord->setColumnWidth(6, 100);
			m_pTableRecord->setColumnWidth(7, 120);
			m_pTableRecord->setColumnWidth(8, 70);
			m_pTableRecord->hideColumn(0);                                                                  //���ص�һ������
			m_pTableRecord->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);                           //�ر�ˮƽ������
			m_pTableRecord->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);                              //�򿪴�ֱ������                                                                        
			m_pTableRecord->setContextMenuPolicy(Qt::CustomContextMenu);                                    //�����Ҽ��˵�
		}
		pLayoutRecord->addWidget(m_pTableRecord);
	}
	//ͼƬ
	QWidget *pWidgetScanImage = new QWidget(this);
	{
		pWidgetScanImage->setFixedSize(400, 316);
		QGroupBox *pGroupScanImage = new QGroupBox(pWidgetScanImage);
		{
			pGroupScanImage->setGeometry(0, 0, 400, 316);
			pGroupScanImage->setTitle(tr("ץ��"));
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
			m_pLabelScanImage->setText(tr("ץ��"));
			m_pLabelScanImage->setGeometry(0, 16, 400, 300);
			QPixmap pixmap("./EtcInfo/123.jpg");
			pixmap = pixmap.scaled(400, 300);
			//m_pLabelScanImage->setPixmap(QPixmap("./EtcInfo/123.jpg"));
			//m_pLabelScanImage->setPixmap(QPixmap("./EtcInfo/123.jpg"));
			m_pLabelScanImage->setPixmap(QPixmap("./Resources/anidog01.jpg"));
		}
	}
	QGridLayout *m_pGridLayout = new QGridLayout(); //������
	{
		m_pGridLayout->addLayout(pLayoutRecord,    0, 0, 9, 9, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(pWidgetScanImage, 0, 9, 6, 6, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addLayout(pGridCondition,   6, 9, 3, 3, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(m_pBtnSearch,     7, 13, 1, 1, Qt::AlignLeft | Qt::AlignTop);
	}
	this->setLayout(m_pGridLayout);
	m_pGridLayout->setHorizontalSpacing(4);// ����ˮƽ���
	m_pGridLayout->setVerticalSpacing(4);	// ���ô�ֱ���
	m_pGridLayout->setContentsMargins(0, 0, 0, 0);

	{
		m_pMenu = new QMenu();               //�Ҽ��˵���ʼ��
		m_pActionDeleteItm = new QAction(this);
		m_pActionDeleteItm->setText(tr("ɾ��"));
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

	int pos = m_stepCount - 16 - m_RemoveItemSize; //�����·������źŵ�ֵ��16��һ������Ӵ��Ĵ�С
	if (pos == m_pTableRecord->verticalScrollBar()->value())//�·��鿴
	{
		m_begingIndex = m_begingIndex + pos; //����
		if (mWhellEvent->delta() < 0) //�»�����
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
	if (0 == m_pTableRecord->verticalScrollBar()->value())  //�Ϸ��鿴
	{
		if (m_begingIndex > 0) //m_begingIndex>0�����·���
		{
			if (mWhellEvent->delta() > 0)  //���Ϲ���
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
