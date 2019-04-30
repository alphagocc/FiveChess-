#include "networkthread.h"
/*#include <QFile>
#include <QMessageBox>
networkThread::networkThread(QObject *parent):
    QThread(parent)
{

}

void networkThread::run()
{
    QFile *file=new QFile(QString("conf.conf"));
    QString hostName;
    int port;
    if (!file->open(QFile::ReadOnly|QFile::Text))
    {
       QByteArray confData(file->readLine());
       hostName=confData;
       confData=file->readLine();
       port=confData.toInt();
       file->close();
       manager->connectToHost(hostName,port);
    }else
    {
        QMessageBox::critical(this,
                             tr("Error!"),
                             tr("The Configuration File Can't Read\n"
                                "Please check and try again."),
                             QMessageBox::Ok,
                             QMessageBox::Cancel);
    }

}
*/
