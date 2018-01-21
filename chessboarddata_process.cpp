#include "chessboarddata_process.h"
#include <QDebug>
#define FOR(i,j,k) for (int i=(j);i<(k);i++)

chessBoardData_Process::chessBoardData_Process()
{
    clear();
    qDebug()<<"none:"<<none<<"black:"<<black<<"white:"<<white<<endl;
}

void chessBoardData_Process::dataPrint()
{
    FOR(i,0,15){
        FOR(j,0,15)
        {
            qDebug()<<data[i][j];
        }
        qDebug()<<endl;
    }
}

void chessBoardData_Process::clear()
{
    FOR(i,0,15)
        FOR(j,0,15)
        {
            data[i][j]=none;
        }
}

bool chessBoardData_Process::searchWin(chessBoardData_Process::dataType chess)
{
    FOR(i,0,11)FOR(j,0,15)
    if (data[i][j]==chess&&data[i+1][j]==chess&&data[i+2][j]==chess&&data[i+3][j]==chess&&data[i+4][j]==chess)
        return true;

    FOR(i,0,15)FOR(j,0,11)
    if (data[i][j]==chess&&data[i][j+1]==chess&&data[i][j+2]==chess&&data[i][j+3]==chess&&data[i][j+4]==chess)
        return true;

    FOR(i,0,11)FOR(j,0,11)
    if (data[i][j]==chess&&data[i+1][j+1]==chess&&data[i+2][j+2]==chess&&data[i+3][j+3]==chess&&data[i+4][j+4]==chess)
        return true;

    FOR(i,0,11)FOR(j,4,15)
    if (data[i][j]==chess&&data[i+1][j-1]==chess&&data[i+2][j-2]==chess&&data[i+3][j-3]==chess&&data[i+4][j-4]==chess)
        return true;

    return false;
}
