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
//	//不管成功与否都释放frame空间
//	virtual void Repaint(AVFrame *frame);
//
//	void saveShot(const QString &savePath);
//
//	XVideoWidget(QWidget *parent);
//	~XVideoWidget();
//protected:
//	//刷新显示
//	void paintGL();
//
//	//初始化gl
//	void initializeGL();
//
//	// 窗口尺寸变化
//	void resizeGL(int width, int height);
//private:
//	std::mutex mux;
//
//	//shader程序
//	QGLShaderProgram program;
//
//	//shader中yuv变量地址
//	GLuint unis[3] = { 0 };
//	//openg的 texture地址
//	GLuint texs[3] = { 0 };
//
//	//材质内存空间
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
	
		//不管成功与否都释放frame空间
		virtual void Repaint(AVFrame *frame);
	public slots:
	void slotShowYuv(uchar *ptr, uint width, uint height); //显示一帧Yuv图像

protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;

private:
	QOpenGLShaderProgram *program;
	QOpenGLBuffer vbo;
	GLuint textureUniformY, textureUniformU, textureUniformV; //opengl中y、u、v分量位置
	QOpenGLTexture *textureY = nullptr, *textureU = nullptr, *textureV = nullptr;
	GLuint idY, idU, idV; //自己创建的纹理对象ID，创建错误返回0
	uint videoW, videoH;
	uchar *yuvPtr = nullptr;
};

#endif // GLYUVWIDGET_H