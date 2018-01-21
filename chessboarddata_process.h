#ifndef CHESSBOARDDATA_PROCESS_H
#define CHESSBOARDDATA_PROCESS_H

#include <QObject>

class chessBoardData_Process
{
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
};

#endif // CHESSBOARDDATA_PROCESS_H
