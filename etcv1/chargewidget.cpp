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
		showTable(up);        //��ʾ
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
	if (1 == col) //�����޸�����һ��
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
	modifyList(m_pRecordList, *tmpRecord);   //�޸�record
	DBManager::getInstance()->modifyinspectRecord(tmpRecord);//�޸����ݿ�
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
	DBManager::getInstance()->deleteChargeRecord(m_pTableRecord->item(row, 0)->text().toInt());        //���ݿ�ɾ����¼
	eraseArecord(m_pRecordList, row);       				//ɾ��list��Ӧrecord
	m_pTableRecord->removeRow(row);                         //ɾ����񲿼���Ӧ��
}

void chargeWidget::onTableRecordItemClicked(QTableWidgetItem * pItem)
{
	int id = m_pTableRecord->item(pItem->row(), 0)->text().toInt();
	if (m_lastCliskItemId != id)
	{
		m_lastCliskItemId = id;
		//��ʾͼƬ
		/*HistoryRecord tmpRecord;
		if (m_HisManager.getAutomobRecord(&m_HisManager.m_HistoryRecordList, id, &tmpRecord))
		{
		showRecord(tmpRecord);
		}*/
	}
}

chargeWidget::chargeWidget()
{
	m_begingIndex = 0;      //��ѯ���
	m_stepCount = 36;        //���β�ѯ����
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
	disconnect(m_pTableRecord, &QTableWidget::cellChanged, this, &chargeWidget::onCellChange); //�Ͽ��޸Ĳ�����
	
	m_pTableRecord->clear();
	m_pTableRecord->setRowCount(m_pRecordList->size());
	QStringList header;
	header << tr("����")
		<< tr("���ƺ�")
		<< tr("�û���")
		<< tr("ʱ��")
		<< tr("�۷�")
		<< tr("��ֵ")
		<< tr("���")
		<< tr("��ע");
	m_pTableRecord->setHorizontalHeaderLabels(header);
	for (int count = 0;count < m_pRecordList->size();count++)
	{
		chargeRecord tmp = m_pRecordList->at(count);
		/*���������� �����޸����ݿ�*/
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
	//������
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

		pLabelCondition1->setText(tr("���ƺ�"));
		pLabelCondition2->setText(tr("�û���"));
		pLabelCondition3->setText(tr("��ʼʱ��"));
		pLabelCondition4->setText(tr("����ʱ��"));
		m_pBtnSearch->setText(tr("����"));
		m_pBtnCharge->setText(tr("��ֵ"));

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
	//���
	QHBoxLayout *pLayoutRecord = new QHBoxLayout();
	{
		m_pTableRecord = new QTableWidget();
		{
			m_pTableRecord->setColumnCount(8); //��������
			m_pTableRecord->horizontalHeader()->setDefaultSectionSize(150);
			//���ñ�ͷ����
			QStringList header;
			header << tr("����")
				<< tr("���ƺ�")
				<< tr("�û���")
				<< tr("ʱ��")
				<< tr("�۷�")
				<< tr("��ֵ")
				<< tr("���")
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
			m_pTableRecord->setColumnWidth(0, 100);
			m_pTableRecord->setColumnWidth(1, 70);
			m_pTableRecord->setColumnWidth(2, 70);
			m_pTableRecord->setColumnWidth(3, 110);
			m_pTableRecord->setColumnWidth(4, 90);
			m_pTableRecord->setColumnWidth(5, 90);
			m_pTableRecord->setColumnWidth(6, 90);
			m_pTableRecord->setColumnWidth(7, 90);
			m_pTableRecord->hideColumn(0);                                                                  //���ص�һ������
			m_pTableRecord->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);                           //�ر�ˮƽ������
			m_pTableRecord->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);                              //�򿪴�ֱ������ 
			m_pTableRecord->setContextMenuPolicy(Qt::CustomContextMenu);                                    //�����Ҽ��˵�
		}
		pLayoutRecord->addWidget(m_pTableRecord);
	}
	QGridLayout *m_pGridLayout = new QGridLayout(); //������
	{
		m_pGridLayout->addLayout(pGridCondition, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addLayout(pLayoutRecord, 1, 0, 9, 1, Qt::AlignLeft | Qt::AlignTop);
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
	int pos = m_stepCount - 10 - m_RemoveItemSize; //�����·������źŵ�ֵ��9��һ������Ӵ��Ĵ�С
	if (pos == m_pTableRecord->verticalScrollBar()->value())//�·��鿴
	{
		m_begingIndex = m_begingIndex + pos; //����
		if (mWhellEvent->delta() < 0) //�»�����
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