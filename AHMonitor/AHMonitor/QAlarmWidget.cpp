#include "QAlarmWidget.h"


#include <QMessageBox>
#pragma execution_character_set("utf-8")
QAlarmWidget::QAlarmWidget(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout* vLayout = new QVBoxLayout;

	pTableWidget_ = new QTableWidget(this);
	pTableWidget_->setColumnCount(2); //��������
	pTableWidget_->setColumnWidth(0, 160);  //0 �����п�
	pTableWidget_->setColumnWidth(1, 160); //1 �����п�
	QStringList header;
	header << "ID��" << "��װλ��";
	pTableWidget_->setHorizontalHeaderLabels(header);

	QGridLayout* gLayout = new QGridLayout;
	QHBoxLayout* hlayout = new QHBoxLayout;
	QLabel* alarmtitle = new QLabel;
	//alarmtitle->setMaximumWidth(20);
	alarmtitle->setWordWrap(true);
	alarmtitle->setAlignment(Qt::AlignCenter);
	QString s = "�������";
	alarmtitle->setText(s.split("", QString::SkipEmptyParts).join("\n"));

	gLayout->addWidget(alarmtitle,1,0,2,1);

	gLayout->addWidget(new QLabel("1"), 0, 1);
	gLayout->addWidget(new QLabel("2"), 0, 2);
	gLayout->addWidget(new QLabel("3"), 0, 3);
	gLayout->addWidget(new QLabel("4"), 0, 4);

	QList<QString> btns;
	btns << "ͨ" << "ͨ" << "ͨ" << "ͨ" << "��" << "��" << "��" << "��";
	QList<QString> btnObjects;
	btnObjects << "t1" << "t2" << "t3" << "t4" << "d1" << "d2" << "d3" << "d4";
	//ѭ����Ӷ�����ť
	for (int i = 0; i < btns.count(); i++) {
		QPushButton *btn = new QPushButton;
		//�󶨰�ť�����¼�,���������ź�֪ͨ
		connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
		//���ñ�ʶ,��������ť
		btn->setObjectName(btnObjects.at(i));
		//������������
		btn->setText(btns.at(i));
		//���ù̶����
		btn->setFixedWidth(70);
		//���ù̶����
		btn->setFixedHeight(25);
		//���ý������Ϊ�޽���,���ⵥ���󽹵��ܵ���ť��
		btn->setFocusPolicy(Qt::NoFocus);

		if (i < 4)
		{
			gLayout->addWidget(btn, 1, i+1);
		}
		else
		{
			gLayout->addWidget(btn, 2, i - 3);
		}

		//btnList.push_back(btn);
	}
	//hlayout->addLayout(gLayout);
	vLayout->addWidget(pTableWidget_);
	vLayout->addLayout(gLayout);

	this->setLayout(vLayout);
}


QAlarmWidget::~QAlarmWidget()
{
}

void QAlarmWidget::btnClicked()
{
	QPushButton *btn = (QPushButton *)sender();

	QMessageBox::information(NULL, "Error", btn->objectName(),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}