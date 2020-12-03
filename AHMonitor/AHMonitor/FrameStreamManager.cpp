#include "FrameStreamManager.h"

FrameStreamManager* FrameStreamManager::m_Instance = NULL;

FrameStreamManager::FrameStreamManager()
{
	m_Instance = this;
}

FrameStreamManager::~FrameStreamManager()
{

}

int FrameStreamManager::putFrame(char *in, int length)
{
	int ret;
	QMutexLocker locker(&mutex);

	QBuffer *qbuf = new QBuffer();
	qbuf->open(QBuffer::ReadWrite);
	ret = qbuf->write(in, length);
	qbuf->close();

	list.append(qbuf);

	return ret;
}

int FrameStreamManager::getFrame(char *retbuf, int size)
{
	QMutexLocker locker(&mutex);
	QBuffer *qbuf;
	int ret = 0;

	if (list.size() > 0)
	{
		qbuf = list.takeFirst();
		qbuf->open(QBuffer::ReadWrite);
		ret = qbuf->read(retbuf, size);
		qbuf->close();
		delete qbuf;
	}

	return ret;
}

int FrameStreamManager::getFrameSize()
{
	return list.size();
}

void FrameStreamManager::PushMsg(MP_DATA_INFO * pMsgInfo)
{
	//QMutexLocker locker(&mutex);
	mutex.lock();
	m_queueMsg.push_back(pMsgInfo);
	mutex.unlock();
}

bool FrameStreamManager::PopMeg(MP_DATA_INFO ** pMsgInfo)
{
	bool bRet = false;
	//QMutexLocker locker(&mutex);
	mutex.lock();
	if (m_queueMsg.isEmpty())
	{
		mutex.unlock();
		return bRet;
	}

	bRet = true;
	*pMsgInfo = m_queueMsg.front();
	m_queueMsg.pop_front();
	mutex.unlock();
	return bRet;
}

MP_DATA_INFO * FrameStreamManager::popInfo()
{
	MP_DATA_INFO * pMsgInfo = new MP_DATA_INFO;
	memset(pMsgInfo, 0, sizeof(pMsgInfo));
	bool bRet = false;
	mutex.lock();
	if (m_queueMsg.isEmpty())
	{
		mutex.unlock();
		return NULL;
	}

	bRet = true;
	pMsgInfo = m_queueMsg.front();
	m_queueMsg.pop_front();
	mutex.unlock();
	return pMsgInfo;
}

