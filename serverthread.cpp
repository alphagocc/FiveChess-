#include "serverthread.h"
#include <QDebug>

serverThread::serverThread(QObject *parent):
    QThread(parent)
{
	
}

void serverThread::run()
{
	m_tcpServer = new QTcpServer();
	m_tcpServer->listen(QHostAddress::Any, 23333);
	connect(m_tcpServer,
		&QTcpServer::newConnection,
		this,
        &serverThread::readMessage);
}

void serverThread::newConnect()
{
	m_tcpSocket = m_tcpServer->nextPendingConnection();
	connect(m_tcpSocket,
		&QTcpSocket::readyRead,
		this,
        &serverThread::readMessage);
}

QByteArray serverThread::readMessage()
{
	QByteArray msg = m_tcpSocket->readAll();
	qDebug() << msg;
	return msg;
}

void serverThread::sendMessage(QByteArray &msg)
{
	qDebug() << msg;
	m_tcpSocket->write(msg);
}	

