#include <QCoreApplication>

#include "tcpreceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    quint16 theServerPort = 5432;
    TcpReceiver theTcpReceiver(theServerPort);

    /*
     * nc -l 127.0.0.1 5432
     */
    theTcpReceiver.startServer();

    return a.exec();
}
