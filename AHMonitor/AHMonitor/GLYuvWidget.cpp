#include "GLYuvWidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QDebug>
extern "C" {
#include <libavutil/frame.h>
}
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
	mux.lock();
	yuvPtr = new unsigned char[width*height * 3];
	mux.unlock();
}

void GLYuvWidget::Repaint(AVFrame * frame)
{
	if (!frame)return;
	mux.lock();
	int videowidth = frame->width;
	int videoheight = frame->height;

	int i, j, k;
	for (i = 0; i < videoheight; i++) //Y 
		memcpy(yuvPtr + videowidth*i, frame->data[0] + frame->linesize[0] * i, videowidth);
	for (j = 0; j < videoheight / 2; j++) //U
		memcpy(yuvPtr + videowidth*i + videowidth / 2 * j, frame->data[1] + frame->linesize[1] * j, videowidth / 2);
	for (k = 0; k < videoheight / 2; k++) //V
		memcpy(yuvPtr + videowidth*i + videowidth / 2 * j + videowidth / 2 * k, frame->data[2] + frame->linesize[2] * k, videowidth / 2);


	videoW = videowidth;
	videoH = videoheight;


	mux.unlock();
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
	mux.lock();
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);

	static const GLfloat vertices[]{
		//��������
		-1.0f,-1.0f,
		-1.0f,+1.0f,
		+1.0f,+1.0f,
		+1.0f,-1.0f,
		//��������
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
	mux.unlock();
}

void GLYuvWidget::paintGL()
{
	mux.lock();
	//    QMatrix4x4 m;
	//    m.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f );//͸�Ӿ��������ı仯��ͼ�θ��ű仯����Ļƽ�����ľ����ӵ㣨����ͷ��,��Ҫ��ͼ��������Ļ����һ�����롣
	//    m.ortho(-2,+2,-2,+2,-10,10);//���ü�ƽ����һ������,�������½ǵ���ά�ռ������ǣ�left,bottom,-near��,���Ͻǵ��ǣ�right,top,-near�����Դ˴�Ϊ������ʾz�����Ϊ10��
	//Զ�ü�ƽ��Ҳ��һ������,���½ǵ�ռ������ǣ�left,bottom,-far��,���Ͻǵ��ǣ�right,top,-far�����Դ˴�Ϊ������ʾz����СΪ-10��
	//��ʱ�������Ļ�������Ļˮƽ���м䣬ֻ��ǰ�����ҵľ��������ơ�
	glActiveTexture(GL_TEXTURE0);  //��������ԪGL_TEXTURE0,ϵͳ�����
	glBindTexture(GL_TEXTURE_2D, idY); //��y�����������id�����������Ԫ
									   //ʹ���ڴ��е����ݴ���������y������������
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, videoW, videoH, 0, GL_RED, GL_UNSIGNED_BYTE, yuvPtr);
	//https://blog.csdn.net/xipiaoyouzi/article/details/53584798 �����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE1); //��������ԪGL_TEXTURE1
	glBindTexture(GL_TEXTURE_2D, idU);
	//ʹ���ڴ��е����ݴ���������u������������
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, videoW >> 1, videoH >> 1, 0, GL_RED, GL_UNSIGNED_BYTE, yuvPtr + videoW * videoH);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE2); //��������ԪGL_TEXTURE2
	glBindTexture(GL_TEXTURE_2D, idV);
	//ʹ���ڴ��е����ݴ���������v������������
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, videoW >> 1, videoH >> 1, 0, GL_RED, GL_UNSIGNED_BYTE, yuvPtr + videoW*videoH * 5 / 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//ָ��y����Ҫʹ����ֵ
	glUniform1i(textureUniformY, 0);
	//ָ��u����Ҫʹ����ֵ
	glUniform1i(textureUniformU, 1);
	//ָ��v����Ҫʹ����ֵ
	glUniform1i(textureUniformV, 2);
	//ʹ�ö������鷽ʽ����ͼ��
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	mux.unlock();
}