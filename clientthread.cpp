#include "clientthread.h"
#include "chessboardcore.h"
#include "networksettings.h"
#include <QDebug>

ClientThread* clientThread;

ClientThread::ClientThread(QObject* parent) : QThread(parent) {}

void ClientThread::run()
{
    m_tcpSocket = new QTcpSocket();
    m_tcpSocket->abort();
    m_tcpSocket->connectToHost(networkSettings["host"].toString(),
                               networkSettings["port"].toInt());
    qDebug() << networkSettings["host"].toString()
             << networkSettings["port"].toInt();
    tcpSocketInit();
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
    chessBoard.setAChess(x, y, d);
}

void ClientThread::sendMessage(QByteArray& msg)
{
    qDebug() << msg;
    m_tcpSocket->write(msg);
}

void ClientThread::tcpSocketInit()
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
