#include "etcrecord.h"

etcRecord::etcRecord(QObject *parent)
	: QObject(parent)
{

}

etcRecord::~etcRecord()
{

}

chargeRecord::chargeRecord(QObject *parent)
	: QObject(parent)
{

}

chargeRecord::~chargeRecord()
{

}

//���ݳ��ƺŴ�list���Ҽ�¼������bool
chargeRecord* getChargeRecord(QList<chargeRecord> *pList, int id)
{
	QList<chargeRecord>::iterator it;
	for (it = pList->begin(); it != pList->end(); ++it)
	{
		if (id == (*it).id)
		{
			return &(*it);
		}
	}
	return NULL;
}

//����id�Ŵ�list���Ҽ�¼������ָ��
etcRecord * getInspectRecord(QList<etcRecord> *pList, int id)
{
	QList<etcRecord>::iterator it;
	for (it = pList->begin(); it != pList->end(); ++it)
	{
		if (id == (*it).id)
		{
			return &(*it);
		}
	}
	return NULL;
}

//���ݴ����record�޸�list;
void modifyList(QList<etcRecord>* pList, etcRecord &record)
{
	QList<etcRecord>::iterator it;
	for (it = pList->begin(); it != pList->end(); ++it)
	{
		if (record.id == (*it).id)
		{
			record = (*it);
			return;
		}
	}
}

void modifyList(QList<chargeRecord>* pList, chargeRecord &record)
{
	QList<chargeRecord>::iterator it;
	for (it = pList->begin(); it != pList->end(); ++it)
	{
		if (record.id == (*it).id)
		{
			record = (*it);
			return;
		}
	}
}

//�����±�ɾ����¼
void eraseArecord(QList<etcRecord>* pList, int index)
{
	if (index >= 0 && index < pList->size())
	{
		pList->takeAt(index);
	}
}

void eraseArecord(QList<chargeRecord>* pList, int index)
{
	if (index >= 0 && index < pList->size())
	{
		pList->takeAt(index);
	}
}