#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QObject>
#include <QThread>
#include <QtNetwork>

class serverThread : public QThread
{
	Q_OBJECT

public:
    explicit serverThread(QObject * parent=0);
    void run();
	QByteArray readMessage();
	void sendMessage(QByteArray & msg);
private :
    QTcpServer *m_tcpServer;
    QTcpSocket *m_tcpSocket;
	void newConnect();
};

#endif // SERVERTHREAD_H

