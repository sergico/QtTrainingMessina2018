#include <QCoreApplication>

#include "udpdatasender.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString targetIpAddress("127.0.0.1");
    quint16 targetUdpPort = 5432;

    UdpDataSender theUdpDatagramSender(targetIpAddress, targetUdpPort);
    /*
     *  nc -u -l 5432
     */
    theUdpDatagramSender.sendingDatagrams(10);

    return a.exec();
}
