//#include "XVideoWidget.h"
//#include <QDebug>
//#include <QTimer>
//#include <QDateTime>
extern "C" {
#include <libavutil/frame.h>
}
////自动加双引号
//#define GET_STR(x) #x
//#define A_VER 3
//#define T_VER 4
//
//FILE *fp = NULL;
//
////顶点shader
//const char *vString = GET_STR(
//	attribute vec4 vertexIn;
//attribute vec2 textureIn;
//varying vec2 textureOut;
//void main(void)
//{
//	gl_Position = vertexIn;
//	textureOut = textureIn;
//}
//);
//
//
////片元shader
//const char *tString = GET_STR(
//	varying vec2 textureOut;
//uniform sampler2D tex_y;
//uniform sampler2D tex_u;
//uniform sampler2D tex_v;
//void main(void)
//{
//	vec3 yuv;
//	vec3 rgb;
//	yuv.x = texture2D(tex_y, textureOut).r;
//	yuv.y = texture2D(tex_u, textureOut).r - 0.5;
//	yuv.z = texture2D(tex_v, textureOut).r - 0.5;
//	rgb = mat3(1.0, 1.0, 1.0,
//		0.0, -0.39465, 2.03211,
//		1.13983, -0.58060, 0.0) * yuv;
//	gl_FragColor = vec4(rgb, 1.0);
//}
//
//);
//
//
//
////准备yuv数据
//// ffmpeg -i v1080.mp4 -t 10 -s 240x128 -pix_fmt yuv420p  out240x128.yuv
//XVideoWidget::XVideoWidget(QWidget *parent)
//	: QOpenGLWidget(parent)
//{
//	//QSurfaceFormat format;
//	//format.setDepthBufferSize(24);
//	//format.setStencilBufferSize(8);
//	//format.setVersion(3, 2);
//	////format.setProfile(QSurfaceFormat::CoreProfile);
//	//setFormat(format); // must be called before the widget or its parent window gets shown
//}
//
//XVideoWidget::~XVideoWidget()
//{
//}
//
//void XVideoWidget::Repaint(AVFrame *frame)
//{
//
//	if (!frame)return;
//	mux.lock();
//	//qDebug() << "frame->width:" << frame->width << "frame->height:" << frame->height;
//	//容错，保证尺寸正确
//	if (!datas[0] || width*height == 0/* || frame->width != this->width || frame->height != this->height*/)
//	{
//		av_frame_free(&frame);
//		mux.unlock();
//		return;
//	}
//	if (width == frame->linesize[0]) //无需对齐
//	{
//		memcpy(datas[0], frame->data[0], width*height);
//		memcpy(datas[1], frame->data[1], width*height / 4);
//		memcpy(datas[2], frame->data[2], width*height / 4);
//	}
//	else//行对齐问题
//	{
//		for(int i = 0; i < height; i++) //Y 
//			memcpy(datas[0] + width*i, frame->data[0] + frame->linesize[0]*i, width);
//		for (int i = 0; i < height/2; i++) //U
//			memcpy(datas[1] + width/2*i, frame->data[1] + frame->linesize[1] * i, width/2);
//		for (int i = 0; i < height/2; i++) //V
//			memcpy(datas[2] + width/2*i, frame->data[2] + frame->linesize[2] * i, width/2);
//
//	}
//	
//	mux.unlock();
//	av_frame_free(&frame);
//	//qDebug() << "刷新显示" << endl;
//	//刷新显示
//	update();
//}
//void XVideoWidget::saveShot(const QString &savePath)
//{
//	QPixmap pixmap(this->size());
//	render(&pixmap);
//
//	QDateTime current_date_time = QDateTime::currentDateTime();
//	QString current_date = current_date_time.toString("yyyyMMddhhmmsszzz");
//	QString fileName = savePath + "/" +  current_date + ".jpg";
//	pixmap.save(fileName);
//}
//void XVideoWidget::Init(int width, int height)
//{
//	if (isInit_ == true)
//	{
//		return;
//	}
//	isInit_ = true;
//	mux.lock();
//	this->width = width;
//	this->height = height;
//	delete datas[0];
//	delete datas[1];
//	delete datas[2];
//	///分配材质内存空间
//	datas[0] = new unsigned char[width*height];		//Y
//	datas[1] = new unsigned char[width*height / 4];	//U
//	datas[2] = new unsigned char[width*height / 4];	//V
//
//
//	if (texs[0])
//	{
//		glDeleteTextures(3, texs);
//	}
//	//创建材质
//	glGenTextures(3, texs);
//
//	//Y
//	glBindTexture(GL_TEXTURE_2D, texs[0]);
//	//放大过滤，线性插值   GL_NEAREST(效率高，但马赛克严重)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//创建材质显卡空间
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
//
//	//U
//	glBindTexture(GL_TEXTURE_2D, texs[1]);
//	//放大过滤，线性插值
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//创建材质显卡空间
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width / 2, height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
//
//	//V
//	glBindTexture(GL_TEXTURE_2D, texs[2]);
//	//放大过滤，线性插值
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//创建材质显卡空间
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width / 2, height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
//
//
//	mux.unlock();
//
//
//}
////初始化opengl
//void XVideoWidget::initializeGL()
//{
//	//qDebug() << glGetString(GL_VERSION) << endl;
//	qDebug() << "initializeGL";
//	mux.lock();
//	//初始化opengl （QOpenGLFunctions继承）函数 
//	initializeOpenGLFunctions();
//
//	//program加载shader（顶点和片元）脚本
//	//片元（像素）
//	qDebug() << program.addShaderFromSourceCode(QGLShader::Fragment, tString);
//	//顶点shader
//	qDebug() << program.addShaderFromSourceCode(QGLShader::Vertex, vString);
//
//	//设置顶点坐标的变量
//	program.bindAttributeLocation("vertexIn", A_VER);
//
//	//设置材质坐标
//	program.bindAttributeLocation("textureIn", T_VER);
//
//	//编译shader
//	qDebug() << "program.link() = " << program.link();
//
//	qDebug() << "program.bind() = " << program.bind();
//
//	//传递顶点和材质坐标
//	//顶点
//	static const GLfloat ver[] = {
//		-1.0f,-1.0f,
//		1.0f,-1.0f,
//		-1.0f, 1.0f,
//		1.0f,1.0f
//	};
//
//	//材质
//	static const GLfloat tex[] = {
//		0.0f, 1.0f,
//		1.0f, 1.0f,
//		0.0f, 0.0f,
//		1.0f, 0.0f
//	};
//
//	//顶点
//	glVertexAttribPointer(A_VER, 2, GL_FLOAT, 0, 0, ver);
//	glEnableVertexAttribArray(A_VER);
//
//	//材质
//	glVertexAttribPointer(T_VER, 2, GL_FLOAT, 0, 0, tex);
//	glEnableVertexAttribArray(T_VER);
//
//
//	//从shader获取材质
//	unis[0] = program.uniformLocation("tex_y");
//	unis[1] = program.uniformLocation("tex_u");
//	unis[2] = program.uniformLocation("tex_v");
//	qDebug() << glGetString(GL_VERSION) << endl;
//	mux.unlock();
//	//fp = fopen("out240x128.yuv", "rb");
//	//if (!fp)
//	//{
//	//	qDebug() << "out240x128.yuv file open failed!";
//	//}
//
//
//	////启动定时器
//	//QTimer *ti = new QTimer(this);
//	//connect(ti, SIGNAL(timeout()), this, SLOT(update()));
//	//ti->start(40);
//}
//
////刷新显示
//void XVideoWidget::paintGL()
//{
//	if (!datas[0])
//	{
//		return;
//	}
//	//if (feof(fp))
//	//{
//	//	fseek(fp, 0, SEEK_SET);
//	//}
//	//fread(datas[0], 1, width*height, fp);
//	//fread(datas[1], 1, width*height / 4, fp);
//	//fread(datas[2], 1, width*height / 4, fp);
//	mux.lock();
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texs[0]); //0层绑定到Y材质
//										   //修改材质内容(复制内存内容)
//	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, datas[0]);
//	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
//	//与shader uni遍历关联
//	glUniform1i(unis[0], 0);
//
//
//	glActiveTexture(GL_TEXTURE0 + 1);
//	glBindTexture(GL_TEXTURE_2D, texs[1]); //1层绑定到U材质
//										   //修改材质内容(复制内存内容)
//	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width / 2, height / 2, GL_RED, GL_UNSIGNED_BYTE, datas[1]);
//	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
//	//与shader uni遍历关联
//	glUniform1i(unis[1], 1);
//
//
//	glActiveTexture(GL_TEXTURE0 + 2);
//	glBindTexture(GL_TEXTURE_2D, texs[2]); //2层绑定到V材质
//										   //修改材质内容(复制内存内容)
//	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width / 2, height / 2, GL_RED, GL_UNSIGNED_BYTE, datas[2]);
//	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
//	//与shader uni遍历关联
//	glUniform1i(unis[2], 2);
//
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	//qDebug() << "paintGL";
//	mux.unlock();
//}
//
//
//// 窗口尺寸变化
//void XVideoWidget::resizeGL(int width, int height)
//{
//	mux.lock();
//	qDebug() << "resizeGL " << width << ":" << height;
//	mux.unlock();
//}
#include "XVideoWidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QDebug>
#define VERTEXIN 0
#define TEXTUREIN 1

GLYuvWidget::GLYuvWidget(QWidget *parent) :
	QOpenGLWidget(parent)
{
}

GLYuvWidget::~GLYuvWidget()
{
	makeCurrent();
	vbo.destroy();
	textureY->destroy();
	textureU->destroy();
	textureV->destroy();
	doneCurrent();
}

void GLYuvWidget::Init(int width, int height)
{
	yuvPtr = new unsigned char[width*height * 3];
}

void GLYuvWidget::Repaint(AVFrame * frame)
{
	if (!frame)return;
	//	mux.lock();
		//qDebug() << "frame->width:" << frame->width << "frame->height:" << frame->height;
		//容错，保证尺寸正确
// 		if (!datas[0] || width*height == 0/* || frame->width != this->width || frame->height != this->height*/)
// 		{
// 			av_frame_free(&frame);
// 			mux.unlock();
// 			return;
// 		}
// 		if (width == frame->linesize[0]) //无需对齐
// 		{
// 			memcpy(datas[0], frame->data[0], width*height);
// 			memcpy(datas[1], frame->data[1], width*height / 4);
// 			memcpy(datas[2], frame->data[2], width*height / 4);
// 		}
//		else//行对齐问题
	//unsigned char *datas[3] = { 0 };
	int videowidth = frame->width;
	int videoheight = frame->height;
	//datas[0] = new unsigned char[videowidth*videoheight];		//Y
	//datas[1] = new unsigned char[videowidth*videoheight / 4];	//U
	//datas[2] = new unsigned char[videowidth*videoheight / 4];	//V
	//
	//unsigned char *datas = new unsigned char[videowidth*videoheight * 3];
		{
		int i, j, k;
			for(i = 0; i < videoheight; i++) //Y 
				memcpy(yuvPtr + videowidth*i , frame->data[0] + frame->linesize[0]*i, videowidth);
			for (j = 0; j < videoheight /2; j++) //U
				memcpy(yuvPtr + videowidth*i+ videowidth / 2 * j, frame->data[1] + frame->linesize[1] * j, videowidth /2);
			for (k = 0; k < videoheight /2; k++) //V
				memcpy(yuvPtr + videowidth*i+ videowidth / 2 * j + videowidth / 2 * k, frame->data[2] + frame->linesize[2] * k, videowidth /2);
	
		}

		//slotShowYuv(datas, videowidth, videoheight);
		//yuvPtr = ptr;
		videoW = videowidth;
		videoH = videoheight;
		//mux.unlock();
		av_frame_free(&frame);

		update();
}

void GLYuvWidget::slotShowYuv(uchar *ptr, uint width, uint height)
{
	yuvPtr = ptr;
	videoW = width;
	videoH = height;
	update();
}

void GLYuvWidget::initializeGL()
{
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);

	static const GLfloat vertices[]{
		//顶点坐标
		-1.0f,-1.0f,
		-1.0f,+1.0f,
		+1.0f,+1.0f,
		+1.0f,-1.0f,
		//纹理坐标
		0.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
	};


	vbo.create();
	vbo.bind();
	vbo.allocate(vertices, sizeof(vertices));

	QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char *vsrc =
		"attribute vec4 vertexIn; \
    attribute vec2 textureIn; \
    varying vec2 textureOut;  \
    void main(void)           \
    {                         \
        gl_Position = vertexIn; \
        textureOut = textureIn; \
    }";
	vshader->compileSourceCode(vsrc);

	QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char *fsrc = "varying vec2 textureOut; \
    uniform sampler2D tex_y; \
    uniform sampler2D tex_u; \
    uniform sampler2D tex_v; \
    void main(void) \
    { \
        vec3 yuv; \
        vec3 rgb; \
        yuv.x = texture2D(tex_y, textureOut).r; \
        yuv.y = texture2D(tex_u, textureOut).r - 0.5; \
        yuv.z = texture2D(tex_v, textureOut).r - 0.5; \
        rgb = mat3( 1,       1,         1, \
                    0,       -0.39465,  2.03211, \
                    1.13983, -0.58060,  0) * yuv; \
        gl_FragColor = vec4(rgb, 1); \
    }";
	fshader->compileSourceCode(fsrc);

	program = new QOpenGLShaderProgram(this);
	program->addShader(vshader);
	program->addShader(fshader);
	program->bindAttributeLocation("vertexIn", VERTEXIN);
	program->bindAttributeLocation("textureIn", TEXTUREIN);
	program->link();
	program->bind();
	program->enableAttributeArray(VERTEXIN);
	program->enableAttributeArray(TEXTUREIN);
	program->setAttributeBuffer(VERTEXIN, GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));
	program->setAttributeBuffer(TEXTUREIN, GL_FLOAT, 8 * sizeof(GLfloat), 2, 2 * sizeof(GLfloat));

	textureUniformY = program->uniformLocation("tex_y");
	textureUniformU = program->uniformLocation("tex_u");
	textureUniformV = program->uniformLocation("tex_v");
	textureY = new QOpenGLTexture(QOpenGLTexture::Target2D);
	textureU = new QOpenGLTexture(QOpenGLTexture::Target2D);
	textureV = new QOpenGLTexture(QOpenGLTexture::Target2D);
	textureY->create();
	textureU->create();
	textureV->create();
	idY = textureY->textureId();
	idU = textureU->textureId();
	idV = textureV->textureId();
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void GLYuvWidget::paintGL()
{
	//    QMatrix4x4 m;
	//    m.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f );//透视矩阵随距离的变化，图形跟着变化。屏幕平面中心就是视点（摄像头）,需要将图形移向屏幕里面一定距离。
	//    m.ortho(-2,+2,-2,+2,-10,10);//近裁剪平面是一个矩形,矩形左下角点三维空间坐标是（left,bottom,-near）,右上角点是（right,top,-near）所以此处为负，表示z轴最大为10；
	//远裁剪平面也是一个矩形,左下角点空间坐标是（left,bottom,-far）,右上角点是（right,top,-far）所以此处为正，表示z轴最小为-10；
	//此时坐标中心还是在屏幕水平面中间，只是前后左右的距离已限制。
	glActiveTexture(GL_TEXTURE0);  //激活纹理单元GL_TEXTURE0,系统里面的
	glBindTexture(GL_TEXTURE_2D, idY); //绑定y分量纹理对象id到激活的纹理单元
									   //使用内存中的数据创建真正的y分量纹理数据
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, videoW, videoH, 0, GL_RED, GL_UNSIGNED_BYTE, yuvPtr);
	//https://blog.csdn.net/xipiaoyouzi/article/details/53584798 纹理参数解析
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE1); //激活纹理单元GL_TEXTURE1
	glBindTexture(GL_TEXTURE_2D, idU);
	//使用内存中的数据创建真正的u分量纹理数据
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, videoW >> 1, videoH >> 1, 0, GL_RED, GL_UNSIGNED_BYTE, yuvPtr + videoW * videoH);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE2); //激活纹理单元GL_TEXTURE2
	glBindTexture(GL_TEXTURE_2D, idV);
	//使用内存中的数据创建真正的v分量纹理数据
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, videoW >> 1, videoH >> 1, 0, GL_RED, GL_UNSIGNED_BYTE, yuvPtr + videoW*videoH * 5 / 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//指定y纹理要使用新值
	glUniform1i(textureUniformY, 0);
	//指定u纹理要使用新值
	glUniform1i(textureUniformU, 1);
	//指定v纹理要使用新值
	glUniform1i(textureUniformV, 2);
	//使用顶点数组方式绘制图形
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}