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
	QList<QCameraInfo> cameras = QCameraInfo::availableCameras();//���ҿ������
	if (cameras.count() > 0)
	{
		foreach(const QCameraInfo&cameraInfo, cameras)
		{
			;
		}
		camera = new QCamera(cameras.at(0));//������
	}
	viewfinder = new QCameraViewfinder(this);//�����ʾ
	camera->setViewfinder(viewfinder);
	viewfinder->resize(400, 300);
	imageCapture = new QCameraImageCapture(camera);//��ͼ
	camera->start();

}

etcCamera::~etcCamera()
{

}


void etcCamera::onBtnSnapshot()//����
{
	//qDebug() << "xsaxsaxsaxsa123564";
	bool ok;
	QDir fileDir(QDir::currentPath());
	if (!fileDir.exists("EtcInfo")) //ȷ���ļ��д���
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