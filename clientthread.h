#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QtNetwork>
class clientThread :
	public QThread
{
	Q_OBJECT

public:
	explicit clientThread(QObject * parent = nullptr);
	void run();
	QByteArray readMessage();
	void sendMessage(QByteArray & msg);
private :
	QTcpSocket *m_tcpSocket;
};

#endif CLIENTTHREAD_H
