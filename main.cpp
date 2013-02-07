#include <qapplication.h>
#include "robotdialog.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	RobotDialog dialog;
	dialog.show();
	return a.exec();

}
