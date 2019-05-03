#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include "clientthread.h"
#include <QObject>
#include <QThread>
#include <QtNetwork>

class ServerThread : public ClientThread
{
    Q_OBJECT

  public:
    explicit ServerThread(QObject* parent = 0);
    void run();

  private:
    QTcpServer* m_tcpServer;
    void        newConnect();
};
extern ServerThread *serverThread;
#endif // SERVERTHREAD_H
