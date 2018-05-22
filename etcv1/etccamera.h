#ifndef ETCCAMERA_H
#define ETCCAMERA_H

#include"etccar.h"

#include <QWidget>
#include <QDate>

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

class etcCamera : public QWidget
{
	Q_OBJECT

public:
	etcCamera(QWidget *parent = 0);
	~etcCamera();
public Q_SLOTS:
    void onCameraSave(etcCar*m_pcar);
private:
	QCamera*camera;
	QCameraViewfinder*viewfinder;
	QCameraImageCapture*imageCapture;
};

#endif // ETCCAMERA_H
