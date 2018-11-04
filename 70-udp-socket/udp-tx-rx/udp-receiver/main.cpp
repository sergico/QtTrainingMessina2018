#include <QCoreApplication>

#include "udpdatareceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString targetIpAddress("127.0.0.1");
    quint16 targetUdpPort = 5432;

    /*
     *  nc -u -l 127.0.0.1 5432
     */
    UdpDataReceiver theUdpDataReceiver(targetIpAddress, targetUdpPort);
    theUdpDataReceiver.start();

    return a.exec();
}
