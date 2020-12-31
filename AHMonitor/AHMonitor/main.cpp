#include "AHMonitor.h"
#include "QLogonDialog.h"
#include <QtWidgets/QApplication>
#include <QtWebEngine>

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

	static QMutex mutex;

	mutex.lock();

	QString text;

	switch (type)
	{

	case QtDebugMsg:

		text = QString("Debug:");

		break;

	case QtWarningMsg:

		text = QString("Warning:");

		break;

	case QtCriticalMsg:

		text = QString("Critical:");

		break;

	case QtFatalMsg:

		text = QString("Fatal:");
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);

	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");

	QString current_date = QString("(%1)").arg(current_date_time);

	QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

	QFile file("AHlog.txt");

	file.open(QIODevice::WriteOnly | QIODevice::Append);

	QTextStream text_stream(&file);

	text_stream << message << "\r\n";

	file.flush();

	file.close();

	mutex.unlock();

}

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
	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
	QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
	QNetworkProxyFactory::setUseSystemConfiguration(false);
	QApplication a(argc, argv);

	//×¢²áMessageHandler

	qInstallMessageHandler(outputMessage);
	QFile qss("Resources/qss/stylesheet.qss");

	if (qss.open(QFile::ReadOnly))
	{
		qDebug("open success");
		QString style = QLatin1String(qss.readAll());
		a.setStyleSheet(style);
		qss.close();
	}
	else
	{
		qDebug("Open failed");
	}
	QtWebEngine::initialize();
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
