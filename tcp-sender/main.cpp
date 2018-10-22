#include <QCoreApplication>

#include "tcpsender.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QString targetAddress("127.0.0.1");
    quint16 targetPort = 5432;

    TcpSender theSender( targetAddress, targetPort );
    theSender.connecteMe();

    QString dataToSend;
    dataToSend = "This is the stream of data we want to send...";

    /*
     *   nc -l 127.0.0.1 5432
     */
    theSender.sendSomeData( dataToSend );

    return a.exec();
}
