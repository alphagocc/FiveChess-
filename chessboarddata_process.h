#ifndef CHESSBOARDDATA_PROCESS_H
#define CHESSBOARDDATA_PROCESS_H

#include <QObject>
#include <QCoreApplication>

class chessBoardData_Process
{
    Q_DECLARE_TR_FUNCTIONS(chessBoardData_Process)
public:
    chessBoardData_Process();
    enum dataType{
        none  = 0x00000000,
        white = 0x00000001,
        black = 0x00000002
    };
    dataType data[15][15];
    void dataPrint();
    void clear();
    bool searchWin(dataType chess);
    bool saveBoard();
    bool loadBoard();
};

#endif // CHESSBOARDDATA_PROCESS_H
