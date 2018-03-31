#ifndef CHESSBOARDDATA_PROCESS_H
#define CHESSBOARDDATA_PROCESS_H

#include <QObject>
#include <QCoreApplication>

class chessBoardCore
{
private :
    Q_DECLARE_TR_FUNCTIONS(chessBoardCore)
public:
    chessBoardCore();
    enum dataType{
        none  = 0x00000000,
        white = 0x00000001,
        black = 0x00000002
    };
    enum paintOptType{
        onlyChessBoard = 0x00000000,
        chess          = 0x00000001,
        blackWin       = 0x00000002,
        whiteWin       = 0x00000004
    };
private :
    int m_flag;
    paintOptType m_opt;
    dataType m_data[15][15];
public :
    void dataPrint();
    void clearData();
    bool searchWin(dataType chess);
    bool saveBoard();
    bool loadBoard();
    void init();
    bool setPointData(int x,int y,dataType d)
    {if(x<0||y<0||x>=15||y>=15)
            return false;
    else m_data[x][y]=d;
    return true;}
    void setOpt(paintOptType o){m_opt=o;}
    void setFlag(int f){m_flag=f;}
    dataType getPointData(int x,int y){return m_data[x][y];}
    paintOptType getPaintOpt(){return m_opt;}
    int getFlag(){return m_flag;}
};

#endif // CHESSBOARDDATA_PROCESS_H
