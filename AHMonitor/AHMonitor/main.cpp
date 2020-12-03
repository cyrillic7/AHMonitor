#include "AHMonitor.h"
#include "QLogonDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AHMonitor w;
	/*w.show();*/

	/*QLogonDialog logonDlg;*/
	if (w.pLogonDialog_->exec() == QDialog::Accepted)
	{
		w.showMaximized();
		w.updateTreeWidget();
	}
	else
	{
		return -1;
	}

	return a.exec();
}
