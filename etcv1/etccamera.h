#ifndef ETCCAMERA_H
#define ETCCAMERA_H

#include <QWidget>

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
    void onBtnSnapshot(void);
private:
	QCamera*camera;
	QCameraViewfinder*viewfinder;
	QCameraImageCapture*imageCapture;
};

#endif // ETCCAMERA_H
