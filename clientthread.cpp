#include "clientthread.h"
#include <QDebug>

clientThread::clientThread(QObject *parent):
	QThread(parent)
{

}

void clientThread::run()
{
	m_tcpSocket = new QTcpSocket();
	m_tcpSocket->abort();
	m_tcpSocket->connectToHost("127.0.0.1", 23333);
	connect(m_tcpSocket,
		&QTcpSocket::readyRead,
		this,
        &clientThread::readMessage);
}

QByteArray clientThread::readMessage()
{
	QByteArray msg = m_tcpSocket->readAll();
	qDebug() << msg;
	return msg;
}

void clientThread::sendMessage(QByteArray & msg)
{
	qDebug() << msg;
	m_tcpSocket->write(msg);
}
