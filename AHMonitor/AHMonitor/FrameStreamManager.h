#ifndef FRAMESTREAMMANAGER_H
#define FRAMESTREAMMANAGER_H

#include "HeadFile.h"
#include <QLinkedList>
#include <QBuffer>
#include <QByteArray>
#include <QMutexLocker>
#include <QMutex>
#include <QQueue>

class FrameStreamManager
{
public:
	FrameStreamManager();
	~FrameStreamManager();

	static FrameStreamManager *getInstance() {
		return m_Instance;
	}

	static FrameStreamManager *m_Instance;

private:
	QLinkedList<QBuffer*> list;
	QMutex mutex;

	QQueue<MP_DATA_INFO*> m_queueMsg;

public:
	int putFrame(char *in, int length);
	int getFrame(char *rebuf, int size);
	int getFrameSize(void);

	void PushMsg(MP_DATA_INFO* pMsgInfo);

	bool PopMeg(MP_DATA_INFO** pMsgInfo);

	MP_DATA_INFO* popInfo();
};


#endif