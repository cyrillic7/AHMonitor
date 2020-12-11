#include "AHMonitor.h"
#include "QLogonDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	/*QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(4, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);*/
	//QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
	qRegisterMetaType<QVector<int>>("QVector<int>");
	QApplication a(argc, argv);

	//QSurfaceFormat format;
	//format.setDepthBufferSize(24);
	//format.setStencilBufferSize(8);
	//format.setVersion(3, 2);
	//format.setProfile(QSurfaceFormat::CoreProfile);
	//QSurfaceFormat::setDefaultFormat(format);

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
