#include "serverthread.h"
#include "chessboardcore.h"
#include "networksettings.h"
#include <QDebug>

ServerThread* serverThread;

ServerThread::ServerThread(QObject* parent) : ClientThread(parent) {}

void ServerThread::run()
{
    m_tcpServer = new QTcpServer();
    connect(m_tcpServer, &QTcpServer::newConnection, this, &ServerThread::newConnect);
    m_tcpServer->listen(QHostAddress::Any, networkSettings["port"].toInt());
    qDebug() << networkSettings["port"].toInt();
}

void ServerThread::newConnect()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    tcpSocketInit();
}
