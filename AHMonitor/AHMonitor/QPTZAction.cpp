#include "QPTZAction.h"

#include <QMessageBox>
#pragma execution_character_set("utf-8")
QPTZAction::QPTZAction(QWidget *parent) : QWidget(parent)
{
	QGridLayout* gLayout = new QGridLayout;
	pScanlabel_ = new QLabel("ɨ��", this);
	pCruiselabel_ = new QLabel("Ѳ��", this);
	pInfraredlabel_ = new QLabel("����", this);
	pWiperlabel_ = new QLabel("��ˢ", this);

	pScanlabel_->setWordWrap(true);
	pScanlabel_->setAlignment(Qt::AlignCenter);
	pCruiselabel_->setWordWrap(true);
	pCruiselabel_->setAlignment(Qt::AlignCenter);
	pInfraredlabel_->setWordWrap(true);
	pInfraredlabel_->setAlignment(Qt::AlignCenter);
	pWiperlabel_->setWordWrap(true);
	pWiperlabel_->setAlignment(Qt::AlignCenter);

	//QHBoxLayout* hLayout = new QHBoxLayout;
	gLayout->addWidget(pScanlabel_,0,0);
	gLayout->addWidget(pCruiselabel_,0,1);
	gLayout->addWidget(pInfraredlabel_,0,2);
	gLayout->addWidget(pWiperlabel_,0,3);

	QList<QString> btns;
	btns << "��" << "��" << "��" << "��" << "ͣ" << "ͣ" << "ͣ" << "ͣ";
	QList<QString> btnObjects;
	btnObjects << "ss" << "xs" << "hs" << "ys" << "sp" << "xp" << "hp" << "yp";
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
		btn->setFixedWidth(30);
		//���ù̶����
		btn->setFixedHeight(30);
		//���ý������Ϊ�޽���,���ⵥ���󽹵��ܵ���ť��
		btn->setFocusPolicy(Qt::NoFocus);

		if (i < 4)
		{
			gLayout->addWidget(btn, 1, i);
		}
		else
		{
			gLayout->addWidget(btn, 2, i - 4);
		}

		//btnList.push_back(btn);
	}

	//gLayout->addLayout(hLayout, 0, 0);
	
	this->setLayout(gLayout);
}


QPTZAction::~QPTZAction()
{
}

void QPTZAction::btnClicked()
{
	QPushButton *btn = (QPushButton *)sender();

	QMessageBox::information(NULL, "Error", btn->objectName(),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}