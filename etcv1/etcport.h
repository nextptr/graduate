#ifndef ETCPORT_H
#define ETCPORT_H
#pragma execution_character_set("utf-8")  

#include "etcconfiger.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushbutton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QTextEdit>


class etcPortWidget : public QWidget
{
	Q_OBJECT

public:
	void initWidget(void);
	void initConnect(void);
	etcPortWidget();
	~etcPortWidget();
public Q_SLOTS:
    void on_btnShowClick(void);
	void on_btnKeyClick(void);
	void on_btnGoClick(void);
	void on_btnBackClick(void);
	void on_btnLeftClick(void);
	void on_btnReightClick(void);
	void on_btnStopClick(void);
	void AutoRecvDate(void);
signals:
    void PositionSignal(pocket);

private:

	QByteArray* lastbuf;

	bool portFlag;
	QSerialPort mySeriaPort;

	QComboBox*portBox;
	QComboBox*bundBox;
	QComboBox*bitnumBox;
	QComboBox*parityBox;
	QComboBox*stopBox;

	QPushButton*m_btnKey;

	QPushButton*m_btnGo;
	QPushButton*m_btnBack;
	QPushButton*m_btnLeft;
	QPushButton*m_btnReight;
	QPushButton*m_btnStop;

};

#endif // ETCPORT_H
