#include "etcport.h"
#include <QPixmap>
#include <QDebug>

etcPortWidget::etcPortWidget()
{
	lastbuf = new QByteArray;
	portFlag = false;
	initWidget();
	initConnect();
}

etcPortWidget::~etcPortWidget()
{

}

void etcPortWidget::on_btnKeyClick(void)
{
	if(false == portFlag)
	{
		m_btnKey->setText("��");//�Ѿ��򿪴����´�ֻ�ܹر�
		
		mySeriaPort.setPortName(portBox->currentText()); //���ں�
		mySeriaPort.open(QIODevice::ReadWrite);
		mySeriaPort.setBaudRate(bundBox->currentText().toInt());//������
		switch (bitnumBox->currentText().toInt())//����λ
		{
		case 8:
			mySeriaPort.setDataBits(QSerialPort::Data8);
			break;
		default: break;
		}
		switch (parityBox->currentText().toInt())//У��λ
		{
		case 0:
			mySeriaPort.setParity(QSerialPort::NoParity);
			break;
		default:break;
		}
		switch (stopBox->currentText().toInt())//ֹͣλ
		{
		case 1:
			mySeriaPort.setStopBits(QSerialPort::OneStop);
			break;
		case 2:
			mySeriaPort.setStopBits(QSerialPort::TwoStop);
			break;
		default:break;
		}
		mySeriaPort.setFlowControl(QSerialPort::NoFlowControl);//��������
		//�ر����ÿ�
		portBox->setEnabled(false);
		bundBox->setEnabled(false);
		bitnumBox->setEnabled(false);
		parityBox->setEnabled(false);
		stopBox->setEnabled(false);
		portFlag = true;
	}
	else
	{
		m_btnKey->setText("��"); //�رմ��ڣ��´δ�
		mySeriaPort.clear();
		mySeriaPort.close();
		//mySerialport.deleteLater();
		//�ָ�����ʹ��
		portBox->setEnabled(true);
		bundBox->setEnabled(true);
		bitnumBox->setEnabled(true);
		parityBox->setEnabled(true);
		stopBox->setEnabled(true);
		portFlag = false;
	}
}

void etcPortWidget::on_btnGoClick(void)
{
	QString str = "0x01";
	QByteArray str2 = QByteArray::fromHex(str.toLatin1().data());//��ʮ�����Ʊ��������
	qDebug() << " byte " << str2;
	mySeriaPort.write(str2);
}

void etcPortWidget::on_btnBackClick(void)
{
	QString str = "0x03";
	QByteArray str2 = QByteArray::fromHex(str.toLatin1().data());//��ʮ�����Ʊ��������
	mySeriaPort.write(str2);
}

void etcPortWidget::on_btnLeftClick(void)
{
	QString str = "0x02";
	QByteArray str2 = QByteArray::fromHex(str.toLatin1().data());//��ʮ�����Ʊ��������
	mySeriaPort.write(str2);
}

void etcPortWidget::on_btnReightClick(void)
{
	QString str = "0x04";
	QByteArray str2 = QByteArray::fromHex(str.toLatin1().data());//��ʮ�����Ʊ��������
	mySeriaPort.write(str2);
}

void etcPortWidget::on_btnStopClick(void)
{
	QString str = "0x05";
	QByteArray str2 = QByteArray::fromHex(str.toLatin1().data());//��ʮ�����Ʊ��������
	mySeriaPort.write(str2);
}

void etcPortWidget::AutoRecvDate(void)
{
	QByteArray buf;
	QByteArray tmpbuf;

	pocket pok;
	int card;
	buf = mySeriaPort.readAll(); //�Ӵ����ж�ȡ���ݵ�buf
	//qDebug() << " orbufsiz  " << buf.size() << " orbuf " << buf;
	qDebug() << "RFID��ǩ��Ϣ  " << buf;
	if (!buf.isEmpty())
	{
		if (buf.size() != 12)
		{
			//qDebug() << "las " << lastbuf->size() << " now " << buf.size();
			if (lastbuf->size() + buf.size() == 12)
			{
				tmpbuf = *lastbuf + buf;
				buf = tmpbuf;
				lastbuf->clear();
				//qDebug() << " sz " << lastbuf->size() + buf.size() << " bufsiz  " << buf.size() << " buf " << buf;
				card = buf[10] & 0x000000FF;
				qDebug() <<"RFID��ǩ��Ϣ���� "<< buf[8] << buf[9] << card ;
				pok.roadnam = buf[8];
				pok.roadid = buf[9] & 0x000000FF;
				pok.roidpos = card;
				emit PositionSignal(pok);
			}
			*lastbuf = buf;
		}
		else
		{
			//qDebug() << "bufsiz  " << buf.size() << " buf " << buf;
			card = buf[10] & 0x000000FF;
			qDebug() << "RFID��ǩ��Ϣ���� " << buf[8] << buf[9] << card ;
			pok.roadnam = buf[8];
			pok.roadid = buf[9] & 0x000000FF;
			pok.roidpos = card;
			emit PositionSignal(pok);
		}
	}
	buf.clear();
}

void etcPortWidget::initWidget(void)
{
	this->setFixedSize(450, 280);
	//���ÿ�
	QGridLayout *pGridCondition = new QGridLayout();
	{
		QLabel *pLabel1 = new QLabel(this);
		QLabel *pLabel2 = new QLabel(this);
		QLabel *pLabel3 = new QLabel(this);
		QLabel *pLabel4 = new QLabel(this);
		QLabel *pLabel5 = new QLabel(this);
		pLabel1->setText(tr("����"));
		pLabel2->setText(tr("������"));
		pLabel3->setText(tr("����λ"));
		pLabel4->setText(tr("У��λ"));
		pLabel5->setText(tr("ֹͣλ"));

		portBox = new QComboBox;
		portBox->setFixedWidth(140);
		portBox->setFixedHeight(25);
		foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
		{
			QSerialPort serial; //��ʱ���ڱ���
			serial.setPort(info);
			if (serial.open(QIODevice::ReadWrite))
			{
				portBox->addItem(serial.portName()); //�����ô�����ӵ���Ŀ��
				serial.close();
			}
		}
		bundBox = new QComboBox;
		bundBox->setFixedWidth(140);
		bundBox->setFixedHeight(25);
		bundBox->addItem("9600");
		bundBox->addItem("38400");
		bundBox->addItem("115200");

		bitnumBox = new QComboBox;
		bitnumBox->setFixedWidth(140);
		bitnumBox->setFixedHeight(25);
		bitnumBox->addItem("8");

		parityBox = new QComboBox;
		parityBox->setFixedWidth(140);
		parityBox->setFixedHeight(25);
		parityBox->addItem("0");

		stopBox = new QComboBox;
		stopBox->setFixedWidth(140);
		stopBox->setFixedHeight(25);
		stopBox->addItem("1");
		stopBox->addItem("2");

		m_btnKey = new QPushButton;
		m_btnKey->setText(tr("��"));
		m_btnKey->setFixedHeight(25);

		pGridCondition->addWidget(pLabel1, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(portBox, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabel2, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(bundBox, 1, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabel3, 2, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(bitnumBox, 2, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabel4, 3, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(parityBox, 3, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
		pGridCondition->addWidget(pLabel5, 4, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
		pGridCondition->addWidget(stopBox, 4, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

		pGridCondition->setHorizontalSpacing(10);
		pGridCondition->setVerticalSpacing(10);
		pGridCondition->setContentsMargins(4, 4, 4, 4);

	}
	//��ť��
	{
		m_btnGo = new QPushButton();
		{
			m_btnGo->setObjectName(QStringLiteral("m_pBtnIndex"));
			m_btnGo->setShortcut(QKeySequence("q"));
			m_btnGo->setFixedSize(80, 80);
			m_btnGo->setStyleSheet(QLatin1String("QPushButton{\n"
				"		border-image:url(:/etcv1/Resources/img/go.png);\n"
				"		}\n"
				"QPushButton:pressed{\n"
				"		border-image:url(:/etcv1/Resources/img/btnBack.png);\n"
				"		}"));
			m_btnGo->setAutoDefault(false);
			m_btnGo->setDefault(false);
			m_btnGo->setFlat(false);
		}
		m_btnBack = new QPushButton();
		{
			m_btnBack->setObjectName(QStringLiteral("m_pBtnIndex"));
			m_btnBack->setShortcut(QKeySequence("q"));
			m_btnBack->setFixedSize(80, 80);
			m_btnBack->setStyleSheet(QLatin1String("QPushButton{\n"
				"		border-image:url(:/etcv1/Resources/img/back.png);\n"
				"		}\n"
				"QPushButton:pressed{\n"
				"		border-image:url(:/etcv1/Resources/img/btnBack.png);\n"
				"		}"));
			m_btnBack->setAutoDefault(false);
			m_btnBack->setDefault(false);
			m_btnBack->setFlat(false);
		}
		m_btnLeft = new QPushButton();
		{
			m_btnLeft->setObjectName(QStringLiteral("m_pBtnIndex"));
			m_btnLeft->setShortcut(QKeySequence("q"));
			m_btnLeft->setFixedSize(80, 80);
			m_btnLeft->setStyleSheet(QLatin1String("QPushButton{\n"
				"		border-image:url(:/etcv1/Resources/img/left.png);\n"
				"		}\n"
				"QPushButton:pressed{\n"
				"		border-image:url(:/etcv1/Resources/img/btnBack.png);\n"
				"		}"));
			m_btnLeft->setAutoDefault(false);
			m_btnLeft->setDefault(false);
			m_btnLeft->setFlat(false);
		}
		m_btnReight = new QPushButton();
		{
			m_btnReight->setObjectName(QStringLiteral("m_pBtnIndex"));
			m_btnReight->setShortcut(QKeySequence("q"));
			m_btnReight->setFixedSize(80, 80);
			m_btnReight->setStyleSheet(QLatin1String("QPushButton{\n"
				"		border-image:url(:/etcv1/Resources/img/reight.png);\n"
				"		}\n"
				"QPushButton:pressed{\n"
				"		border-image:url(:/etcv1/Resources/img/btnBack.png);\n"
				"		}"));
			m_btnReight->setAutoDefault(false);
			m_btnReight->setDefault(false);
			m_btnReight->setFlat(false);
		}
		m_btnStop = new QPushButton();
		{
			m_btnStop->setObjectName(QStringLiteral("m_pBtnIndex"));
			m_btnStop->setShortcut(QKeySequence("q"));
			m_btnStop->setFixedSize(80, 80);
			m_btnStop->setStyleSheet(QLatin1String("QPushButton{\n"
				"		border-image:url(:/etcv1/Resources/img/stop.png);\n"
				"		}\n"
				"QPushButton:pressed{\n"
				"		border-image:url(:/etcv1/Resources/img/btnBack.png);\n"
				"		}"));
			m_btnStop->setAutoDefault(false);
			m_btnStop->setDefault(false);
			m_btnStop->setFlat(false);
		}
	}

	QGridLayout *m_pGridLayout = new QGridLayout(); //������
	{
		m_pGridLayout->addLayout(pGridCondition, 0, 0, 6, 4, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(m_btnGo, 0, 6, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(m_btnLeft, 2, 4, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(m_btnBack, 4, 6, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(m_btnReight, 2, 8, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(m_btnStop, 2, 6, 1, 1, Qt::AlignLeft | Qt::AlignTop);
		m_pGridLayout->addWidget(m_btnKey, 4, 1, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);
	}
	this->setLayout(m_pGridLayout);

	m_pGridLayout->setHorizontalSpacing(4);// ����ˮƽ���
	m_pGridLayout->setVerticalSpacing(4);	// ���ô�ֱ���
	m_pGridLayout->setContentsMargins(0, 0, 0, 0);
}

void etcPortWidget::initConnect()
{
	connect(m_btnKey,    &QPushButton::clicked, this, &etcPortWidget::on_btnKeyClick);
	connect(m_btnGo,     &QPushButton::clicked, this, &etcPortWidget::on_btnGoClick);
	connect(m_btnBack,   &QPushButton::clicked, this, &etcPortWidget::on_btnBackClick);
	connect(m_btnLeft,   &QPushButton::clicked, this, &etcPortWidget::on_btnLeftClick);
	connect(m_btnReight, &QPushButton::clicked, this, &etcPortWidget::on_btnReightClick);
	connect(m_btnStop,   &QPushButton::clicked, this, &etcPortWidget::on_btnStopClick);
	connect(&mySeriaPort, &QSerialPort::readyRead, this, &etcPortWidget::AutoRecvDate);
}

void etcPortWidget::on_btnShowClick()
{
	this->hide();
	this->show();
}