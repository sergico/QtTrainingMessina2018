#include <QCoreApplication>

#include <dnsresolver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DnsResolver theResolver;

    // valid host name
    theResolver.asyncResolve("www.netresults.it");

    // invalid hostname
    theResolver.asyncResolve("www.nteresults.it");

    // reverse lookup
    theResolver.asyncResolve("81.31.147.144");

    return a.exec();
}
