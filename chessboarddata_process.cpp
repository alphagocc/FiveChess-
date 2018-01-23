#include "chessboarddata_process.h"
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
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

bool chessBoardData_Process::saveBoard()
{
    QString fileName= QFileDialog::getSaveFileName(nullptr,
                                           tr("Save Chess Board File"),
                                           QString("."),
                                           tr("ChessBoardFile(*.chessbrd)"));
    if (!fileName.isNull()){
        QFile file(fileName);
        if (!file.open(QFile::Text|QFile::WriteOnly))
        {qDebug()<<file.errorString()<<endl;return false;}
        QJsonObject jsonObj;
        QJsonArray jsonArr;
        FOR(i,0,15){
            QJsonArray jsonArrTemp;
            QJsonObject Temp;
            FOR(j,0,15)
            {
                QJsonObject tempObj;
                tempObj[QString("ColChess%1").arg(j)]=data[i][j];
                jsonArrTemp.append(tempObj);
            }
            Temp[QString("RowChess%1").arg(i)]=jsonArrTemp;
            jsonArr.append(Temp);
        }
            jsonObj["ChessBoard"]=jsonArr;
            QJsonDocument jsonDoc(jsonObj);
            file.write(jsonDoc.toJson());
            file.close();
    }
    qDebug()<<fileName<<endl;
    return true;
}

bool chessBoardData_Process::loadBoard()
{
    QString filename = QFileDialog::getOpenFileName(nullptr,
                                                    tr("Open Chess Board File"),
                                                    QString("."),
                                                    tr("ChessBoardFile(*.chessbrd)"));
    if (!filename.isNull())
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug()<<file.errorString()<<endl;
            return false;
        }
        QJsonDocument jsonDoc(QJsonDocument::fromJson(file.readAll()));
        QJsonObject jsonObj=jsonDoc.object();
        QJsonArray jsonArr=jsonObj["ChessBoard"].toArray();
        FOR(i,0,15){
            QJsonObject Temp=jsonArr[i].toObject();
            QJsonArray jsonArrTemp=Temp[QString("RowChess%1").arg(i)].toArray();
            FOR(j,0,15)
            {
                QJsonObject tempObj=jsonArrTemp[j].toObject();
                int tempData=tempObj[QString("ColChess%1").arg(j)].toInt();
                switch (tempData) {
                case 0:
                {
                    data[i][j]=none;
                    break;
                }
                case 2:
                {
                    data[i][j]=black;
                    break;
                }
                case 1:
                {
                    data[i][j]=white;
                    break;
                }
                default:
                    break;
                }
            }
        }
        dataPrint();
        file.close();
    }
    return true;
}
