#include "AHMonitor.h"
#include "QLogonDialog.h"
#include <QtWidgets/QApplication>
//#include <QtWebEngine>
int main(int argc, char *argv[])
{
//#ifdef USED3D
	//qputenv("QT_ANGLE_PLATFORM", "d3d9");
	//QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
//#endif
	/*QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(4, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);*/
	//QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
	//QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
	//QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
	qRegisterMetaType<QVector<int>>("QVector<int>");
	//QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
	QApplication a(argc, argv);
	//QSurfaceFormat format;
	//format.setDepthBufferSize(24);
	//format.setStencilBufferSize(8);
	//format.setVersion(3, 2);
	//format.setProfile(QSurfaceFormat::CoreProfile);
	//QSurfaceFormat::setDefaultFormat(format);
//	QtWebEngine::initialize();
	AHMonitor w;
	/*w.show();*/

	/*QLogonDialog logonDlg;*/
	if (w.pLogonDialog_->exec() == QDialog::Accepted)
	{
		if (w.serverConnection(w.pLogonDialog_->szAccounts, w.pLogonDialog_->szPassword, w.pLogonDialog_->szAddress, w.pLogonDialog_->szPort) == -1)
			return -1;

		w.showMaximized();
		w.updateTreeWidget();
		w.updateDisConWidget();
	}
	else
	{
		return -1;
	}

	return a.exec();
}
