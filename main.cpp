#include <QCoreApplication>

#include "udpdatasender.h"
#include "udpdatareceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString targetIpAddress("127.0.0.1");
    quint16 targetUdpPort = 5432;

#if (0)
    UdpDataSender theUdpDatagramSender(targetIpAddress, targetUdpPort);
    /*
     *  nc -u -l 5432
     */
    theUdpDatagramSender.sendingDatagrams(10);
#endif

    UdpDataReceiver theUdpDataReceiver("127.0.0.1", 5432);
    theUdpDataReceiver.start();

    return a.exec();
}
