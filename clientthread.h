#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QtNetwork>
class ClientThread : public QThread
{
    Q_OBJECT

  public:
    explicit ClientThread(QObject* parent = nullptr);
    void run();
    void readMessage();
    void sendMessage(QByteArray& msg);

  protected:
    QTcpSocket* m_tcpSocket;
    void        tcpSocketInit();
};
extern ClientThread* clientThread;
#endif CLIENTTHREAD_H
