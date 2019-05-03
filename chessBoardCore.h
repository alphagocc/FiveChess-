#ifndef CHESSBOARDCORE_H
#define CHESSBOARDCORE_H

#include <QCoreApplication>
#include <QMutex>
#include <QObject>

class ChessBoardCore : public QObject
{
    Q_OBJECT
  public:
    ChessBoardCore();
    enum class DataType : int
    {
        none  = 0x00,
        white = 0x01,
        black = 0x02
    };
    enum class PaintOptType : int
    {
        onlyChessBoard = 0x00,
        chess          = 0x01,
        blackWin       = 0x02,
        whiteWin       = 0x04
    };
    enum class PlayMode : int
    {
        single = 0x00,
        server = 0x01,
        client = 0x02
    };
    ~ChessBoardCore();

  private:
    int            m_flag;
    int64_t        m_usedTime;
    PaintOptType   m_opt;
    DataType       m_data[15][15];
    PlayMode       m_mode;
    mutable QMutex mutex;

  public:
    void     dataPrint();
    void     clearData();
    bool     searchWin(DataType chess);
    bool     saveBoard();
    bool     loadBoard();
    void     init();
    int64_t  getUsedTime() { return m_usedTime; }
    void     addUsedTime() { m_usedTime++; }
    void     setPlayMode(PlayMode m) { m_mode = m; }
    PlayMode getPlayMode() { return m_mode; }

    bool setPointData(int x, int y, DataType d)
    {
        if (x < 0 || y < 0 || x >= 15 || y >= 15)
            return false;
        else
        {
            QMutexLocker locker(&mutex);
            m_data[x][y] = d;
            emit dataChanged(x, y, d);
            return true;
        }
    }
    void setOpt(PaintOptType o)
    {
        QMutexLocker locker(&mutex);
        m_opt = o;
    }
    void setFlag(int f)
    {
        QMutexLocker locker(&mutex);
        m_flag = f;
    }
    PaintOptType getPaintOpt()
    {
        QMutexLocker locker(&mutex);
        return m_opt;
    }
    int getFlag()
    {
        QMutexLocker locker(&mutex);
        return m_flag;
    }
    DataType getPointData(int x, int y)
    {
        QMutexLocker locker(&mutex);
        if (x < 0 || y < 0 || x >= 15 || y >= 15)
            throw std::out_of_range("Out Of Range");
        return m_data[x][y];
    }
  signals:
    void dataChanged(int x, int y, DataType d);
};
extern ChessBoardCore chessBoard;
#endif // CHESSBOARDCORE_H
