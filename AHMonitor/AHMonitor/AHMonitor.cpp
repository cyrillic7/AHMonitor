#include "AHMonitor.h"
#include "QLogonDialog.h"
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
extern "C"
{
#include "libavformat/avformat.h"
};
#pragma execution_character_set("utf-8")

//INT64 _h264Handle = 0;
void UIEventCallBackHandler(MP_ENG_EVENT event, int nIndex, void *pParam, void *pAppData)
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
	{
		AHMonitor* pMonitor = (AHMonitor*)pAppData;
		pMonitor->updateCamOnLine(nIndex,true);
	}
	break;
	case MP_EVENT_CAMEXIT:
	{
		AHMonitor* pMonitor = (AHMonitor*)pAppData;
		pMonitor->updateCamOnLine(nIndex, false);
	}
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
		AHMonitor* pMonitor = (AHMonitor*)pAppData;
		MP_DATA_INFO *pData = (MP_DATA_INFO *)pParam;
		if (pData->type == MP_DATA_H264)   //视频数据，也可能是h265，
		{
			//VideoWidget* pWidget = (VideoWidget*)pAppData;
			////pWidget->setVideoh264Data(pParam);

			//MP_DATA_INFO *pMPData = (MP_DATA_INFO *)pData;
			//if (pMPData->type == MP_DATA_H264)   //视频数据，也可能是h265，
			//{
			//	int videoWidth;                 //视频宽度
			//	int videoHeight;                //视频高度
			//	int nResolution = ((pMPData->nTimestamp & 0xe000) >> 13);
			//	pWidget->getVideoResolution(nResolution, &videoWidth, &videoHeight);

			//	if (_h264Handle == 0)
			//	{
			//		_h264Handle = H264_CreateHandle();
			//	}

			//	int pRet = H264_PutVideoStream(_h264Handle, (char*)pMPData->pData, pMPData->nLen);
			//	if (pRet != 0)
			//	{
			//		return;
			//	}

			//	int picWidth = videoWidth;
			//	int picHeight = videoHeight;
			//	INT32 frameSize = H264_GetVideoFrameSize_Rgb2(_h264Handle, picWidth, picHeight);
			//	if (frameSize == 0)
			//		return;

			//	char* buffer = new char[frameSize];
			//	memset(buffer, 0, sizeof(buffer));

			//	INT32 ret = H264_GetNextVideoFrame_Rgb2(_h264Handle, buffer, frameSize, picWidth, picHeight);
			//	if (ret != 0) {
			//		delete[] buffer;
			//		return;
			//	}

			//	//pMonitor->pVidoePanel_Widget_->widgets[0]->width;
			//	/*int width = pMonitor->pVidoePanel_Widget_->widgets[0]->width();
			//	int height = pMonitor->pVidoePanel_Widget_->widgets[0]->height();*/
			//	//QImage *tmpImg = new QImage((uchar *)buffer, picWidth, picHeight, 3 * picWidth, QImage::Format_RGB888);
			//	QImage* pimage = new QImage(picWidth, picHeight, QImage::Format_RGB888);
			//	int b, g, r;
			//	//设置像素
			//	for (int i = 0; i < picHeight; i++)
			//	{
			//		for (int j = 0; j < picWidth; j++)
			//		{
			//			b = (int)buffer[i];
			//			g = (int)buffer[i + 1];
			//			r = (int)buffer[i + 2];
			//			pimage->setPixel(j, i, qRgb(r, g, b));
			//		}
			//	}

			//	pWidget->updateImage(*pimage);

			//	delete pimage;
			//	delete[] buffer;
			//}
		}
		else if (pData->type == MP_DATA_G723)   //音频数据，对于新设备事实上是AMR_NB格式
		{
			//老版本的都是 AMR_NB
			//新版本的dll， 支持不同类型，
			pData->nFlag;  //是 1的话是amr， 是2是aac ， 若是0，可能playback dll是老版本，
						   //add your code here
		}
		else  if (pData->type == MP_DATA_YUV)
		{
			MP_YUV_INFO *pYUVData = (MP_YUV_INFO *)pData->pData;
			char* rgb = new char[pYUVData->nWidth*pYUVData->nHeight * sizeof(RGB32)];
			pMonitor->YUV420_2_RGB(pYUVData->pY, pYUVData->pU, pYUVData->pV,(unsigned char*)rgb, pYUVData->nWidth, pYUVData->nHeight);
			QImage* pimage = new QImage(pYUVData->nWidth, pYUVData->nHeight, QImage::Format_RGB888);
			int b, g, r;
			//设置像素
			for (int i = 0; i < pYUVData->nHeight; i++)
			{
				for (int j = 0; j < pYUVData->nWidth; j++)
				{
					b = (int)rgb[i];
					g = (int)rgb[i + 1];
					r = (int)rgb[i + 2];
					pimage->setPixel(j, i, qRgb(r, g, b));
				}
			}
			//pMonitor->RGB2Image(rgb, pYUVData->nWidth, pYUVData->nHeight, pimage);

			pMonitor->pVidoePanel_Widget_->Play(*pimage);
			delete pimage;
			delete[] rgb;
		}
	}

	break;
	}
}


AHMonitor::AHMonitor(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	pLogonDialog_ = new QLogonDialog(this);
	pLogonDialog_->move((qApp->desktop()->availableGeometry().width() - width()) / 2 + qApp->desktop()->availableGeometry().x(),
		(qApp->desktop()->availableGeometry().height() - height()) / 2 + qApp->desktop()->availableGeometry().y());


	pVidoePanel_Widget_ = new VideoPanel(this);
	pToolsSplit_ = new QToolsSplit(this);
	pToolsSplit_->setVideoPanelWidget(pVidoePanel_Widget_);

	//m_pFrameStreamManager = new FrameStreamManager;
	m_pServerManager = new ServerManager;
	m_pPlayerManager = new CPlayerManager;
	m_pPlayerManager->setPanelWidget(pVidoePanel_Widget_);

	QMainWidget = new QWidget;
	this->setCentralWidget(QMainWidget);

	pTreeWidget_ = new QServerTreeWidget(this);
	pTreeWidget_->setMaximumWidth(280);

	QGridLayout* pMainLayout = new QGridLayout;
	QVBoxLayout* pControlLayout = new QVBoxLayout;
	pControlLayout->addWidget(pTreeWidget_);
	pMainLayout->addLayout(pControlLayout, 0, 0);

	pMainLayout->addWidget(pVidoePanel_Widget_, 0, 1);

	pMainLayout->addWidget(pToolsSplit_, 0, 2);

	QMainWidget->setLayout(pMainLayout);


	//创建动作、菜单、工具栏
	createActions();
	createMenus();
	createToolBars();

	CPlaybackEngine::Initialize("{D79399DA-2F36-4f7d-846A-292C90BA9E8D}");

	if (av_register == false)
	{
		av_register_all();

		avformat_network_init();
		av_register = true;

	}
}

AHMonitor::~AHMonitor()
{
	
}

void AHMonitor::updateTreeWidget()
{
	pTreeWidget_->updateServerTreeItem();
}

void AHMonitor::updateCamOnLine(int nSession, bool bOnline)
{
	pTreeWidget_->updateCamLine(nSession, bOnline);
	pVidoePanel_Widget_->setVideoOffLine(nSession);
}

void AHMonitor::showh264toImage(unsigned char * pData, int iLen,int nResolution)
{

}

void AHMonitor::createActions()
{
	LinkAction_ = new QAction(tr("链接站点"), this);
	connect(LinkAction_, SIGNAL(triggered()), this, SLOT(onServerConnect()));

	unLinkAction_ = new QAction(tr("断开站点"), this);
	connect(unLinkAction_, SIGNAL(triggered()), this, SLOT(onServerDisConnect()));

	ExitAction_ = new QAction(tr("退出"), this);
	connect(ExitAction_, SIGNAL(triggered()), this, SLOT(close()));
}

void AHMonitor::createMenus()
{
	LinkMenu_ = menuBar()->addMenu(tr("路径"));
	LinkMenu_->addAction(LinkAction_);
	LinkMenu_->addAction(unLinkAction_);
	LinkMenu_->addAction(ExitAction_);


}

void AHMonitor::createToolBars()
{
	LinkTool_ = addToolBar("链接站点");
	LinkTool_->addAction(LinkAction_);
}

void AHMonitor::onServerConnect()
{
	if (pLogonDialog_->exec() == QDialog::Accepted)
	{
		//updateTreeWidget();
	}
}

void AHMonitor::onServerDisConnect()
{
	ServerManager* pServerMng = ServerManager::getInstance();
	for (int i = 0; i < pServerMng->getServerCount(); i++)
	{
		/*CServerNode* pServerNode = pServerMng->getServerNode(i);
		int ret = pServerNode->m_pCameraMngr->AssignPlayer(0, 32992);

		CPlaybackEngine* player1 = CPlaybackEngine::getInstance(0);
		player1 = CPlaybackEngine::getInstance(0);
		player1->SetMode(MP_MODE_SERV_PROXY);
		player1->SetCallbackFunc(UIEventCallBackHandler, pVidoePanel_Widget_->getVideoWidget());
		player1->Load();
		player1->Start();*/
	}
}

bool AHMonitor::GetVideoFrameResolution(void *pParam, int *width, int *height)
{
	MP_DATA_INFO *pData = (MP_DATA_INFO *)pParam;

	int nResolution = ((pData->nTimestamp & 0xe000) >> 13);

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

	return true;
}

void  AHMonitor::Yuv420p2Rgb32(unsigned char *pBufy, unsigned char *pBufu, unsigned char *pBufv, const  BYTE  *rgbBuffer_out, int  width, int  height)
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

			BYTE  Y = (BYTE )pBufy[indexY]; //yuvBuffer[indexY];
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


void AHMonitor::YUV420_2_RGB(unsigned char *pBufy, unsigned char *pBufu, unsigned char *pBufv, unsigned char* pRGB, int width, int height)
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

bool AHMonitor::yuv420ToRgb(unsigned char *pBufy, unsigned char *pBufu, unsigned char *pBufv,int w, int h, char *rgb)
{
	/*unsigned char *pBufy = new unsigned char[w*h];
	unsigned char *pBufu = new unsigned char[w*h / 4];
	unsigned char *pBufv = new unsigned char[w*h / 4];

	memcpy(pBufy, yuv, w*h);
	memcpy(pBufu, yuv + w*h, w*h / 4);
	memcpy(pBufv, yuv + w*h * 5 / 4, w*h / 4);*/

	for (int i = 0; i < w*h / 4; i++)
	{
		rgb[i * 3 + 2] = pBufy[i] + 1.772*(pBufu[i] - 128);  //B = Y +1.779*(U-128)
		rgb[i * 3 + 1] = pBufy[i] - 0.34413*(pBufu[i] - 128) - 0.71414*(pBufv[i] - 128);//G = Y-0.3455*(U-128)-0.7169*(V-128)
		rgb[i * 3 + 0] = pBufy[i] + 1.402*(pBufv[i] - 128);//R = Y+1.4075*(V-128)
	}
	/*free(pBufy);
	free(pBufu);
	free(pBufv);*/
	return true;
}

void AHMonitor::RGB2Image(char *srcBuf, int w, int h, QImage *pDistImage)
{
	int i;
	int r, g, b;
	QRgb *point;
	uchar *bit;
	i = 0;
	bit = (uchar *)(srcBuf);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			/* Please attion the Littile-Edian and Big-Edian,
			* The Order maybe R-G-B.
			*/
			b = (int)bit[i];
			g = (int)bit[i + 1];
			r = (int)bit[i + 2];
			point = (QRgb *)pDistImage->scanLine(y) + x;
			*point = qRgb(r, g, b);
			i += 3;
		}
	}
	return;
}

//int AHMonitor::DecodeFrame(unsigned char * framedata, int framelen,//input
//	unsigned char *outputframe, int *width, int *height, int *pixfmt)//output
//{
//	avpkt.size = framelen;
//	avpkt.data = framedata;
//	while (avpkt.size > 0)
//	{
//		if (decode_frame(codec_ctx, frame, &avpkt, 0, outputframe) < 0)
//		{
//			printf("%s decode fail\n", __func__);
//			return -1;
//		}
//	}
//	*width = codec_ctx->width;
//	*height = codec_ctx->height;
//	*pixfmt = codec_ctx->pix_fmt;
//	return 0;
//}