#ifndef ETCRECORD_H
#define ETCRECORD_H

#include <QObject>

enum UpOrDown { up, down, deful };  //�����ʾ��ģʽ


class SearchOption
{
public:

	QString StartTime;	//��ʼʱ��
	QString EndTime;	//����ʱ��
	QString PlateNumber;//���ƺ� 
	QString UserName;   //�û��� 
	QString Result;   	//�����
	QString StationId;	//��վ���
	QString Direction;	//����

	SearchOption()
	{
		reset();
	}

	void reset()
	{
		StartTime = "";
		EndTime = "";
		StationId = "";
		PlateNumber = "";
		UserName = "";
		Result = "";
		Direction = "";
	}
};

class etcRecord : public QObject
{
	Q_OBJECT

public:
	int id;

	QString DetectionTime;	//��ʼʱ��
	QString PlateNumber;    //���ƺ� 
	QString UserName;       //�û��� 
	QString Direction;	    //����
	QString Result;   	    //�����
	QString Money;   	    //���
	QString StationId;	    //��վ���
	QString Remark;	        //��ע

public:
	etcRecord(QObject *parent);
	~etcRecord();
	etcRecord()
	{
		reset();
	}
	void reset()
	{
		id = 0;
		DetectionTime = "";
		PlateNumber = "";
		UserName = "";
		Direction = "";
		Result = "";
		Money = "";
		StationId = "";
		Remark = "";
	}
	etcRecord(const etcRecord & record)
	{
		id = record.id;
		DetectionTime = record.DetectionTime;
		PlateNumber = record.PlateNumber;
		UserName = record.UserName;
		Direction = record.Direction;
		Result = record.Result;
		Money = record.Money;
		StationId = record.StationId;
		Remark = record.Remark;
	}
	etcRecord& operator= (const etcRecord &instance)
	{
		this->id = instance.id;
		this->DetectionTime = instance.DetectionTime;
		this->PlateNumber = instance.PlateNumber;
		this->UserName = instance.UserName;
		this->Direction = instance.Direction;
		this->Result = instance.Result;
		this->Money = instance.Money;
		this->StationId = instance.StationId;
		this->Remark = instance.Remark;
		return *this;
	}
private:
	
};

class chargeRecord : public QObject
{
	Q_OBJECT

public:
	int id;                 //����
	QString PlateNumber;    //���ƺ� 
	QString UserName;       //�û��� 
	QString Time;	        //��ʼʱ��
	QString Payout;	        //֧��
	QString Income;   	    //��ֵ
	QString Balance;	    //���
	QString Remark;	        //��ע


public:
	chargeRecord(QObject *parent);
	~chargeRecord();
	chargeRecord()
	{
		reset();
	}
	void reset()
	{
		id = 0;
		PlateNumber = "";
		UserName = "";
		Time = "";
		Payout = "";
		Balance = "";
		Income = "";
		Remark = "";
	}
	chargeRecord(const chargeRecord & record)
	{
		id = record.id;
		PlateNumber = record.PlateNumber;
		UserName = record.UserName;
		Time = record.Time;
		Payout = record.Payout;
		Balance = record.Balance;
		Income = record.Income;
		Remark = record.Remark;
	}
	chargeRecord& operator= (const chargeRecord &instance)
	{
		this->id = instance.id;
		this->PlateNumber = instance.PlateNumber;
		this->UserName = instance.UserName;
		this->Time = instance.Time;
		this->Payout = instance.Payout;
		this->Income = instance.Income;
		this->Balance = instance.Balance;
		this->Remark = instance.Remark;
		return *this;
	}
private:
};

etcRecord * getInspectRecord(QList<etcRecord> *pList, int id);
chargeRecord* getChargeRecord(QList<chargeRecord>* pList, int id);
void modifyList(QList<etcRecord>* pList, etcRecord &record);
void modifyList(QList<chargeRecord>* pList, chargeRecord &record);
void eraseArecord(QList<etcRecord>* pList, int index);
void eraseArecord(QList<chargeRecord>* pList, int index);

#endif // ETCRECORD_H
