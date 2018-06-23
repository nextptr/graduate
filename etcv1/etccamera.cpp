#include "etccamera.h"
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QFileDialog>
#include <QList>
#include <QDir>
#include <QLabel>
#include <QInputDialog>


etcCamera::etcCamera(QWidget *parent)
	: QWidget(parent)
{
	QList<QCameraInfo> cameras = QCameraInfo::availableCameras();//查找可用相机
	if (cameras.count() > 0)
	{
		foreach(const QCameraInfo&cameraInfo, cameras)
		{
			;
		}
		camera = new QCamera(cameras.at(0));//获得相机
	}
	viewfinder = new QCameraViewfinder(this);//相机显示
	camera->setViewfinder(viewfinder);
	viewfinder->resize(400, 300);
	imageCapture = new QCameraImageCapture(camera);//截图
	camera->start();

}

etcCamera::~etcCamera()
{

}

void etcCamera::onCameraSave(etcCar*m_pcar)//拍照
{
	QString TimStr = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
	QStringList TimStrList = TimStr.split("-");
	QString fileSaveName = QDir::currentPath() + "/EtcInfo/" + TimStrList[0] + "/" + TimStrList[1] + "/" + TimStrList[2] + "/"+ m_pcar->saveImg;//保存路径

	camera->setCaptureMode(QCamera::CaptureStillImage);
	camera->searchAndLock();
	imageCapture->capture(fileSaveName);
	camera->unlock();
}