#include "FiveChess.h"
#include "chessBoardCore.h"
#include <QApplication>
#include "chessboardgui.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTranslator tsor;
	tsor.load(":/lang/zh_CN.qm");
	a.installTranslator(&tsor);

    FiveChess w;
    chessBoardCore data;
	w.setTranslator(&tsor);
    w.setData(&data);
    w.show();

    return a.exec();
}
