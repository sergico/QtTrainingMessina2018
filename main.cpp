#include <QCoreApplication>

#include "sslserverwrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    /*
     * openssl s_client -connect 127.0.0.1:10022
     */
    SslServerWrapper TheSslServer;

    return a.exec();
}
