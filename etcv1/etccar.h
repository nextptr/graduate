#ifndef ETCCAR_H
#define ETCCAR_H

#include <QGraphicsObject>
#include <QGraphicsSceneHoverEvent>

class etcCar : public QGraphicsObject
{
	Q_OBJECT
signals :
	void carFlag(int flag);
public:
	etcCar(QString pixmapDir, QString carname, QString username, int flag);
	QPainterPath shape();
	//void advance(int phase);
	QRectF boundingRect()const; //��ͼ����
	void paint(QPainter*painter, const QStyleOptionGraphicsItem*option, QWidget*widget);//��ͼ����
	void etcCar::hoverEnterEvent(QGraphicsSceneHoverEvent*);
	int clock;         //����clock�ı䳵ֵ��״̬
	int activeFlag;    //��ֹ��ײ,�����Ŷ�
	bool resetFlag;     //��������������־      
public:
	QString pixmapstr; //������ͼ
	QString CarNumber; //����
	QString userName; //�û���
	int carflag;    //��������	
	int money;      //������� 
protected:
	//void mousePressEvent(QGraphicsSceneMouseEvent*myevent);
	
};

#endif // ECAR_H
