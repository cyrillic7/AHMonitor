#include "stdafx.h"
#include "H264Decode2.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
};


H264Decode2::H264Decode2()
{
}


H264Decode2::~H264Decode2()
{
}


int H264Decode2::DecodeH264()
{
	AVFormatContext		*pFormatCtx = NULL;
	AVCodecContext		*pCodecCtx = NULL;
	AVCodec				*pCodec = NULL;
	AVFrame				*pFrame = NULL, *pFrameYUV = NULL;
	unsigned char		*out_buffer = NULL;
	AVPacket			packet;
	struct SwsContext	*img_convert_ctx = NULL;
	int					got_picture;
	int					videoIndex;
	int					frame_cnt = 1;

	char filepath[] = "Titanic.ts";
	//char filepath[] = "Forrest_Gump_IMAX.mp4";

	FILE *fp_yuv = fopen("film.yuv", "wb+");
	FILE *fp_h264 = fopen("film.h264", "wb+");
	if (fp_yuv == NULL || fp_h264 == NULL)
	{
		printf("FILE open error");
		return -1;
	}

	av_register_all();

	if (avformat_open_input(&pFormatCtx, filepath, NULL, NULL) != 0) {
		printf("Couldn't open an input stream.\n");
		return -1;
	}
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		printf("Couldn't find stream information.\n");
		return -1;
	}
	videoIndex = -1;
	for (int i = 0; i < pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoIndex = i;
			break;
		}

	if (videoIndex == -1) {
		printf("Couldn't find a video stream.\n");
		return -1;
	}

	pCodecCtx = pFormatCtx->streams[videoIndex]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) {
		printf("Codec not found.\n");
		return -1;
	}
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec.\n");
		return -1;
	}



	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();
	if (pFrame == NULL || pFrameYUV == NULL)
	{
		printf("memory allocation error\n");
		return -1;
	}

	/**
	*  RGB--------->AV_PIX_FMT_RGB24
	*  YUV420P----->AV_PIX_FMT_YUV420P
	*  UYVY422----->AV_PIX_FMT_UYVY422
	*  YUV422P----->AV_PIX_FMT_YUV422P
	*/
	out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1));
	av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, out_buffer,
		AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);




	/*
	//针对H.264码流
	unsigned char *dummy = NULL;   //输入的指针
	int dummy_len;
	const char nal_start[] = { 0, 0, 0, 1 };
	AVBitStreamFilterContext* bsfc = av_bitstream_filter_init("h264_mp4toannexb");
	av_bitstream_filter_filter(bsfc, pCodecCtx, NULL, &dummy, &dummy_len, NULL, 0, 0);
	fwrite(pCodecCtx->extradata, pCodecCtx->extradata_size, 1, fp_h264);
	av_bitstream_filter_close(bsfc);
	free(dummy);
	*/
	while (av_read_frame(pFormatCtx, &packet) >= 0)
	{
		if (packet.stream_index == videoIndex)
		{
			//输出出h.264数据
			fwrite(packet.data, 1, packet.size, fp_h264);

			//针对H.264码流
			//fwrite(nal_start, 4, 1, fp_h264);
			//fwrite(packet.data + 4, packet.size - 4, 1, fp_h264);

			if (avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet) < 0)
			{
				printf("Decode Error.\n");
				return -1;
			}
			if (got_picture)
			{
				sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
					pFrameYUV->data, pFrameYUV->linesize);

				//输出出YUV数据
				int y_size = pCodecCtx->width * pCodecCtx->height;
				fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv);		//Y 
				fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);	//U
				fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);	//V

																	/**
																	*  输出RGB数据
																	*  fwrite(pFrameYUV->data[0], (pCodecCtx->width) * (pCodecCtx->height) * 3, 1, fp);
																	*  输出UYVY数据
																	*  fwrite(pFrameYUV->data[0], (pCodecCtx->width) * (pCodecCtx->height), 2, fp);
																	*/

				printf("Succeed to decode %d frame!\n", frame_cnt);
				frame_cnt++;
			}
		}
		av_free_packet(&packet);
	}

	//flush decoder
	//FIX: Flush Frames remained in Codec
	while (true)
	{
		if (avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet) < 0)
		{
			break;
		}
		if (!got_picture)
		{
			break;
		}

		sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
			pFrameYUV->data, pFrameYUV->linesize);

		int y_size = pCodecCtx->width * pCodecCtx->height;
		fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv);		//Y 
		fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);	//U
		fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);	//V

		printf("Flush Decoder: Succeed to decode %d frame!\n", frame_cnt);
		frame_cnt++;
	}


	fclose(fp_yuv);
	fclose(fp_h264);
	sws_freeContext(img_convert_ctx);
	av_free(out_buffer);
	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);

	return 0;
}

