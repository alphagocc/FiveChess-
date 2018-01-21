#include "FiveChess.h"
#include "chessboarddata_process.h"
#include <QApplication>
#include "chessboardgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FiveChess w;
    chessBoardData_Process data=chessBoardData_Process();
    w.setData(data);
    w.show();

    return a.exec();
}
