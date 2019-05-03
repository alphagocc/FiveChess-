#include "chessboardcore.h"
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <cctype>
#define FOR(i, j, k) for (int i = (j); i < (k); i++)
// 共享的全局变量定义
ChessBoardCore chessBoard;

ChessBoardCore::ChessBoardCore() { init(); }

ChessBoardCore::~ChessBoardCore() {}

void ChessBoardCore::dataPrint()
{
    FOR(i, 0, 15)
    {
        FOR(j, 0, 15) { qDebug("%d", static_cast<int>(m_data[i][j])); }
        qDebug() << endl;
    }
}

void ChessBoardCore::clearData()
{
    FOR(i, 0, 15)
    FOR(j, 0, 15) { m_data[i][j] = DataType::none; }
}

bool ChessBoardCore::searchWin(ChessBoardCore::DataType chess)
{
    FOR(i, 0, 11)
    FOR(j, 0, 15)
    if (m_data[i][j] == chess && m_data[i + 1][j] == chess && m_data[i + 2][j] == chess &&
        m_data[i + 3][j] == chess && m_data[i + 4][j] == chess) return true;

    FOR(i, 0, 15)
    FOR(j, 0, 11)
    if (m_data[i][j] == chess && m_data[i][j + 1] == chess && m_data[i][j + 2] == chess &&
        m_data[i][j + 3] == chess && m_data[i][j + 4] == chess) return true;

    FOR(i, 0, 11)
    FOR(j, 0, 11)
    if (m_data[i][j] == chess && m_data[i + 1][j + 1] == chess &&
        m_data[i + 2][j + 2] == chess && m_data[i + 3][j + 3] == chess &&
        m_data[i + 4][j + 4] == chess) return true;

    FOR(i, 0, 11)
    FOR(j, 4, 15)
    if (m_data[i][j] == chess && m_data[i + 1][j - 1] == chess &&
        m_data[i + 2][j - 2] == chess && m_data[i + 3][j - 3] == chess &&
        m_data[i + 4][j - 4] == chess) return true;

    return false;
}

bool ChessBoardCore::saveBoard()
{
    QString fileName =
        QFileDialog::getSaveFileName(nullptr, tr("Save Chess Board File"), QString("."),
                                     tr("ChessBoardFile(*.chessbrd)"));
    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QFile::Text | QFile::WriteOnly))
        {
            qDebug() << file.errorString() << endl;
            return false;
        }
        file.write(QString("%1\n").arg(m_usedTime).toUtf8());
        file.write(QString("%1\n").arg(m_flag).toUtf8());
        FOR(i, 0, 15)
        {
            FOR(j, 0, 15)
            {
                file.write(QString("%1").arg(static_cast<int>(m_data[i][j])).toUtf8());
            }
        }
        file.close();
    }
    qDebug() << fileName << endl;
    return true;
}

bool ChessBoardCore::loadBoard()
{
    QString filename =
        QFileDialog::getOpenFileName(nullptr, tr("Open Chess Board File"), QString("."),
                                     tr("ChessBoardFile(*.chessbrd)"));
    if (!filename.isNull())
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << file.errorString() << endl;
            return false;
        }
        m_usedTime = file.readLine().toInt();
        m_flag     = file.readLine().toInt();
        qDebug() << m_usedTime;
        qDebug() << m_flag;
        QString tempStr;
        tempStr = file.readLine();
        FOR(i, 0, 15)
        {
            FOR(j, 0, 15)
            {
                int tempData = tempStr[j].toLatin1();
                if (!std::isdigit(tempData))
                {
                    file.close();
                    init();
                    return false;
                }
                m_data[i][j] = static_cast<DataType>(tempData - 48);
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
    m_opt      = ChessBoardCore::PaintOptType::onlyChessBoard;
    m_flag     = 0;
    m_usedTime = 0;
}

bool ChessBoardCore::setPointData(int x, int y, DataType d, int s = 1)
{
    if (x < 0 || y < 0 || x >= 15 || y >= 15)
        return false;
    else
    {
        QMutexLocker locker(&mutex);
        m_data[x][y] = d;
        emit needRepaint();
        if (s == 1) emit dataChanged(x, y, d);
        return true;
    }
}

void ChessBoardCore::setAChess(int x, int y, ChessBoardCore::DataType d)
{
    if (chessBoard.getPointData(x, y) == ChessBoardCore::DataType::none)
    {
        chessBoard.setOpt(ChessBoardCore::PaintOptType::chess);
        chessBoard.setPointData(x, y, d, 1);
        if (chessBoard.searchWin(d))
        {
            if (m_flag) { chessBoard.setOpt(ChessBoardCore::PaintOptType::whiteWin); }
            else
            {
                chessBoard.setOpt(ChessBoardCore::PaintOptType::blackWin);
            }
        }
        m_flag ^= 1;
    }
}
