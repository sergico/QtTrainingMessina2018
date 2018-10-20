#include <QCoreApplication>

#include <dnsresolver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DnsResolver theResolver;

    // valid host name
    theResolver.resolve("www.netresults.it");

    qDebug() << "";

    // invalid hostname
    theResolver.resolve("www.nteresults.it");

    // reverse lookup
    theResolver.resolve("81.31.147.144");


    return a.exec();
}
