#include "ini_file.h"
#include <QtCore/QtCore>
#include <QFile>
#include <QDebug>

INI_File::INI_File()
{
	//m_qstrFileName = QCoreApplication::applicationDirPath() + "/Config.ini";

	//qDebug() << "m_qstrFileName: " << m_qstrFileName;

	////"Config.ini"配置文件，文件存在则打开，不存在则创建
	//m_psetting = new QSettings(m_qstrFileName, QSettings::IniFormat);
}

INI_File::~INI_File()
{
	delete m_psetting;
	m_psetting = NULL;
}

void INI_File::OpenFile(QString qstrFilePath, QString qstrFileName)
{
	m_qstrFileName = QCoreApplication::applicationDirPath() + "/" + qstrFileName;

	qDebug() << "m_qstrFileName: " << m_qstrFileName;

	//"Config.ini"配置文件，文件存在则打开，不存在则创建
	m_psetting = new QSettings(m_qstrFileName, QSettings::IniFormat);
}

void INI_File::SetIp(QString qstrIp)
{
	m_psetting->setValue("/NetParameters/ip", qstrIp);
}

void INI_File::SetPort(QString qstrPort)
{
	m_psetting->setValue("/NetParameters/port", qstrPort);
}

QString INI_File::GetPort()
{
	return m_psetting->value("/NetParameters/port").toString();
}

void INI_File::SetUserName(QString qstrUserName)
{
	m_psetting->setValue("/NetParameters/user", qstrUserName);
}

QString INI_File::GetUsername()
{
	return m_psetting->value("/NetParameters/user").toString();
}

void INI_File::SetPassword(QString qstrPassword)
{
	m_psetting->setValue("/NetParameters/password", qstrPassword);
}

QString INI_File::GetPassword()
{
	return m_psetting->value("/NetParameters/password").toString();
}

QString INI_File::GetDefaultSavePath()
{
	return QCoreApplication::applicationDirPath() + "/SavePath/";
}

QString INI_File::readString(QString qItem, QString qString)
{
	QString strkey = "/" + qItem + "/" + qString;
	return m_psetting->value(strkey).toString();
}

QString INI_File::GetIp()
{
	return m_psetting->value("/NetParameters/ip").toString();
}
