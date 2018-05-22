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

	QDir mDir(QDir::currentPath());
	if (!mDir.exists("EtcInfo")) //确保文件夹存在
	{
		mDir.mkdir("EtcInfo");
	}
	QDir mDirYear("./EtcInfo");
	if (!mDirYear.exists(TimStrList[0])) //年
	{
		mDirYear.mkdir(TimStrList[0]);
	}
	QDir mDirMon("./EtcInfo/" + TimStrList[0]);
	if (!mDirMon.exists(TimStrList[1])) //年
	{
		mDirMon.mkdir(TimStrList[1]);
	}
	QDir mDirDay("./EtcInfo/" + TimStrList[0] + "/" + TimStrList[1]);
	if (!mDirDay.exists(TimStrList[2])) //年
	{
		mDirDay.mkdir(TimStrList[2]);
	}

	QString ImgSaveName;//拍照文件名
	for (int i = 0;i < 6;i++)
	{
		ImgSaveName += TimStrList[i];
	}
	ImgSaveName += m_pcar->CarNumber + ".png";

	QString fileSaveName = mDir.currentPath() + "/EtcInfo/" + TimStrList[0] + "/" + TimStrList[1] + "/" + TimStrList[2] + "/"+ ImgSaveName;//保存路径

	camera->setCaptureMode(QCamera::CaptureStillImage);
	camera->searchAndLock();
	imageCapture->capture(fileSaveName);


	camera->unlock();
}