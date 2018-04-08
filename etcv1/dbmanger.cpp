#include "dbmanger.h"
#include <QMutex>
#include <QSqlQuery>
#include <QDir>
#include <QFile>
#include <QVariant>
#include <QDebug>

static QMutex s_MutexConstr;
DBManager *DBManager::m_pInstance = NULL;

DBManager::DBManager(QObject *parent)
	: QThread(parent)
	, m_isQuit(false)
{
	if (!init())
	{
		;
	}
}
DBManager::~DBManager()
{

}
bool DBManager::init(void)
{
	if (!openDataBase("VehicleManagement.db"))
	{
		qDebug() << "openDatabase failed.";
		return false;
	}

	if (!isexittable("inspectionrecord"))
	{
		//创建数据进出口检测表  
		QSqlQuery sqlQuery;
		QString sql_create_inspectionrecord = "CREATE TABLE inspectionrecord(\
			id INTEGER PRIMARY KEY AUTOINCREMENT,\
			detectiontime varchar,\
			platenumber varchar,\
			username varchar,\
			direction varchar,\
			result varchar,\
			money varchar,\
			stationid varchar,\
            remark varchar)";
		sqlQuery.prepare(sql_create_inspectionrecord); //创建表  
		if (!sqlQuery.exec()) //查看创建表是否成功  
		{
			qDebug() << QObject::tr("Table Create failed");
			qDebug() << sqlQuery.lastError();
			return false;
		}
		else
		{
			qDebug() << "Table Created";
		}
	}
	if (!isexittable("chargerecord"))
	{
		//创建收费管理表
		QSqlQuery sqlQuery;
		QString sql_create_automobilerecord = "CREATE TABLE chargerecord(\
			id INTEGER PRIMARY KEY AUTOINCREMENT,\
			platenumber varchar,\
			username varchar,\
			time varchar,\
			payout varchar,\
			income varchar,\
			balance varchar,\
            remark varchar)";
		sqlQuery.prepare(sql_create_automobilerecord);
		if (!sqlQuery.exec())
		{
			qDebug() << QObject::tr("Table Create failed");
			qDebug() << sqlQuery.lastError();
			return false;
		}
		else
		{
			qDebug() << "Table Created";
		}
	}
	return true;
}
bool DBManager::getinspectRecordList(const SearchOption option, int iIndex, int iCount, QList<etcRecord>* m_plist)
{
	QSqlQuery sqlQuery(m_db);
	QString sqlSearch;
	m_plist->clear();

	//设置搜索语句
	sqlSearch += QString("SELECT * FROM inspectionrecord WHERE detectiontime ");
	if ("" != option.StartTime)
	{
		sqlSearch += QString("> '");
		sqlSearch += option.StartTime;
	}
	else
	{
		sqlSearch += QString("> '1970-01-01 ");
	}

	if ("" != option.EndTime)
	{
		sqlSearch += QString("' and detectiontime < '");
		sqlSearch += option.EndTime;
	}
	else
	{
		sqlSearch += QString("' and detectiontime <' 2999-12-31 ");
	}

	if ("" != option.PlateNumber)
	{
		sqlSearch += QString("' and platenumber='");
		sqlSearch += option.PlateNumber;
	}

	if ("" != option.UserName)
	{
		sqlSearch += QString("' and username='");
		sqlSearch += option.UserName;
	}

	if ("" != option.Result)
	{
		sqlSearch += QString("' and result='");
		sqlSearch += option.Result;
	}

	if ("" != option.StationId)
	{
		sqlSearch += QString("' and stationid='");
		sqlSearch += option.StationId;
	}

	if ("" != option.Direction)
	{
		sqlSearch += QString("' and direction= '");
		sqlSearch += option.Direction;
	}

	sqlSearch += QString("' order by platenumber asc limit '%1','%2';").arg(iIndex).arg(iCount);


	//查询进出口检测表
	sqlQuery.prepare(sqlSearch);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	else
	{
		while (sqlQuery.next())
		{
			etcRecord tmp;
			tmp.id = sqlQuery.value(0).toInt();
			tmp.DetectionTime = sqlQuery.value(1).toString();
			tmp.PlateNumber = sqlQuery.value(2).toString();
			tmp.UserName = sqlQuery.value(3).toString();
			tmp.Direction = sqlQuery.value(4).toString();
			tmp.Result = sqlQuery.value(5).toString();
			tmp.Money = sqlQuery.value(6).toString();
			tmp.StationId = sqlQuery.value(7).toString();
			tmp.Remark = sqlQuery.value(8).toString();
			m_plist->append(tmp);
		}
	}

	return true;
}
bool DBManager::getChargeRecordList(const chargeRecord option, int iIndex, int iCount, QList<chargeRecord> *m_plist)
{
	QSqlQuery sqlQuery(m_db);
	QString sqlSearch;
	m_plist->clear();
	//设置搜索语句
	sqlSearch += QString("SELECT * FROM chargerecord WHERE time ");
	if ("" != option.Time)
	{
		sqlSearch += QString("> '");
		sqlSearch += option.Time;
	}
	else
	{
		sqlSearch += QString("> '1970-01-01 ");
	}

	if ("" != option.Remark)
	{
		sqlSearch += QString("' and time < '");
		sqlSearch += option.Remark;
	}
	else
	{
		sqlSearch += QString("' and time <' 2999-12-31 ");
	}

	if ("" != option.PlateNumber)
	{
		sqlSearch += QString("' and platenumber='");
		sqlSearch += option.PlateNumber;
	}

	if ("" != option.UserName)
	{
		sqlSearch += QString("' and username='");
		sqlSearch += option.UserName;
	}
	sqlSearch += QString("' order by platenumber asc limit '%1','%2';").arg(iIndex).arg(iCount);
	//查询进出口检测表
	sqlQuery.prepare(sqlSearch);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	else
	{
		while (sqlQuery.next())
		{
			chargeRecord tmp;
			tmp.id = sqlQuery.value(0).toInt();
			tmp.PlateNumber = sqlQuery.value(1).toString();
			tmp.UserName = sqlQuery.value(2).toString();
			tmp.Time = sqlQuery.value(3).toString();
			tmp.Payout = sqlQuery.value(4).toString();
			tmp.Income = sqlQuery.value(5).toString();
			tmp.Balance = sqlQuery.value(6).toString();
			tmp.Remark = sqlQuery.value(7).toString();
			m_plist->append(tmp);
		}
	}
	return true;
}
bool DBManager::insertinspectRecord(etcRecord * pRecord)
{
	QSqlQuery sqlQuery(m_db);
	QString sqlCmd = QString(
		"INSERT INTO inspectionrecord(detectiontime, platenumber,username, direction, result, money, stationid, remark) \
			VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');")
		.arg(pRecord->DetectionTime)
		.arg(pRecord->PlateNumber)
		.arg(pRecord->UserName)
		.arg(pRecord->Direction)
		.arg(pRecord->Result)
		.arg(pRecord->Money)
		.arg(pRecord->StationId)
		.arg(pRecord->Remark);

	sqlQuery.prepare(sqlCmd);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}

	int iMaxID = 0;
	QString sqlSelectMaxID = "SELECT max(id) FROM inspectionrecord";
	sqlQuery.prepare(sqlSelectMaxID);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	else
	{
		while (sqlQuery.next())
		{
			iMaxID = sqlQuery.value(0).toInt();
			qDebug() << QString("max id:%1").arg(iMaxID);
			pRecord->id = iMaxID;
		}
	}

	return true;
}
bool DBManager::insertChargeRecord(chargeRecord * pRecord)
{
	QSqlQuery sqlQuery(m_db);
	QString sqlCmd = QString(
		"INSERT INTO chargerecord(platenumber, username, time, payout, income, balance, remark) \
			VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7');")
		.arg(pRecord->PlateNumber)
		.arg(pRecord->UserName)
		.arg(pRecord->Time)
		.arg(pRecord->Payout)
		.arg(pRecord->Income)
		.arg(pRecord->Balance)
		.arg(pRecord->Remark);

	sqlQuery.prepare(sqlCmd);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}

	int iMaxID = 0;
	QString sqlSelectMaxID = "SELECT max(id) FROM chargerecord";
	sqlQuery.prepare(sqlSelectMaxID);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	else
	{
		while (sqlQuery.next())
		{
			iMaxID = sqlQuery.value(0).toInt();
			qDebug() << QString("max id:%1").arg(iMaxID);
			pRecord->id = iMaxID;
		}
	}

	return true;
}
bool DBManager::modifyinspectRecord(const etcRecord & record)
{
	//查询所有记录  
	QSqlQuery sqlQuery(m_db);
	QString sqlCheckIDExist = QString("SELECT * FROM inspectionrecord WHERE id = '%1';").arg(record.id);
	sqlQuery.prepare(sqlCheckIDExist);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	else
	{
		if (sqlQuery.next())
		{
			int id = sqlQuery.value(0).toInt();
			QString name = sqlQuery.value(1).toString();
			QString type = sqlQuery.value(2).toString();
			qDebug() << QString("id:%1  detectiontime:%2  platenumber:%3").arg(id).arg(name).arg(type);
		}
		else
		{
			return false;
		}
	}

	QString sqlUpdateRecord = QString(
		"UPDATE inspectionrecord SET detectiontime = '%1', platenumber = '%2', username='%3'\
			direction = '%4', result = '%5', money = '%6', stationid = '%7',remark='%8' WHERE id = '%9' ;")
		.arg(record.DetectionTime)
		.arg(record.PlateNumber)
		.arg(record.UserName)
		.arg(record.Direction)
		.arg(record.Result)
		.arg(record.Money)
		.arg(record.StationId)
		.arg(record.Remark)
		.arg(record.id);
	sqlQuery.prepare(sqlUpdateRecord);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	return true;
}
bool DBManager::modifyChargeRecord(const chargeRecord & record)
{
	QSqlQuery sqlQuery(m_db);
	QString sqlCheckIDExist = QString("SELECT * FROM chargerecord WHERE id = '%1';").arg(record.id);
	sqlQuery.prepare(sqlCheckIDExist);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	else
	{
		if (sqlQuery.next())
		{
			int id = sqlQuery.value(0).toInt();
			QString name = sqlQuery.value(2).toString();
			QString type = sqlQuery.value(1).toString();
			qDebug() << QString("id:%1  time:%2  platenumber:%3").arg(id).arg(name).arg(type);
		}
		else
		{
			return false;
		}
	}

	QString sqlUpdateRecord = QString(
		"UPDATE chargerecord SET platenumber = '%1', username = '%2', time = '%3', payout = '%4', income = '%5', balance = '%6',remark='%7' WHERE id = '%8' ;")
		.arg(record.PlateNumber)
		.arg(record.UserName)
		.arg(record.Time)
		.arg(record.Payout)
		.arg(record.Income)
		.arg(record.Balance)
		.arg(record.Remark)
		.arg(record.id);
	sqlQuery.prepare(sqlUpdateRecord);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	return true;
}
bool DBManager::deleteinspectRecord(int id)
{
	QSqlQuery sqlQuery(m_db);
	QString sqlCmd = QString("DELETE FROM inspectionrecord WHERE id = '%1';").arg(id);
	sqlQuery.prepare(sqlCmd);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	return true;
}
bool DBManager::deleteChargeRecord(int id)
{
	QSqlQuery sqlQuery(m_db);
	QString sqlCmd = QString("DELETE FROM chargerecord WHERE id = '%1';").arg(id);
	sqlQuery.prepare(sqlCmd);
	if (!sqlQuery.exec())
	{
		qDebug() << sqlQuery.lastError();
		return false;
	}
	return true;
}
bool DBManager::openDataBase(const QString & strFileName)
{
	if (!QFile::exists(strFileName))//文件不存在，则创建  
	{
		QDir fileDir = QFileInfo(strFileName).absoluteDir();
		QString strFileDir = QFileInfo(strFileName).absolutePath();
		if (!fileDir.exists()) //路径不存在，创建路径  
		{
			fileDir.mkpath(strFileDir);
		}
		QFile dbFile(strFileName);
		if (!dbFile.open(QIODevice::WriteOnly))//未成功打开  
		{
			dbFile.close();
			return false;
		}
		dbFile.close();
	}

	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(strFileName);
	if (m_db.open())
	{
		return true;
	}

	return false;
}
bool DBManager::isexittable(const QString & strtablename)
{
	QSqlQuery query;
	QString strSql = QString("SELECT 1 FROM sqlite_master where type = 'table' and  name = '%1'").arg(strtablename);
	query.exec(strSql);
	if (query.next())
	{
		int nResult = query.value(0).toInt();//有表时返回1，无表时返回null  
		if (nResult)
		{
			return true;
		}
	}
	return false;
}
void DBManager::closedatabase()
{
	if (!m_db.open())
	{
		m_db.close();
	}
}
void DBManager::run()
{
	QString threadText = QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	QString logStr = QString("run function, thread id = %1").arg(threadText);
	qDebug() << "DBManager:" << logStr;

	while (!m_isQuit)
	{
		static bool isFistConnect = true;
		static bool isConnected = true;
		if (!m_db.isOpen())
		{
			if (!m_db.open())
			{
				if (isConnected != false)
				{
					//emitError();
					;
				}

				isConnected = false;
			}
			else
			{
				qDebug() << "Connect to database";
				if (isConnected != true || isFistConnect)
				{
					//emit signalError("Connect to database successsful");
					;
				}
				isConnected = true;
				isFistConnect = false;
			}
		}

		msleep(500);
	}

	closedatabase();
}
DBManager*DBManager::getInstance(void)
{
	if (m_pInstance == NULL)
	{
		s_MutexConstr.lock();
		if (m_pInstance == NULL)
		{
			m_pInstance = new DBManager();
		}
		s_MutexConstr.unlock();
	}

	return m_pInstance;
}
