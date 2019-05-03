#include "clientthread.h"
#include "chessboardcore.h"
#include <QDebug>

ClientThread* clientThread;

ClientThread::ClientThread(QObject* parent) : QThread(parent) { init(); }

void ClientThread::run()
{
    m_tcpSocket = new QTcpSocket();
    m_tcpSocket->abort();
    m_tcpSocket->connectToHost("127.0.0.1", 23333);
}

void ClientThread::readMessage()
{
    QByteArray msg = m_tcpSocket->readAll();
    qDebug() << msg;
    if (msg.size() < 3) throw std::out_of_range("Too short");
    int                      x = msg[0];
    int                      y = msg[1];
    ChessBoardCore::DataType d =
        static_cast<ChessBoardCore::DataType>(static_cast<int>(msg[2]));
    if (!chessBoard.setPointData(x, y, d, 0)) { throw std::exception("Data Error"); }
}

void ClientThread::sendMessage(QByteArray& msg)
{
    qDebug() << msg;
    m_tcpSocket->write(msg);
}

void ClientThread::init()
{
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ClientThread::readMessage);
    connect(&chessBoard, &ChessBoardCore::dataChanged, this,
            [&](const int x, const int y, const ChessBoardCore::DataType d) {
                QByteArray ba;
                ba.append(x);
                ba.append(y);
                ba.append(static_cast<int>(d));
                sendMessage(ba);
            });
}
