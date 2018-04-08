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


void etcCamera::onBtnSnapshot()//拍照
{
	//qDebug() << "xsaxsaxsaxsa123564";
	bool ok;
	QDir fileDir(QDir::currentPath());
	if (!fileDir.exists("EtcInfo")) //确保文件夹存在
	{
		fileDir.mkdir("EtcInfo");
	}
	QString filename = QInputDialog::getText(this, "filename", "please enter", QLineEdit::Normal, "user", &ok);
	QString fileSaveName = fileDir.currentPath() + "/EtcInfo/" + filename+".jpg";
	camera->setCaptureMode(QCamera::CaptureStillImage);
	camera->searchAndLock();
	imageCapture->capture(fileSaveName);
	qDebug() << " filename " << filename << endl;
	qDebug() << " fileSaveName " << fileSaveName << endl;
	qDebug() << " fileDir.currentPath " << fileDir.currentPath() << endl;

	camera->unlock();
}