#ifndef IVIDEOCALL
#define IVIDEOCALL
struct AVFrame;
class IVideoCall//ÏÔÊ¾»Øµ÷
{
public:
	virtual void Init(int width, int height) = 0;
	virtual void Repaint(AVFrame *frame) = 0;
};

#endif

