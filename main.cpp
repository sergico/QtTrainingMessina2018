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

    return a.exec();
}
