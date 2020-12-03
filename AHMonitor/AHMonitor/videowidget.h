﻿#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

/**
 * 1. 可设置边框大小
 * 2. 可设置边框颜色
 * 3. 可设置两路OSD标签
 * 4. 可设置是否绘制OSD标签
 * 5. 可设置标签文本或图片
 * 6. 可设置OSD位置 左上角+左下角+右上角+右下角
 * 7. 可设置OSD风格 文本+日期+时间+日期时间+图片
 * 8. 自定义半透明悬浮窗体,一排按钮
 * 9. 悬浮按钮可自定义设置,包括背景颜色+按下颜色
 * 10. 发送信号通知单击了哪个悬浮按钮
 * 11. 能够识别拖进来的文件,通知url
 * 12. 提供open close pause等接口
 */
#include "HeadFile.h"
#include <QWidget>
#include <QDateTime>
#include "ffmpeg.h"
#include <QList>
#include "FDecodeThread.h"
#include <iostream>
#include <QThread>
#include "XVideoWidget.h"
#include "XAudioThread.h"
#include "XVideoThread.h"
extern "C" {
#include <libavcodec/avcodec.h>
}
using namespace std;
class QTimer;
class VideoWidget;
//class FFmpegsThread : public QThread
//{
//	Q_OBJECT
//public:
//	explicit FFmpegsThread(QObject *parent = 0);
//	//static void UIPlayerEventCallBackHandler(MP_ENG_EVENT event, int nIndex, void * pParam, void * pAppData);
//protected:
//	
//	void run();
//
//	/*bool ish265IFrame(void * pParam);
//
//	bool isIFrame(void * pParam);*/
//
//public:
//	MP_DATA_INFO pktdata;
//	QList<MP_DATA_INFO *> HStreamList;
//	QMutex mutex;
//	VideoWidget* pWidget_;
//	INT64 _h264Handle;				
//	volatile bool stopped;          //线程停止标志位
//	volatile bool isPlay;           //播放视频标志位
//
//	int nResolution_;
//
//	//void pushVideoData(MP_DATA_INFO * pData);
//
//	int getHStreamCount() { return HStreamList.size(); }
//
//	void pushHStreamInfo(MP_DATA_INFO* pData) {
//		QMutex mutex;
//		HStreamList.push_back(pData);
//	}
//	MP_DATA_INFO * getHStreamInfo() {
//		QMutexLocker locker(&mutex);
//		if (HStreamList.isEmpty())
//		{
//			return NULL;
//		}
//		return HStreamList.front();
//	}
//
//	void removeHStreamInfo() {
//		QMutexLocker locker(&mutex);
//		//HStreamList.removeFirst(); 
//		if (getHStreamCount() > 0)
//		{
//			HStreamList.pop_front();
//		}
//	}
//signals:
//	//收到图片信号
//	void receiveImage(const QImage &image);
//
//public slots:
//	//设置码流数据
//	//void pushVideoData(const MP_DATA_INFO &pData);
//	//
//	void getVideoResolution(int nResolution, int* width, int* height);
//	//初始化视频对象
//	bool init(INT64 handle, int Resolution, VideoWidget* pWidget);
//	//释放对象
//	void free();
//	//播放视频对象
//	void play();
//	//暂停播放
//	void pause();
//	//继续播放
//	void next();
//	//停止采集线程
//	void stop();
//};

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT VideoWidget : public QWidget
#else
class VideoWidget : public QWidget/*, public IVideoCall*/
#endif

{
    Q_OBJECT
    Q_ENUMS(OSDFormat)
    Q_ENUMS(OSDPosition)

    Q_PROPERTY(bool copyImage READ getCopyImage WRITE setCopyImage)
    Q_PROPERTY(bool checkLive READ getCheckLive WRITE setCheckLive)
    Q_PROPERTY(bool drawImage READ getDrawImage WRITE setDrawImage)
    Q_PROPERTY(bool fillImage READ getFillImage WRITE setFillImage)

    Q_PROPERTY(bool flowEnable READ getFlowEnable WRITE setFlowEnable)
    Q_PROPERTY(QColor flowBgColor READ getFlowBgColor WRITE setFlowBgColor)
    Q_PROPERTY(QColor flowPressColor READ getFlowPressColor WRITE setFlowPressColor)

    Q_PROPERTY(int timeout READ getTimeout WRITE setTimeout)
    Q_PROPERTY(int borderWidth READ getBorderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(QColor focusColor READ getFocusColor WRITE setFocusColor)    
    Q_PROPERTY(QString bgText READ getBgText WRITE setBgText)
    Q_PROPERTY(QImage bgImage READ getBgImage WRITE setBgImage)

    Q_PROPERTY(bool osd1Visible READ getOSD1Visible WRITE setOSD1Visible)
    Q_PROPERTY(int osd1FontSize READ getOSD1FontSize WRITE setOSD1FontSize)
    Q_PROPERTY(QString osd1Text READ getOSD1Text WRITE setOSD1Text)
    Q_PROPERTY(QColor osd1Color READ getOSD1Color WRITE setOSD1Color)
    Q_PROPERTY(QImage osd1Image READ getOSD1Image WRITE setOSD1Image)
    Q_PROPERTY(OSDFormat osd1Format READ getOSD1Format WRITE setOSD1Format)
    Q_PROPERTY(OSDPosition osd1Position READ getOSD1Position WRITE setOSD1Position)

    Q_PROPERTY(bool osd2Visible READ getOSD2Visible WRITE setOSD2Visible)
    Q_PROPERTY(int osd2FontSize READ getOSD2FontSize WRITE setOSD2FontSize)
    Q_PROPERTY(QString osd2Text READ getOSD2Text WRITE setOSD2Text)
    Q_PROPERTY(QColor osd2Color READ getOSD2Color WRITE setOSD2Color)
    Q_PROPERTY(QImage osd2Image READ getOSD2Image WRITE setOSD2Image)
    Q_PROPERTY(OSDFormat osd2Format READ getOSD2Format WRITE setOSD2Format)
    Q_PROPERTY(OSDPosition osd2Position READ getOSD2Position WRITE setOSD2Position)

public:
    //标签格式
    enum OSDFormat {
        OSDFormat_Text = 0,             //文本
        OSDFormat_Date = 1,             //日期
        OSDFormat_Time = 2,             //时间
        OSDFormat_DateTime = 3,         //日期时间
        OSDFormat_Image = 4             //图片
    };

    //标签位置
    enum OSDPosition {
        OSDPosition_Left_Top = 0,       //左上角
        OSDPosition_Left_Bottom = 1,    //左下角
        OSDPosition_Right_Top = 2,      //右上角
        OSDPosition_Right_Bottom = 3    //右下角
    };

    explicit VideoWidget(QWidget *parent = 0);
    ~VideoWidget();

	/*virtual void Init(int width, int height);
	virtual void Repaint(AVFrame *frame);*/
	//static void UIPlayerEventCallBackHandler(MP_ENG_EVENT event, int nIndex, void *pParam, void *pAppData);
protected:
	void resizeEvent(QResizeEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void dropEvent(QDropEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void paintEvent(QPaintEvent *);
	void drawBorder(QPainter *painter);
	void drawBg(QPainter *painter);
	void drawImg(QPainter *painter, QImage img);
	void drawOSD(QPainter *painter,
		bool osdVisible,
		int osdFontSize,
		const QString &osdText,
		const QColor &osdColor,
		const QImage &osdImage,
		const OSDFormat &osdFormat,
		const OSDPosition &osdPosition);

public:
	XAudioThread* at = 0;
	XVideoThread* vt = 0;
	bool isInit_ = false;
	QMutex mutex;
	//FDecodeThread* pDecodeThread_;
	QList<MP_DATA_INFO *> HStreamList;
	bool IsthreadRun_;
	//FFmpegsThread *thread_;
	//INT64 _h264Handle;
	int _nSession;				//视频标识
	//FFmpegWidget* pffmpegWidget;	//ffmpeg控件
    QTimer *timerCheck;             //定时器检查设备是否在线
    QImage image;                   //要显示的图片
    QWidget *flowPanel;             //悬浮条面板
	QLabel* pImageLable_;
	GLYuvWidget* pXvideoWidget_;	//

    bool copyImage;                 //是否拷贝图片
    bool checkLive;                 //检测是否活着
    bool drawImage;                 //是否绘制图片
    bool fillImage;                 //自动拉伸填充

    bool flowEnable;                //是否显示悬浮条
    QColor flowBgColor;             //悬浮条背景颜色
    QColor flowPressColor;          //悬浮条按下颜色

    int timeout;                    //超时时间
    int borderWidth;                //边框宽度
    QColor borderColor;             //边框颜色
    QColor focusColor;              //有焦点边框颜色    
    QString bgText;                 //默认无图像显示文字
    QImage bgImage;                 //默认无图像背景图片

    bool osd1Visible;               //显示标签1
    int osd1FontSize;               //标签1字号
    QString osd1Text;               //标签1文本
    QColor osd1Color;               //标签1颜色
    QImage osd1Image;               //标签1图片
    OSDFormat osd1Format;           //标签1文本格式
    OSDPosition osd1Position;       //标签1位置

    bool osd2Visible;               //显示标签2
    int osd2FontSize;               //标签2字号
    QString osd2Text;               //标签2文本
    QColor osd2Color;               //标签2颜色
    QImage osd2Image;               //标签2图片
    OSDFormat osd2Format;           //标签2文本格式
    OSDPosition osd2Position;       //标签2位置

private:
    //初始化解码线程
    void initThread();
    //初始化悬浮条
    void initFlowPanel();
    //初始化悬浮条样式
    void initFlowStyle();

public:
	int getSession() { return _nSession; }
	void setSession(int nSession) { _nSession = nSession; }

    QImage getImage()               const;
    QDateTime getLastTime()         const;
    QString getUrl()                const;

    bool getCopyImage()             const;
    bool getCheckLive()             const;
    bool getDrawImage()             const;
    bool getFillImage()             const;

    bool getFlowEnable()            const;
    QColor getFlowBgColor()         const;
    QColor getFlowPressColor()      const;

    int getTimeout()                const;
    int getBorderWidth()            const;
    QColor getBorderColor()         const;
    QColor getFocusColor()          const;
    QString getBgText()             const;
    QImage getBgImage()             const;

    bool getOSD1Visible()           const;
    int getOSD1FontSize()           const;
    QString getOSD1Text()           const;
    QColor getOSD1Color()           const;
    QImage getOSD1Image()           const;
    OSDFormat getOSD1Format()       const;
    OSDPosition getOSD1Position()   const;

    bool getOSD2Visible()           const;
    int getOSD2FontSize()           const;
    QString getOSD2Text()           const;
    QColor getOSD2Color()           const;
    QImage getOSD2Image()           const;
    OSDFormat getOSD2Format()       const;
    OSDPosition getOSD2Position()   const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public slots :
    //接收图像并绘制
    void updateImage(const QImage &image);
    //校验设备
    void checkVideo();
    //处理按钮单击
    void btnClicked();

signals:
    //播放成功
    void receivePlayStart();
    //播放失败
    void receivePlayError();
    //播放结束
    void receivePlayFinsh();

    //收到图片信号
    void receiveImage(const QImage &image);

    //接收到拖曳文件
    void fileDrag(const QString &url);

    //工具栏单击
    void btnClicked(const QString &objName);


	void pushVideoh264Data(const MP_DATA_INFO &pData);
public slots:
    //获取长度
    uint getLength();
    //获取当前播放位置
    uint getPosition();
    //设置播放位置
    void setPosition(int position);

    //获取静音状态
    bool getMute();
    //设置静音
    void setMute(bool mute);

    //获取音量
    int getVolume();
    //设置音量
    void setVolume(int volume);

    //设置显示间隔
    void setInterval(int interval);
    //设置休眠时间
    void setSleepTime(int sleepTime);
    //设置检测连接超时
    void setCheckTime(int checkTime);
    //设置是否检测连接
    void setCheckConn(bool checkConn);
    //设置视频流地址
    void setUrl(const QString &url);
    //设置硬件解码器名称
    void setHardware(const QString &hardware);

    //设置是否保存文件
    void setSaveFile(bool saveFile);
    //设置保存间隔
    void setSaveInterval(int saveInterval);
    //设置保存文件夹
    void setSavePath(const QString &savePath);
    //设置保存文件名称
    void setFileName(const QString &fileName);

    //设置是否拷贝图片
    void setCopyImage(bool copyImage);
    //设置是否检测活着
    void setCheckLive(bool checkLive);
    //设置是否实时绘制图片
    void setDrawImage(bool drawImage);
    //设置是否拉伸填充
    void setFillImage(bool fillImage);

    //设置是否启用悬浮条
    void setFlowEnable(bool flowEnable);    
    //设置悬浮条背景颜色
    void setFlowBgColor(const QColor &flowBgColor);
    //设置悬浮条按下颜色
    void setFlowPressColor(const QColor &flowPressColor);

    //设置超时时间
    void setTimeout(int timeout);
    //设置边框宽度
    void setBorderWidth(int borderWidth);
    //设置边框颜色
    void setBorderColor(const QColor &borderColor);
    //设置有焦点边框颜色
    void setFocusColor(const QColor &focusColor);    
    //设置无图像文字
    void setBgText(const QString &bgText);
    //设置无图像背景图
    void setBgImage(const QImage &bgImage);

    //设置标签1是否可见
    void setOSD1Visible(bool osdVisible);
    //设置标签1文字字号
    void setOSD1FontSize(int osdFontSize);
    //设置标签1文本
    void setOSD1Text(const QString &osdText);
    //设置标签1文字颜色
    void setOSD1Color(const QColor &osdColor);
    //设置标签1图片
    void setOSD1Image(const QImage &osdImage);
    //设置标签1格式
    void setOSD1Format(const OSDFormat &osdFormat);
    //设置标签1位置
    void setOSD1Position(const OSDPosition &osdPosition);

    //设置标签2是否可见
    void setOSD2Visible(bool osdVisible);
    //设置标签2文字字号
    void setOSD2FontSize(int osdFontSize);
    //设置标签2文本
    void setOSD2Text(const QString &osdText);
    //设置标签2文字颜色
    void setOSD2Color(const QColor &osdColor);
    //设置标签2图片
    void setOSD2Image(const QImage &osdImage);
    //设置标签2格式
    void setOSD2Format(const OSDFormat &osdFormat);
    //设置标签2位置
    void setOSD2Position(const OSDPosition &osdPosition);

	int getHStreamCount() { return HStreamList.size(); }

	void pushHStreamInfo(MP_DATA_INFO* pData) {
		mutex.lock();
		HStreamList.push_back(pData);
		mutex.unlock();
		//msleep(1);
	}
	MP_DATA_INFO * getHStreamInfo() {
		mutex.lock();
		if (HStreamList.isEmpty())
		{
			mutex.unlock();
			return NULL;
		}
		MP_DATA_INFO * hstream = HStreamList.front();
		HStreamList.pop_front();
		mutex.unlock();
		return hstream;
	}

	//void removeHStreamInfo() {
	//	QMutexLocker locker(&mutex);
	//	//HStreamList.removeFirst(); 
	//	if (getHStreamCount()>0)
	//	{
	//		HStreamList.pop_front();
	//	}
	//}

	//void pushFrame(MP_DATA_INFO * pData);

	//int popFrame(MP_DATA_INFO** pData);

	void startVideoThread();

	bool ish265IFrame(void * pParam);

	void setVideoh264Data(void * pData);

	void RGB2Image(char * srcBuf, int w, int h, QImage * pDistImage);

	bool isIFrame(void * pParam);

	void setVideoYUVData(void * pData);

	bool YV12ToBGR24_FFmpeg(/*unsigned char * pBufy, unsigned char * pBufu, unsigned char * pBufv,*/unsigned char * pYUV, unsigned char * pBGR24, int width, int height);

	void Yuv420p2Rgb32(unsigned char * pBufy, unsigned char * pBufu, unsigned char * pBufv, const BYTE * rgbBuffer_out, int width, int height);

	void YUV420_2_RGB(unsigned char * pBufy, unsigned char * pBufu, unsigned char * pBufv, unsigned char * pRGB, int width, int height);

	void getVideoResolution(int nResolution,int* width,int* height);
    //打开设备
    void open();
    //暂停
    void pause();
    //继续
    void next();
    //关闭设备
    void close();
    //重新加载
    void restart();
    //清空
    void clear();

	bool vtInit(AVCodecID codeID, IVideoCall *call, int width, int height);
	//bool atInit(AVCodecID codeID, IVideoCall *call, int width, int height);

	bool initPacket(void * pParam);

	void patientFrame(AVFrame *frame);

};

#endif // VIDEOWIDGET_H
