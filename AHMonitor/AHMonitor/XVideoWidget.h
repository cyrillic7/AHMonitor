//#ifndef XVIDEOWIDGET
//#define XVIDEOWIDGET
//
//#include <QOpenGLWidget>
//#include <QOpenGLFunctions>
//#include <QGLShaderProgram>
//#include <mutex>
//#include "IVideoCall.h"
struct AVFrame;
//class XVideoWidget : public QOpenGLWidget, protected QOpenGLFunctions,public IVideoCall
//{
//	Q_OBJECT
//
//public:
//	virtual void Init(int width, int height);
//
//	//���ܳɹ�����ͷ�frame�ռ�
//	virtual void Repaint(AVFrame *frame);
//
//	void saveShot(const QString &savePath);
//
//	XVideoWidget(QWidget *parent);
//	~XVideoWidget();
//protected:
//	//ˢ����ʾ
//	void paintGL();
//
//	//��ʼ��gl
//	void initializeGL();
//
//	// ���ڳߴ�仯
//	void resizeGL(int width, int height);
//private:
//	std::mutex mux;
//
//	//shader����
//	QGLShaderProgram program;
//
//	//shader��yuv������ַ
//	GLuint unis[3] = { 0 };
//	//openg�� texture��ַ
//	GLuint texs[3] = { 0 };
//
//	//�����ڴ�ռ�
//	unsigned char *datas[3] = { 0 };
//
//	int width = 240;
//	int height = 128;
//	bool isInit_ = false;
//};
//
//#endif
#ifndef GLYUVWIDGET_H
#define GLYUVWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QTimer>
#include "IVideoCall.h"
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class GLYuvWidget : public QOpenGLWidget, protected QOpenGLFunctions, public IVideoCall
{
	Q_OBJECT
public:
	GLYuvWidget(QWidget *parent = 0);
	~GLYuvWidget();
	public:
		//unsigned char *datas;
		virtual void Init(int width, int height);
	
		//���ܳɹ�����ͷ�frame�ռ�
		virtual void Repaint(AVFrame *frame);
	public slots:
	void slotShowYuv(uchar *ptr, uint width, uint height); //��ʾһ֡Yuvͼ��

protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;

private:
	QOpenGLShaderProgram *program;
	QOpenGLBuffer vbo;
	GLuint textureUniformY, textureUniformU, textureUniformV; //opengl��y��u��v����λ��
	QOpenGLTexture *textureY = nullptr, *textureU = nullptr, *textureV = nullptr;
	GLuint idY, idU, idV; //�Լ��������������ID���������󷵻�0
	uint videoW, videoH;
	uchar *yuvPtr = nullptr;
};

#endif // GLYUVWIDGET_H