#ifndef GLYUVWIDGET_H
#define GLYUVWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QTimer>
#include <mutex>
#include "IVideoCall.h"
struct AVFrame;
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
	std::mutex mux;
	QOpenGLShaderProgram *program;
	QOpenGLBuffer vbo;
	GLuint textureUniformY, textureUniformU, textureUniformV; //opengl中y、u、v分量位置
	QOpenGLTexture *textureY = nullptr, *textureU = nullptr, *textureV = nullptr;
	GLuint idY, idU, idV; //自己创建的纹理对象ID，创建错误返回0
	uint videoW, videoH;
	uchar *yuvPtr = nullptr;
};

#endif // GLYUVWIDGET_H

