#ifndef DNSRESOLVER_H
#define DNSRESOLVER_H

#include <QString>
#include <QDebug>
#include <QHostInfo>
#include <QTime>
#include <QObject>

class DnsResolver : public QObject
{
    Q_OBJECT

protected slots:
    void asyncResolvedSlot()
    {

    }

public:
    DnsResolver() {}

    bool resolve(const QString& i_hostname)
    {
        QTime dnsTimeMsec;
        dnsTimeMsec.start();
        // Sync DNS resolution
        QHostInfo resolvedHostname = QHostInfo::fromName( i_hostname );
        int dnsResolveTimeMsec = dnsTimeMsec.elapsed();

        qDebug() << QString("%1 resolved in %2 msec")
                    .arg(i_hostname)
                    .arg(dnsResolveTimeMsec);

        if ( resolvedHostname.error() != QHostInfo::NoError )
        {
            qDebug() << "Error resolving hostname:" << resolvedHostname.errorString();
            return false;
        }
        else
        {
            qDebug() << resolvedHostname.addresses() << resolvedHostname.hostName();
            return true;
        }
    }

    void asyncResolve(const QString& i_hostname)
    {

    }

};

#endif // DNSRESOLVER_H
