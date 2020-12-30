#ifndef INI_FILE_H
#define INI_FILE_H

#include <QString>
#include <QSettings>

class INI_File
{
public:
	INI_File();
	virtual ~INI_File();

	void OpenFile(QString qstrFilePath, QString qstrFileName);

	void SetIp(QString qstrIp);
	QString GetIp();

	void SetPort(QString qstrPort);
	QString GetPort();

	void SetUserName(QString qstrUserName);
	QString GetUsername();

	void SetPassword(QString qstrPassword);
	QString GetPassword();

	QString GetDefaultSavePath();

	QString readString(QString qItem, QString qString);
private:
	QString m_qstrFileName;
	QSettings *m_psetting;
};

#endif // INI_FILE_H
