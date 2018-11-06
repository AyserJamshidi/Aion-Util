#include "AionUtil.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	// Pre-creation settings
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication a(argc, argv);
	QApplication::setStyle("Fusion");

	AionUtil w;
	w.show();
	return a.exec();
}
