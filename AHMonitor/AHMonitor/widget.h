#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class titleWidget;
class myPushButton;
class QLabel;
class QTimer;

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void showAsQQ();//在右下角显示

public slots:
    void setMsg(QString title,QString content,QString url);
private slots:
    void openWeb();

    void myMove();
    void myStay();
    void myClose();
    
private:
    titleWidget *titleW;
    QLabel *content;
    myPushButton *btnLook;
    QString url;

    QPoint normalPoint;//完全显示时左上角位置
    QRect deskRect;

    QTimer *timerShow;//平滑显示的定时器
    QTimer *timerStay;//停留时间的定时器 10s
    QTimer *timerClose;//关闭淡出的定时器

	int beginY;
	int timeCount;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // WIDGET_H
