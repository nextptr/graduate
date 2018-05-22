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
	bool insertinspectRecord(etcRecord *pRecord);	//添加检测记录
	bool insertChargeRecord(chargeRecord *pRecord);	//添加检测记录
	bool modifyinspectRecord(const etcRecord &record);	//修改记录
	bool modifyChargeRecord(const chargeRecord &record);	//修改记录
	bool deleteinspectRecord(int id);	//删除记录
	bool deleteChargeRecord(int id);	//删除记录
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
	static CGarbo m_CGarbo; //定义一个静态成员，程序结束时，系统会自动调用它的析构函数
protected:
	void run();
};


#endif // DBMANGER_H
