#pragma execution_character_set("utf-8")

#include "videowidget.h"
#include "qfontdatabase.h"
#include "qpushbutton.h"
#include "qtreewidget.h"
#include "qlayout.h"
#include "qtimer.h"
#include "qdir.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmimedata.h"
#include "qurl.h"
#include "qdebug.h"
#include <QDateTime>
#include "XDecode.h"
extern "C"
{
#include "libswscale/swscale.h"
};

void UIPlayerEventCallBackHandler(MP_ENG_EVENT event, int nIndex, void *pParam, void *pAppData)
{
	switch (event)
	{
	case MP_EVENT_FPS:
		break;
	case MP_EVENT_BINDWIDTH:
		break;
	case MP_EVENT_PLR:
		break;
	case MP_EVENT_ERROR:
		break;
	case MP_EVENT_ACK:
		break;
	case MP_EVENT_CAMJOIN:
		break;
	case MP_EVENT_CAMEXIT:
		break;
	case MP_EVENT_WATERMARK_LOW:
		break;
	case MP_EVENT_WATERMARK_HIGH:
		break;
	case MP_EVENT_USER_LOGIN:
		break;
	case MP_EVENT_USER_LOGOUT:
		break;
	case MP_EVENT_USER_PWD_ERROR:
		break;
	case MP_EVENT_SERVER_DISCONNECT:
		break;
	case MP_EVENT_SERVER_CONNECT:
		break;
	case MP_EVENT_MOVE_DETECTION:
		break;
	case MP_EVENT_MOVE_STOP:
		break;
	case MP_EVENT_ALARM:
		break;
	case MP_EVENT_DISK_LOW:
		break;
	case MP_EVENT_DISK_FULL:
		break;
	case MP_EVENT_DATA_READY:
	{
		VideoWidget* pWidget = (VideoWidget*)pAppData;
		pWidget->initPacket(pParam);
		//MP_DATA_INFO *pData = (MP_DATA_INFO *)pParam;
		//if (pData->type == MP_DATA_H264)   //视频数据，也可能是h265，
		//{
		//	MP_DATA_INFO *pMPData = (MP_DATA_INFO *)pData;
		//	if (pMPData->type == MP_DATA_H264)   //视频数据，也可能是h265，
		//	{
		//		int videoWidth;                 //视频宽度
		//		int videoHeight;                //视频高度
		//		int nResolution = ((pMPData->nTimestamp & 0xe000) >> 13);
		//		pWidget->getVideoResolution(nResolution, &videoWidth, &videoHeight);
		//		pWidget->vt->init(AV_CODEC_ID_H265, pWidget->pXvideoWidget_, videoWidth, videoHeight);

		//		//AVPacket *packet = av_packet_alloc();
		//		AVPacket packet = { 0 };
		//		packet.data = (uint8_t*)pData->pData;	//这里填入一个指向完整H264数据帧的指针 
		//		packet.size = pData->nLen;		//这个填入H264数据帧的大小  
		//		//packet.stream_index = AVMEDIA_TYPE_VIDEO;
		//		pWidget->vt->Push(&packet);
		//	}
		//	else if (pData->type == MP_DATA_G723)   //音频数据，对于新设备事实上是AMR_NB格式
		//	{
		//		switch (pData->nFlag)  //是 1的话是amr， 是2是aac ， 若是0，可能playback dll是老版本，
		//		{
		//		case 1:
		//		{
		//		}
		//		break;
		//		case 2:
		//		{

		//		}
		//		break;
		//		}
		//	}
			//VideoWidget* pWidget = (VideoWidget*)pAppData;
			//pWidget->setVideoh264Data(pParam);
		//	//pWidget->startVideoThread();
		//	//MP_DATA_INFO *pMPData = (MP_DATA_INFO *)pData;
		//	//if (pMPData->type == MP_DATA_H264)   //视频数据，也可能是h265，
		//	//{
		//	//	int videoWidth;                 //视频宽度
		//	//	int videoHeight;                //视频高度
		//	//	int nResolution = ((pMPData->nTimestamp & 0xe000) >> 13);
		//	//	pWidget->getVideoResolution(nResolution, &videoWidth, &videoHeight);

		//	//	if (_h264Handle == 0)
		//	//	{
		//	//		_h264Handle = H264_CreateHandle();
		//	//	}

		//	//	int pRet = H264_PutVideoStream(_h264Handle, (char*)pMPData->pData, pMPData->nLen);
		//	//	if (pRet != 0)
		//	//	{
		//	//		return;
		//	//	}

		//	//	int picWidth = videoWidth;
		//	//	int picHeight = videoHeight;
		//	//	INT32 frameSize = H264_GetVideoFrameSize_Rgb2(_h264Handle, picWidth, picHeight);
		//	//	if (frameSize == 0)
		//	//		return;

		//	//	char* buffer = new char[frameSize];
		//	//	memset(buffer, 0, sizeof(buffer));

		//	//	INT32 ret = H264_GetNextVideoFrame_Rgb2(_h264Handle, buffer, frameSize, picWidth, picHeight);
		//	//	if (ret != 0) {
		//	//		delete[] buffer;
		//	//		return;
		//	//	}

		//	//	//pMonitor->pVidoePanel_Widget_->widgets[0]->width;
		//	//	/*int width = pMonitor->pVidoePanel_Widget_->widgets[0]->width();
		//	//	int height = pMonitor->pVidoePanel_Widget_->widgets[0]->height();*/
		//	//	//QImage *tmpImg = new QImage((uchar *)buffer, picWidth, picHeight, 3 * picWidth, QImage::Format_RGB888);
		//	//	QImage* pimage = new QImage(picWidth, picHeight, QImage::Format_RGB888);
		//	//	int b, g, r;
		//	//	//设置像素
		//	//	for (int i = 0; i < picHeight; i++)
		//	//	{
		//	//		for (int j = 0; j < picWidth; j++)
		//	//		{
		//	//			b = (int)buffer[i];
		//	//			g = (int)buffer[i + 1];
		//	//			r = (int)buffer[i + 2];
		//	//			pimage->setPixel(j, i, qRgb(r, g, b));
		//	//		}
		//	//	}

		//	//	pWidget->updateImage(*pimage);

		//	//	delete pimage;
		//	//	delete[] buffer;
		//	//}
		//}
		//else if (pData->type == MP_DATA_G723)   //音频数据，对于新设备事实上是AMR_NB格式
		//{
		//}
		//else  if (pData->type == MP_DATA_YUV)
		//{
		//	VideoWidget* pWidget = (VideoWidget*)pAppData;
		//	pWidget->setVideoYUVData(pParam);
		//}
	}
	break;
	default:
		break;
	}
}

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
	pXvideoWidget_ = new GLYuvWidget(this);
	IsthreadRun_ = false;
	_nSession = -1;
	//设置强焦点
	setFocusPolicy(Qt::StrongFocus);
	//设置支持拖放
	setAcceptDrops(true);

	//定时器校验视频
	timerCheck = new QTimer(this);
	timerCheck->setInterval(10 * 1000);
	connect(timerCheck, SIGNAL(timeout()), this, SLOT(checkVideo()));

	//pffmpegWidget = new FFmpegWidget;
	image = QImage();
	copyImage = false;
	checkLive = true;
	drawImage = true;
	fillImage = false;

	flowEnable = false;
	flowBgColor = "#000000";
	flowPressColor = "#5EC7D9";

	timeout = 20;
	borderWidth = 5;
	borderColor = "#000000";
	focusColor = "#22A3A9";
	bgText = "实时视频";
	bgImage = QImage();

	osd1Visible = false;
	osd1FontSize = 12;
	osd1Text = "时间";
	osd1Color = "#FF0000";
	osd1Image = QImage();
	osd1Format = OSDFormat_DateTime;
	osd1Position = OSDPosition_Right_Top;

	osd2Visible = false;
	osd2FontSize = 12;
	osd2Text = "通道名称";
	osd2Color = "#FF0000";
	osd2Image = QImage();
	osd2Format = OSDFormat_Text;
	osd2Position = OSDPosition_Left_Bottom;

	//初始化解码线程
	this->initThread();
	//初始化悬浮条
	this->initFlowPanel();
	//初始化悬浮条样式
	this->initFlowStyle();
}

void VideoWidget::initThread()
{
	mutex.lock();
	if (!vt) vt = new XVideoThread();
	if (!at) at = new XAudioThread();

	//connect(vt, SIGNAL(RepatintImage(AVFrame*)), this, SLOT(patientFrame(AVFrame*)));

	if (vt)vt->start();
	if (at)at->start();

	mutex.unlock();
}

void VideoWidget::initFlowPanel()
{
	//顶部工具栏,默认隐藏,鼠标移入显示移除隐藏
	flowPanel = new QWidget(this);
	flowPanel->setObjectName("flowPanel");
	flowPanel->setVisible(false);

	//用布局顶住,左侧弹簧
	QHBoxLayout *layout = new QHBoxLayout;
	layout->setSpacing(2);
	layout->setMargin(0);
	layout->addStretch();
	flowPanel->setLayout(layout);

	//按钮集合名称,如果需要新增按钮则在这里增加即可
	QList<QString> btns;
	btns << "btnFlowVideo" << "btnFlowSnap" << "btnFlowSound" << "btnFlowAlarm" << "btnFlowClose";

	//有多种办法来设置图片,qt内置的图标+自定义的图标+图形字体
	//既可以设置图标形式,也可以直接图形字体设置文本
#if 0
	QList<QIcon> icons;
	icons << QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
	icons << QApplication::style()->standardIcon(QStyle::SP_FileIcon);
	icons << QApplication::style()->standardIcon(QStyle::SP_DirIcon);
	icons << QApplication::style()->standardIcon(QStyle::SP_DialogOkButton);
	icons << QApplication::style()->standardIcon(QStyle::SP_DialogCancelButton);
#else
	QList<QChar> chars;
	chars << 0xe68d << 0xe672 << 0xe674 << 0xea36 << 0xe74c;

	//判断图形字体是否存在,不存在则加入
	QFont iconFont;
	QFontDatabase fontDb;
	if (!fontDb.families().contains("iconfont")) {
		int fontId = fontDb.addApplicationFont(":/image/iconfont.ttf");
		QStringList fontName = fontDb.applicationFontFamilies(fontId);
		if (fontName.count() == 0) {
			qDebug() << "load iconfont.ttf error";
		}
	}

	if (fontDb.families().contains("iconfont")) {
		iconFont = QFont("iconfont");
		iconFont.setPixelSize(17);
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
		iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
	}
#endif

	//循环添加顶部按钮
	for (int i = 0; i < btns.count(); i++) {
		QPushButton *btn = new QPushButton;
		//绑定按钮单击事件,用来发出信号通知
		connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
		//设置标识,用来区别按钮
		btn->setObjectName(btns.at(i));
		//设置固定宽度
		btn->setFixedWidth(20);
		//设置拉伸策略使得填充
		btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		//设置焦点策略为无焦点,避免单击后焦点跑到按钮上
		btn->setFocusPolicy(Qt::NoFocus);

#if 0
		//设置图标大小和图标
		btn->setIconSize(QSize(16, 16));
		btn->setIcon(icons.at(i));
#else
		btn->setFont(iconFont);
		btn->setText(chars.at(i));
#endif

		//将按钮加到布局中
		layout->addWidget(btn);
	}
}

void VideoWidget::initFlowStyle()
{
	//设置样式以便区分,可以自行更改样式,也可以不用样式
	QStringList qss;
	QString rgba = QString("rgba(%1,%2,%3,150)").arg(flowBgColor.red()).arg(flowBgColor.green()).arg(flowBgColor.blue());
	qss.append(QString("#flowPanel{background:%1;border:none;}").arg(rgba));
	qss.append(QString("QPushButton{border:none;padding:0px;background:rgba(0,0,0,0);}"));
	qss.append(QString("QPushButton:pressed{color:%1;}").arg(flowPressColor.name()));
	flowPanel->setStyleSheet(qss.join(""));
}

VideoWidget::~VideoWidget()
{
	if (timerCheck->isActive()) {
		timerCheck->stop();
	}

	close();
}

void VideoWidget::resizeEvent(QResizeEvent *)
{
	//重新设置顶部工具栏的位置和宽高,可以自行设置顶部显示或者底部显示
	int height = 20;
	flowPanel->setGeometry(borderWidth, borderWidth, this->width() - (borderWidth * 2), height);
	pXvideoWidget_->setGeometry(borderWidth, borderWidth, this->width(), this->height());
	//flowPanel->setGeometry(borderWidth, this->height() - height - borderWidth, this->width() - (borderWidth * 2), height);
}

void VideoWidget::enterEvent(QEvent *)
{
	//这里还可以增加一个判断,是否获取了焦点的才需要显示
	//if (this->hasFocus()) {}
	if (flowEnable) {
		flowPanel->setVisible(true);
	}
}

void VideoWidget::leaveEvent(QEvent *)
{
	if (flowEnable) {
		flowPanel->setVisible(false);
	}
}

void VideoWidget::dropEvent(QDropEvent *event)
{
	//拖放完毕鼠标松开的时候执行
	//判断拖放进来的类型,取出文件,进行播放
	if (event->mimeData()->hasUrls()) {
		QString url = event->mimeData()->urls().first().toLocalFile();
		this->close();
		this->setUrl(url);
		this->open();
		emit fileDrag(url);
	}
	else if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
		QTreeWidget *treeWidget = (QTreeWidget *)event->source();
		if (treeWidget != 0) {
			QString url = treeWidget->currentItem()->data(0, Qt::UserRole).toString();
			this->close();
			this->setUrl(url);
			this->open();
			emit fileDrag(url);
		}
	}
}

void VideoWidget::dragEnterEvent(QDragEnterEvent *event)
{
	//拖曳进来的时候先判断下类型,非法类型则不处理
	if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
		event->setDropAction(Qt::CopyAction);
		event->accept();
	}
	else if (event->mimeData()->hasFormat("text/uri-list")) {
		event->setDropAction(Qt::LinkAction);
		event->accept();
	}
	else {
		event->ignore();
	}
}

void VideoWidget::paintEvent(QPaintEvent *)
{
	//如果不需要绘制
	if (!drawImage) {
		return;
	}

	//qDebug() << TIMEMS << "paintEvent" << objectName();
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);

	//绘制边框
	drawBorder(&painter);
	if (!image.isNull()) {
		//绘制背景图片
		drawImg(&painter, image);
		//绘制标签
		drawOSD(&painter, osd1Visible, osd1FontSize, osd1Text, osd1Color, osd1Image, osd1Format, osd1Position);
		drawOSD(&painter, osd2Visible, osd2FontSize, osd2Text, osd2Color, osd2Image, osd2Format, osd2Position);
	}
	else {
		//绘制背景
		drawBg(&painter);
	}
}

void VideoWidget::drawBorder(QPainter *painter)
{
	if (borderWidth == 0) {
		return;
	}

	painter->save();
	QPen pen;
	pen.setWidth(borderWidth);
	pen.setColor(hasFocus() ? focusColor : borderColor);
	painter->setPen(pen);
	painter->drawRect(rect());
	painter->restore();
}

void VideoWidget::drawBg(QPainter *painter)
{
	painter->save();

	//背景图片为空则绘制文字,否则绘制背景图片
	if (bgImage.isNull()) {
		painter->setFont(this->font());
		painter->setPen(palette().foreground().color());
		painter->drawText(rect(), Qt::AlignCenter, bgText);
	}
	else {
		//居中绘制
		int x = rect().center().x() - bgImage.width() / 2;
		int y = rect().center().y() - bgImage.height() / 2;
		QPoint point(x, y);
		painter->drawImage(point, bgImage);
	}

	painter->restore();
}

void VideoWidget::drawImg(QPainter *painter, QImage img)
{
	painter->save();

	int offset = borderWidth * 1 + 0;
	if (fillImage) {
		QRect rect(offset / 2, offset / 2, width() - offset, height() - offset);
		painter->drawImage(rect, img);
	}
	else {
		//按照比例自动居中绘制
		img = img.scaled(width() - offset, height() - offset, Qt::KeepAspectRatio);
		int x = rect().center().x() - img.width() / 2;
		int y = rect().center().y() - img.height() / 2;
		QPoint point(x, y);
		painter->drawImage(point, img);
	}

	painter->restore();
}

void VideoWidget::drawOSD(QPainter *painter,
	bool osdVisible,
	int osdFontSize,
	const QString &osdText,
	const QColor &osdColor,
	const QImage &osdImage,
	const VideoWidget::OSDFormat &osdFormat,
	const VideoWidget::OSDPosition &osdPosition)
{
	if (!osdVisible) {
		return;
	}

	painter->save();

	//标签位置尽量偏移多一点避免遮挡
	QRect osdRect(rect().x() + (borderWidth * 2), rect().y() + (borderWidth * 2), width() - (borderWidth * 5), height() - (borderWidth * 5));
	int flag = Qt::AlignLeft | Qt::AlignTop;
	QPoint point = QPoint(osdRect.x(), osdRect.y());

	if (osdPosition == OSDPosition_Left_Top) {
		flag = Qt::AlignLeft | Qt::AlignTop;
		point = QPoint(osdRect.x(), osdRect.y());
	}
	else if (osdPosition == OSDPosition_Left_Bottom) {
		flag = Qt::AlignLeft | Qt::AlignBottom;
		point = QPoint(osdRect.x(), osdRect.height() - osdImage.height());
	}
	else if (osdPosition == OSDPosition_Right_Top) {
		flag = Qt::AlignRight | Qt::AlignTop;
		point = QPoint(osdRect.width() - osdImage.width(), osdRect.y());
	}
	else if (osdPosition == OSDPosition_Right_Bottom) {
		flag = Qt::AlignRight | Qt::AlignBottom;
		point = QPoint(osdRect.width() - osdImage.width(), osdRect.height() - osdImage.height());
	}

	if (osdFormat == OSDFormat_Image) {
		painter->drawImage(point, osdImage);
	}
	else {
		QDateTime now = QDateTime::currentDateTime();
		QString text = osdText;
		if (osdFormat == OSDFormat_Date) {
			text = now.toString("yyyy-MM-dd");
		}
		else if (osdFormat == OSDFormat_Time) {
			text = now.toString("HH:mm:ss");
		}
		else if (osdFormat == OSDFormat_DateTime) {
			text = now.toString("yyyy-MM-dd HH:mm:ss");
		}

		//设置颜色及字号
		QFont font;
		font.setPixelSize(osdFontSize);
		painter->setPen(osdColor);
		painter->setFont(font);

		painter->drawText(osdRect, flag, text);
	}

	painter->restore();
}

QImage VideoWidget::getImage() const
{
	return this->image;
}

QDateTime VideoWidget::getLastTime() const
{
	return QDateTime::currentDateTime();
}

QString VideoWidget::getUrl() const
{
	return this->property("url").toString();
}

bool VideoWidget::getCopyImage() const
{
	return this->copyImage;
}

bool VideoWidget::getCheckLive() const
{
	return this->checkLive;
}

bool VideoWidget::getDrawImage() const
{
	return this->drawImage;
}

bool VideoWidget::getFillImage() const
{
	return this->fillImage;
}

bool VideoWidget::getFlowEnable() const
{
	return this->flowEnable;
}

QColor VideoWidget::getFlowBgColor() const
{
	return this->flowBgColor;
}

QColor VideoWidget::getFlowPressColor() const
{
	return this->flowPressColor;
}

int VideoWidget::getTimeout() const
{
	return this->timeout;
}

int VideoWidget::getBorderWidth() const
{
	return this->borderWidth;
}

QColor VideoWidget::getBorderColor() const
{
	return this->borderColor;
}

QColor VideoWidget::getFocusColor() const
{
	return this->focusColor;
}

QString VideoWidget::getBgText() const
{
	return this->bgText;
}

QImage VideoWidget::getBgImage() const
{
	return this->bgImage;
}

bool VideoWidget::getOSD1Visible() const
{
	return this->osd1Visible;
}

int VideoWidget::getOSD1FontSize() const
{
	return this->osd1FontSize;
}

QString VideoWidget::getOSD1Text() const
{
	return this->osd1Text;
}

QColor VideoWidget::getOSD1Color() const
{
	return this->osd1Color;
}

QImage VideoWidget::getOSD1Image() const
{
	return this->osd1Image;
}

VideoWidget::OSDFormat VideoWidget::getOSD1Format() const
{
	return this->osd1Format;
}

VideoWidget::OSDPosition VideoWidget::getOSD1Position() const
{
	return this->osd1Position;
}

bool VideoWidget::getOSD2Visible() const
{
	return this->osd2Visible;
}

int VideoWidget::getOSD2FontSize() const
{
	return this->osd2FontSize;
}

QString VideoWidget::getOSD2Text() const
{
	return this->osd2Text;
}

QColor VideoWidget::getOSD2Color() const
{
	return this->osd2Color;
}

QImage VideoWidget::getOSD2Image() const
{
	return this->osd2Image;
}

VideoWidget::OSDFormat VideoWidget::getOSD2Format() const
{
	return this->osd2Format;
}

VideoWidget::OSDPosition VideoWidget::getOSD2Position() const
{
	return this->osd2Position;
}

QSize VideoWidget::sizeHint() const
{
	return QSize(500, 350);
}

QSize VideoWidget::minimumSizeHint() const
{
	return QSize(50, 35);
}

void VideoWidget::updateImage(const QImage &image)
{
	//拷贝图片有个好处,当处理器比较差的时候,图片不会产生断层,缺点是占用时间
	//默认QImage类型是浅拷贝,可能正在绘制的时候,那边已经更改了图片的上部分数据
	this->image = copyImage ? image.copy() : image;
	this->update();
}

void VideoWidget::checkVideo()
{
	QDateTime now = QDateTime::currentDateTime();
	QDateTime lastTime = now;
	int sec = lastTime.secsTo(now);
	if (sec >= timeout) {
		restart();
	}
}

void VideoWidget::btnClicked()
{
	QPushButton *btn = (QPushButton *)sender();
	emit btnClicked(btn->objectName());
}

uint VideoWidget::getLength()
{
	return 0;
}

uint VideoWidget::getPosition()
{
	return 0;
}

void VideoWidget::setPosition(int position)
{

}

bool VideoWidget::getMute()
{
	return false;
}

void VideoWidget::setMute(bool mute)
{

}

int VideoWidget::getVolume()
{
	return 0;
}

void VideoWidget::setVolume(int volume)
{

}

void VideoWidget::setInterval(int interval)
{

}

void VideoWidget::setSleepTime(int sleepTime)
{

}

void VideoWidget::setCheckTime(int checkTime)
{

}

void VideoWidget::setCheckConn(bool checkConn)
{

}

void VideoWidget::setUrl(const QString &url)
{
	this->setProperty("url", url);
}

void VideoWidget::setHardware(const QString &hardware)
{

}

void VideoWidget::setSaveFile(bool saveFile)
{

}

void VideoWidget::setSaveInterval(int saveInterval)
{

}

void VideoWidget::setSavePath(const QString &savePath)
{
	//如果目录不存在则新建
	QDir dir(savePath);
	if (!dir.exists()) {
		dir.mkdir(savePath);
	}


}

void VideoWidget::setFileName(const QString &fileName)
{

}

void VideoWidget::setCopyImage(bool copyImage)
{
	this->copyImage = copyImage;
}

void VideoWidget::setCheckLive(bool checkLive)
{
	this->checkLive = checkLive;
}

void VideoWidget::setDrawImage(bool drawImage)
{
	this->drawImage = drawImage;
}

void VideoWidget::setFillImage(bool fillImage)
{
	this->fillImage = fillImage;
}

void VideoWidget::setFlowEnable(bool flowEnable)
{
	this->flowEnable = flowEnable;
}

void VideoWidget::setFlowBgColor(const QColor &flowBgColor)
{
	if (this->flowBgColor != flowBgColor) {
		this->flowBgColor = flowBgColor;
		this->initFlowStyle();
	}
}

void VideoWidget::setFlowPressColor(const QColor &flowPressColor)
{
	if (this->flowPressColor != flowPressColor) {
		this->flowPressColor = flowPressColor;
		this->initFlowStyle();
	}
}

void VideoWidget::setTimeout(int timeout)
{
	this->timeout = timeout;
}

void VideoWidget::setBorderWidth(int borderWidth)
{
	this->borderWidth = borderWidth;
}

void VideoWidget::setBorderColor(const QColor &borderColor)
{
	this->borderColor = borderColor;
}

void VideoWidget::setFocusColor(const QColor &focusColor)
{
	this->focusColor = focusColor;
}

void VideoWidget::setBgText(const QString &bgText)
{
	this->bgText = bgText;
}

void VideoWidget::setBgImage(const QImage &bgImage)
{
	this->bgImage = bgImage;
}

void VideoWidget::setOSD1Visible(bool osdVisible)
{
	this->osd1Visible = osdVisible;
}

void VideoWidget::setOSD1FontSize(int osdFontSize)
{
	this->osd1FontSize = osdFontSize;
}

void VideoWidget::setOSD1Text(const QString &osdText)
{
	this->osd1Text = osdText;
}

void VideoWidget::setOSD1Color(const QColor &osdColor)
{
	this->osd1Color = osdColor;
}

void VideoWidget::setOSD1Image(const QImage &osdImage)
{
	this->osd1Image = osdImage;
}

void VideoWidget::setOSD1Format(const VideoWidget::OSDFormat &osdFormat)
{
	this->osd1Format = osdFormat;
}

void VideoWidget::setOSD1Position(const VideoWidget::OSDPosition &osdPosition)
{
	this->osd1Position = osdPosition;
}

void VideoWidget::setOSD2Visible(bool osdVisible)
{
	this->osd2Visible = osdVisible;
}

void VideoWidget::setOSD2FontSize(int osdFontSize)
{
	this->osd2FontSize = osdFontSize;
}

void VideoWidget::setOSD2Text(const QString &osdText)
{
	this->osd2Text = osdText;
}

void VideoWidget::setOSD2Color(const QColor &osdColor)
{
	this->osd2Color = osdColor;
}

void VideoWidget::setOSD2Image(const QImage &osdImage)
{
	this->osd2Image = osdImage;
}

void VideoWidget::setOSD2Format(const VideoWidget::OSDFormat &osdFormat)
{
	this->osd2Format = osdFormat;
}

void VideoWidget::setOSD2Position(const VideoWidget::OSDPosition &osdPosition)
{
	this->osd2Position = osdPosition;
}

bool VideoWidget::ish265IFrame(void *pParam)
{
	MP_DATA_INFO *pData = (MP_DATA_INFO *)pParam;

	char itmp[5] = { 0x00,0x00,0x00,0x01,0x40 };

	if (pData->nLen < 10)
		return false;

	if (memcmp(pData->pData, itmp, 5) == 0)
		return true;
	else
		return false;
}

void VideoWidget::setVideoh264Data(void * pData)
{
	////thread_->pushVideoData(pData);
	////MP_DATA_INFO *spData = (MP_DATA_INFO *)pData;
	////thread_->pushVideoData(*spData);
	////emit pushVideoh264Data(*spData);
	//bool iFrame = isIFrame(pData);
	//bool b265Frame = ish265IFrame(pData);
	//MP_DATA_INFO *pMPData = (MP_DATA_INFO *)pData;
	///*pushHStreamInfo(pMPData);

	//if (_h264Handle == 0)
	//{
	//	_h264Handle = H264_CreateHandle();
	//}
	//if (thread_->isRunning() == false)
	//{
	//	IsthreadRun_ = true;
	//	thread_->init(_h264Handle, 0, this);
	//	thread_->play();
	//	thread_->start();
	//}*/
	//if (pMPData->type == MP_DATA_H264)   //视频数据，也可能是h265，
	//{
	//	QDateTime current_date_time = QDateTime::currentDateTime();
	//	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
	//	if (b265Frame == false)
	//	{
	//		qDebug() << ("b265Frame == false!") << "time:" << current_date;
	//	}
	//	else
	//	{
	//		qDebug() << ("b265Frame == true!") << "time:" << current_date;;
	//	}

	//	int videoWidth;                 //视频宽度
	//	int videoHeight;                //视频高度
	//	int nResolution = ((pMPData->nTimestamp & 0xe000) >> 13);
	//	getVideoResolution(nResolution, &videoWidth, &videoHeight);

	//	if (_h264Handle == 0)
	//	{
	//		_h264Handle = H264_CreateHandle();
	//	}

	//	/*int picWidth = videoWidth;
	//	int picHeight = videoHeight;
	//	INT32 frameSize = H264_GetVideoFrameSize_Rgb2(_h264Handle, picWidth, picHeight);
	//	if (frameSize == 0)
	//	return;

	//	char* buffer = new char[frameSize];
	//	memset(buffer, 0, sizeof(buffer));*/
	//	/*while (true)
	//	{
	//	if
	//	}*/
	//	int pRet = H264_PutVideoStream(_h264Handle, (char*)pMPData->pData, pMPData->nLen/*, buffer, frameSize,picWidth, picHeight*/);
	//	if (pRet != 0)
	//	{
	//		//delete[] buffer;
	//		return;
	//	}
	//	/*if (thread_->isRunning() == false)
	//	{
	//	IsthreadRun_ = true;
	//	thread_->init(_h264Handle, nResolution);
	//	thread_->play();
	//	thread_->start();
	//	}*/
	//	/*QDateTime current_date_times = QDateTime::currentDateTime();
	//	QString current_dates = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
	//	qDebug() << "H264_PutVideoStreamTIME:" << current_dates;
	//	QImage image((uchar*)buffer, picWidth, picHeight, QImage::Format_RGB888);
	//	QImage imgs = image.rgbSwapped();

	//	setFillImage(false);
	//	this->updateImage(imgs);*/
	//	int picWidth = videoWidth;
	//	int picHeight = videoHeight;
	//	INT32 frameSize = H264_GetVideoFrameSize_Rgb2(_h264Handle, picWidth, picHeight);
	//	if (frameSize == 0)
	//		return;

	//	char* buffer = new char[frameSize];
	//	memset(buffer, 0, sizeof(buffer));

	//	while (true)
	//	{
	//		INT32 ret = H264_GetNextVideoFrame_Rgb2(_h264Handle, buffer, frameSize, picWidth, picHeight);
	//		if (ret != AVERROR(EAGAIN))
	//		{
	//			QImage image((uchar*)buffer, picWidth, picHeight, QImage::Format_RGB888);
	//			QImage imgs = image.rgbSwapped();

	//			setFillImage(false);
	//			this->updateImage(imgs);
	//			qDebug() << "receiveError:" << QString::number(ret);
	//			break;
	//		}
	//	}
	//	/*INT32 ret = H264_GetNextVideoFrame_Rgb2(_h264Handle, buffer, frameSize, picWidth, picHeight);
	//	if (ret != 0) {
	//	delete[] buffer;
	//	return;
	//	}
	//	QImage image((uchar*)buffer, picWidth, picHeight, QImage::Format_RGB888);
	//	QImage imgs = image.rgbSwapped();*/
	//	//QImage img = imgs.scaled(this->size(), Qt::IgnoreAspectRatio);

	//	//QPixmap pixmap = QPixmap::fromImage(image);
	//	//QImage* image = new QImage(picWidth, picHeight, QImage::Format_RGB888);
	//	//	for(int h = 0; h < picHeight; h ++){
	//	//	// scanLine返回ptr该行的数据的开始
	//	//	memcpy(image->scanLine(h),(void*)buffer[h], picWidth * 3);
	//	//}
	//	//QImage tempImage((uchar*)buffer, picWidth, picHeight, QImage::Format_RGB888);
	//	//QImage img = tempImage.scaled(this->size(), Qt::IgnoreAspectRatio);
	//	//QImage* destimage = new QImage(picWidth, picHeight, QImage::Format_RGB888);
	//	//RGB2Image(buffer, picWidth, picHeight, destimage);
	//	/*	int  W_24 = (picWidth * 24 + 31) / 32 * 4;
	//	QByteArray imageByteArray = QByteArray((const char*)buffer, W_24*picHeight);

	//	uchar*  transData = (unsigned char*)imageByteArray.data();

	//	QImage desImage(transData, picWidth, picHeight, QImage::Format_RGB888);*/

	//	//pMonitor->pVidoePanel_Widget_->widgets[0]->width;
	//	/*int width = pMonitor->pVidoePanel_Widget_->widgets[0]->width();
	//	int height = pMonitor->pVidoePanel_Widget_->widgets[0]->height();*/
	//	//QImage *tempImage = new QImage(buffer, width, height, 3 * width, QImage::Format_RGB888);
	//	//QImage pimage((uchar *)buffer, picWidth, picHeight, 3 * picWidth, QImage::Format_RGB888);
	//	//QImage image((uchar *)buffer, picWidth, picHeight, 24, 0, 256, QImage::Format_RGB888);
	//	//QImage img = desImage.scaled(this->size(), Qt::IgnoreAspectRatio);
	//	//QImage* pimage = new QImage(picWidth, picHeight, QImage::Format_RGB888);
	//	//QImage desImage = QImage(picWidth, picHeight, QImage::Format_RGB32); //RGB32

	//	//																	 //RGB分量值
	//	//int b = 0;
	//	//int g = 0;
	//	//int r = 0;

	//	////设置像素
	//	//for (int i = 0; i < picHeight; i++)
	//	//{
	//	//	for (int j = 0; j < picWidth; j++)
	//	//	{
	//	//		b = (int)*(buffer + i*picWidth + j);
	//	//		g = b;
	//	//		r = g;
	//	//		desImage.setPixel(j, i, qRgb(r, g, b));
	//	//	}
	//	//}
	//	/*setFillImage(false);
	//	this->updateImage(imgs);*/

	//	//delete pimage;
	//	delete[] buffer;
	//}
}

bool VideoWidget::isIFrame(void *pParam)
{
	MP_DATA_INFO *pData = (MP_DATA_INFO *)pParam;

	char itmp[5] = { 0x00,0x00,0x00,0x01,0x67 };

	if (pData->nLen < 10)
		return false;

	if (memcmp(pData->pData, itmp, 5) == 0)
		return true;
	else
		return false;
}

void VideoWidget::setVideoYUVData(void * pData)
{
	MP_DATA_INFO *pYUVData = (MP_DATA_INFO *)pData;
	if (pYUVData->type == MP_DATA_YUV)
	{

		MP_YUV_INFO *pYUVInfo = (MP_YUV_INFO *)pYUVData->pData;
		int nSize = pYUVInfo->nWidth*pYUVInfo->nHeight;//Height，Width分别为一帧的高和宽
		unsigned char* m_pBuf = new unsigned char[nSize * 3 / 2];
		//int nSize = pYUVInfo->nWidth*pYUVInfo->nHeight;//Height，Width分别为一帧的高和宽
		unsigned char*p = m_pBuf;//m_pBuf为存放YUV420码流的缓存，足够大
		memcpy(p, pYUVInfo->pY, nSize);//yPointer指向Y分量的缓冲区
		p += nSize;
		memcpy(p, pYUVInfo->pU, nSize / 4);
		p += nSize / 4;
		memcpy(p, pYUVInfo->pV, nSize / 4);
		int len = nSize * 3 / 2; //len为YUV420码流的长度

		unsigned char* rgb24 = new unsigned char[nSize];
		YV12ToBGR24_FFmpeg(m_pBuf, rgb24, pYUVInfo->nWidth, pYUVInfo->nHeight);

		/*char* rgb = new char[pYUVInfo->nWidth*pYUVInfo->nHeight * sizeof(RGB32)];
		Yuv420p2Rgb32(pYUVInfo->pY, pYUVInfo->pU, pYUVInfo->pV, (unsigned char*)rgb, pYUVInfo->nWidth, pYUVInfo->nHeight);*/
		QImage pimage((uchar *)rgb24, pYUVInfo->nWidth, pYUVInfo->nHeight, QImage::Format_RGB888);
		QImage img = pimage.scaled(this->size(), Qt::IgnoreAspectRatio);

		this->updateImage(img);
		//pMonitor->RGB2Image(rgb, pYUVData->nWidth, pYUVData->nHeight, pimage);

		//pMonitor->pVidoePanel_Widget_->Play(*pimage);
		//delete pimage;
		delete[] rgb24;
	}
}

bool VideoWidget::YV12ToBGR24_FFmpeg(/*unsigned char * pBufy, unsigned char * pBufu, unsigned char * pBufv,*/unsigned char* pYUV, unsigned char* pBGR24, int width, int height)
{
	if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
		return false;
	//int srcNumBytes,dstNumBytes;
	//uint8_t *pSrc,*pDst;
	AVPicture pFrameYUV, pFrameBGR;

	//pFrameYUV = avpicture_alloc();
	//srcNumBytes = avpicture_get_size(PIX_FMT_YUV420P,width,height);
	//pSrc = (uint8_t *)malloc(sizeof(uint8_t) * srcNumBytes);
	avpicture_fill(&pFrameYUV, pYUV, AV_PIX_FMT_YUV420P, width, height);

	//U,V互换
	uint8_t * ptmp = pFrameYUV.data[1];
	pFrameYUV.data[1] = pFrameYUV.data[2];
	pFrameYUV.data[2] = ptmp;

	//pFrameBGR = avcodec_alloc_frame();
	//dstNumBytes = avpicture_get_size(PIX_FMT_BGR24,width,height);
	//pDst = (uint8_t *)malloc(sizeof(uint8_t) * dstNumBytes);
	avpicture_fill(&pFrameBGR, pBGR24, AV_PIX_FMT_BGR24, width, height);

	struct SwsContext* imgCtx = NULL;
	imgCtx = sws_getContext(width, height, AV_PIX_FMT_YUV420P, width, height, AV_PIX_FMT_BGR24, SWS_BILINEAR, 0, 0, 0);

	if (imgCtx != NULL) {
		sws_scale(imgCtx, pFrameYUV.data, pFrameYUV.linesize, 0, height, pFrameBGR.data, pFrameBGR.linesize);
		if (imgCtx) {
			sws_freeContext(imgCtx);
			imgCtx = NULL;
		}
		return true;
	}
	else {
		sws_freeContext(imgCtx);
		imgCtx = NULL;
		return false;
	}
}

void  VideoWidget::Yuv420p2Rgb32(unsigned char *pBufy, unsigned char *pBufu, unsigned char *pBufv, const  BYTE  *rgbBuffer_out, int  width, int  height)
{
	//BYTE  *yuvBuffer = (BYTE  *)yuvBuffer_in;
	RGB32 *rgb32Buffer = (RGB32 *)rgbBuffer_out;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int  index = y * width + x;

			int  indexY = y * width + x;
			int  indexU = width * height + y / 2 * width / 2 + x / 2;
			int  indexV = width * height + width * height / 4 + y / 2 * width / 2 + x / 2;

			BYTE  Y = (BYTE)pBufy[indexY]; //yuvBuffer[indexY];
			BYTE  U = (BYTE)pBufu[indexU];// yuvBuffer[indexU];
			BYTE  V = (BYTE)pBufv[indexV];// yuvBuffer[indexV];

			RGB32 *rgbNode = &rgb32Buffer[index];

			///这转换的公式 百度有好多 下面这个效果相对好一些

			rgbNode->rgbRed = Y + 1.402 * (V - 128);
			rgbNode->rgbGreen = Y - 0.34413 * (U - 128) - 0.71414*(V - 128);
			rgbNode->rgbBlue = Y + 1.772*(U - 128);
		}
	}

	//for (int y = 0; y < height; y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{
	//		int  index = y * width + x;

	//		/*	int  indexY = y * width + x;
	//			int  indexU = width * height + y / 2 * width / 2 + x / 2;
	//			int  indexV = width * height + width * height / 4 + y / 2 * width / 2 + x / 2;*/

	//		BYTE  Y = (BYTE)pBufy[index]; //yuvBuffer[indexY];
	//		BYTE  U = (BYTE)pBufu[index];// yuvBuffer[indexU];
	//		BYTE  V = (BYTE)pBufv[index];// yuvBuffer[indexV];

	//		RGB32 *rgbNode = &rgb32Buffer[index];

	//		///这转换的公式 百度有好多 下面这个效果相对好一些

	//		rgbNode->rgbRed = Y + 1.402 * (V - 128);
	//		rgbNode->rgbGreen = Y - 0.34413 * (U - 128) - 0.71414*(V - 128);
	//		rgbNode->rgbBlue = Y + 1.772*(U - 128);
	//	}
	//}
}

void VideoWidget::YUV420_2_RGB(unsigned char *pBufy, unsigned char *pBufu, unsigned char *pBufv, unsigned char* pRGB, int width, int height)
{
	//找到Y、U、V在内存中的首地址  
	unsigned char* pY = pBufy;// pYUV;
	unsigned char* pU = pBufu;// pYUV + height*width;
	unsigned char* pV = pBufv;// pU + (height*width / 4);


	unsigned char* pBGR = NULL;
	unsigned char R = 0;
	unsigned char G = 0;
	unsigned char B = 0;
	unsigned char Y = 0;
	unsigned char U = 0;
	unsigned char V = 0;
	double temp = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//找到相应的RGB首地址  
			pBGR = pRGB + i*width * 3 + j * 3;

			//取Y、U、V的数据值  
			Y = *(pY + i*width + j);
			U = *pU;
			V = *pV;

			//yuv转rgb公式  
			//yuv转rgb公式  
			temp = Y + ((1.773) * (U - 128));
			B = temp < 0 ? 0 : (temp > 255 ? 255 : (unsigned char)temp);

			temp = (Y - (0.344) * (U - 128) - (0.714) * (V - 128));
			G = temp < 0 ? 0 : (temp > 255 ? 255 : (unsigned char)temp);

			temp = (Y + (1.403)*(V - 128));
			R = temp < 0 ? 0 : (temp > 255 ? 255 : (unsigned char)temp);

			//将转化后的rgb保存在rgb内存中，注意放入的顺序b是最低位  
			*pBGR = B;
			*(pBGR + 1) = G;
			*(pBGR + 2) = R;


			if (j % 2 != 0)
			{
				*pU++;
				*pV++;
			}

		}
		if (i % 2 == 0)
		{
			pU = pU - width / 2;
			pV = pV - width / 2;
		}
	}
}

void VideoWidget::getVideoResolution(int nResolution, int * width, int * height)
{
	if (nResolution == 0)
	{
		//should retieve from video streaming
		*width = 0;
		*height = 0;
	}
	else if (nResolution == 1)
	{
		*width = 176;
		*height = 144;
	}
	else if (nResolution == 2)
	{
		*width = 320;
		*height = 240;
	}
	else if (nResolution == 3)
	{
		*width = 352;
		*height = 288;
	}
	else if (nResolution == 4)
	{
		*width = 704;
		*height = 288;
	}
	else if (nResolution == 5)
	{
		*width = 704;
		*height = 576;
	}
	else if (nResolution == 6)
	{
		*width = 1280;
		*height = 720;
	}
	else if (nResolution == 7)
	{
		*width = 1920;
		*height = 1080;
	}
}

void VideoWidget::open()
{
	//qDebug() << TIMEMS << "open video" << objectName();
	clear();

	//如果是图片则只显示图片就行
	image = QImage(this->property("url").toString());
	if (!image.isNull()) {
		this->update();
		return;
	}



	if (checkLive) {
		timerCheck->start();
	}
}

void VideoWidget::pause()
{

}

void VideoWidget::next()
{

}

void VideoWidget::close()
{
	if (checkLive) {
		timerCheck->stop();
	}

	QTimer::singleShot(1, this, SLOT(clear()));

//	H264_CloseHandle(_h264Handle);
//	_h264Handle = 0;
}

void VideoWidget::restart()
{
	//qDebug() << TIMEMS << "restart video" << objectName();
	close();
	QTimer::singleShot(10, this, SLOT(open()));
}

void VideoWidget::clear()
{
	image = QImage();
	this->update();

//	H264_CloseHandle(_h264Handle);
//	_h264Handle = 0;
}

bool VideoWidget::vtInit(AVCodecID codeID, IVideoCall * call, int width, int height)
{
	if (isInit_ == true)
	{
		return true;
	}
	if (vt->init(codeID, call, width, height) == false)
		return false;

	isInit_ = true;
	return true;
}

bool VideoWidget::initPacket(void * pParam)
{
	mutex.lock();
	{
		MP_DATA_INFO *pMPData = (MP_DATA_INFO *)pParam;
		if (!pMPData)
		{
			mutex.unlock();
			return false;
		}
		if (pMPData->type == MP_DATA_H264)   //视频数据，也可能是h265，
		{
			int videoWidth;                 //视频宽度
			int videoHeight;                //视频高度
			int nResolution = ((pMPData->nTimestamp & 0xe000) >> 13);
			getVideoResolution(nResolution, &videoWidth, &videoHeight);
			vtInit(AV_CODEC_ID_H265, pXvideoWidget_, videoWidth, videoHeight);

			AVPacket *packet = av_packet_alloc();
			//AVPacket packet = { 0 };
			av_init_packet(packet);
			av_new_packet(packet, pMPData->nLen);
			//packet->data = (uint8_t*)pMPData->pData;	//这里填入一个指向完整H264数据帧的指针 
			memcpy(packet->data, (uint8_t*)pMPData->pData, pMPData->nLen);
			packet->size = pMPData->nLen;		//这个填入H264数据帧的大小  
			packet->stream_index = AVMEDIA_TYPE_VIDEO;
			//packet->pos = 0;
			//packet->dts = 0;
			//packet->pts = 0;
			cout << "video Packet len: " << pMPData->nLen << endl;
			vt->Push(packet);
		}
		else if (pMPData->type == MP_DATA_G723)   //音频数据，对于新设备事实上是AMR_NB格式
		{
			switch (pMPData->nFlag)  //是 1的话是amr， 是2是aac ， 若是0，可能playback dll是老版本，
			{
			case 1:
			{

			}
			break;
			case 2:
			{

			}
			break;
			}
		}
	}
	mutex.unlock();
	return true;
}

void VideoWidget::patientFrame(AVFrame * frame)
{
	if (!frame)return;
	mutex.lock();
	//qDebug() << "frame->width:" << frame->width << "frame->height:" << frame->height;
	//容错，保证尺寸正确
	//if (!datas[0] || width*height == 0/* || frame->width != this->width || frame->height != this->height*/)
	//{
	//	av_frame_free(&frame);
	//	mux.unlock();
	//	return;
	//}
	//if (width == frame->linesize[0]) //无需对齐
	//{
	//	memcpy(datas[0], frame->data[0], width*height);
	//	memcpy(datas[1], frame->data[1], width*height / 4);
	//	memcpy(datas[2], frame->data[2], width*height / 4);
	//}
	//else//行对齐问题
	//{
		unsigned char *datas[3] = { 0 };
		int videowidth = frame->width;
		int videoheight = frame->height;
		///分配材质内存空间
		//if (datas[0])
		{
			datas[0] = new unsigned char[videowidth*videoheight];		//Y
			datas[1] = new unsigned char[videowidth*videoheight / 4];	//U
			datas[2] = new unsigned char[videowidth*videoheight / 4];	//V
		}
		
		memcpy(datas[0], frame->data[0], videowidth*videoheight);
		memcpy(datas[1], frame->data[1], videowidth*videoheight / 4);
		memcpy(datas[2], frame->data[2], videowidth*videoheight / 4);
		//for (int i = 0; i < videoheight; i++) //Y 
		//	memcpy(datas[0] + videowidth*i, frame->data[0] + frame->linesize[0] * i, videowidth);
		//for (int i = 0; i < videoheight / 2; i++) //U
		//	memcpy(datas[1] + videowidth / 2 * i, frame->data[1] + frame->linesize[1] * i, videowidth / 2);
		//for (int i = 0; i < videoheight / 2; i++) //V
		//	memcpy(datas[2] + videowidth / 2 * i, frame->data[2] + frame->linesize[2] * i, videowidth / 2);

	//}
		char* rgb = new char[videowidth*videoheight * 3];
	YUV420_2_RGB(datas[0], datas[1], datas[2], (unsigned char*)rgb, videowidth, videoheight);
	
	QImage image((uchar*)rgb, videowidth, videoheight, QImage::Format_RGB888);
	QImage imgs = image.rgbSwapped();

	this->updateImage(imgs);

	mutex.unlock();
	delete datas[0];
	delete datas[1];
	delete datas[2];
	//delete datas;
	delete[] rgb;
	av_frame_free(&frame);
	//qDebug() << "刷新显示" << endl;
}
