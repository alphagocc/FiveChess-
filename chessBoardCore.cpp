#include "chessboardcore.h"
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#define FOR(i,j,k) for (int i=(j);i<(k);i++)
// 共享的全局变量定义
ChessBoardCore chessBoard;

ChessBoardCore::ChessBoardCore()
{
    init();
}

ChessBoardCore::~ChessBoardCore()
{

}

void ChessBoardCore::dataPrint()
{
    FOR(i,0,15){
        FOR(j,0,15)
        {
            qDebug()<<static_cast<int>(m_data[i][j]);
        }
        qDebug()<<endl;
    }
}

void ChessBoardCore::clearData()
{
    FOR(i,0,15)
        FOR(j,0,15)
        {
            m_data[i][j]=DataType::none;
        }
}

bool ChessBoardCore::searchWin(ChessBoardCore::DataType chess)
{
    FOR(i,0,11)FOR(j,0,15)
    if (m_data[i][j]==chess&&m_data[i+1][j]==chess&&m_data[i+2][j]==chess&&m_data[i+3][j]==chess&&m_data[i+4][j]==chess)
        return true;

    FOR(i,0,15)FOR(j,0,11)
    if (m_data[i][j]==chess&&m_data[i][j+1]==chess&&m_data[i][j+2]==chess&&m_data[i][j+3]==chess&&m_data[i][j+4]==chess)
        return true;

    FOR(i,0,11)FOR(j,0,11)
    if (m_data[i][j]==chess&&m_data[i+1][j+1]==chess&&m_data[i+2][j+2]==chess&&m_data[i+3][j+3]==chess&&m_data[i+4][j+4]==chess)
        return true;

    FOR(i,0,11)FOR(j,4,15)
    if (m_data[i][j]==chess&&m_data[i+1][j-1]==chess&&m_data[i+2][j-2]==chess&&m_data[i+3][j-3]==chess&&m_data[i+4][j-4]==chess)
        return true;

    return false;
}

bool ChessBoardCore::saveBoard()
{
    QString fileName= QFileDialog::getSaveFileName(nullptr,
                                           tr("Save Chess Board File"),
                                           QString("."),
                                           tr("ChessBoardFile(*.chessbrd)"));
    if (!fileName.isNull()){
        QFile file(fileName);
        if (!file.open(QFile::Text|QFile::WriteOnly))
        {qDebug()<<file.errorString()<<endl;return false;}
        file.write(QString("%1\n").arg(usedTime).toUtf8());
        QJsonObject jsonObj;
        QJsonArray jsonArr;
        FOR(i,0,15){
            QJsonArray jsonArrTemp;
            QJsonObject Temp;
            FOR(j,0,15)
            {
                QJsonObject tempObj;
                tempObj[QString("ColChess%1").arg(j)]=static_cast<int>(m_data[i][j]);
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

bool ChessBoardCore::loadBoard()
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
        usedTime=file.readLine().toInt();
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
                    m_data[i][j]=DataType::none;
                    break;
                }
                case 2:
                {
                    m_data[i][j]=DataType::black;
                    break;
                }
                case 1:
                {
                    m_data[i][j]=DataType::white;
                    break;
                }
                default:
                    break;
                }
            }
        }
        dataPrint();
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

void ChessBoardCore::init()
{
    clearData();
    m_opt=ChessBoardCore::PaintOptType::onlyChessBoard;
    m_flag=0;
    usedTime=0;
}
