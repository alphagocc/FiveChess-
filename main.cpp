#include "fivechess.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); //High DPI supported
#endif

    QApplication a(argc, argv);
	QTranslator tsor;
	tsor.load(":/lang/zh_CN.qm");
	a.installTranslator(&tsor);

    FiveChess w;
	w.setTranslator(&tsor);
    w.show();

    return a.exec();
}
