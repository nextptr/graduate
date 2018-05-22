#ifndef DBMANGER_H
#define DBMANGER_H

#include "etcrecord.h"
#include "etccar.h"

#include <QThread>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMutex>


class DBManager : public QThread
{
	Q_OBJECT

public:
	static DBManager*getInstance(void);
	bool getinspectRecordList(const SearchOption option, int iIndex, int iCount, QList<etcRecord> *m_plist);
	bool getChargeRecordList(const chargeRecord option, int iIndex, int iCount, QList<chargeRecord> *m_plist);
	bool insertinspectRecord(etcRecord *pRecord);	//��Ӽ���¼
	bool insertChargeRecord(chargeRecord *pRecord);	//��Ӽ���¼
	bool modifyinspectRecord(const etcRecord &record);	//�޸ļ�¼
	bool modifyChargeRecord(const chargeRecord &record);	//�޸ļ�¼
	bool deleteinspectRecord(int id);	//ɾ����¼
	bool deleteChargeRecord(int id);	//ɾ����¼
	void initCarBalance(etcCar*SmartCar);

private:
	static DBManager*m_pInstance;
	QSqlDatabase m_db;
	bool m_isQuit;

	explicit DBManager(QObject *parent = 0);
	~DBManager(void);
	bool init(void);
	bool openDataBase(const QString&strFileName);
	bool isexittable(const QString&strtablename);
	void closedatabase();
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (DBManager::m_pInstance)
			{
				delete DBManager::m_pInstance;
			}
		}
	};
	static CGarbo m_CGarbo; //����һ����̬��Ա���������ʱ��ϵͳ���Զ�����������������
protected:
	void run();
};


#endif // DBMANGER_H
