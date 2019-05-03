#include "serverthread.h"
#include "chessboardcore.h"
#include <QDebug>

ServerThread* serverThread;

ServerThread::ServerThread(QObject* parent) : ClientThread(parent)
{
    connect(m_tcpServer, &QTcpServer::newConnection, this, &ServerThread::readMessage);
    init();
}

void ServerThread::run()
{
    m_tcpServer = new QTcpServer();
    m_tcpServer->listen(QHostAddress::Any, 23333);
}

void ServerThread::newConnect() { m_tcpSocket = m_tcpServer->nextPendingConnection(); }

