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

    void printResoved(QHostInfo& i_hostinfo)
    {
        if ( i_hostinfo.error() != QHostInfo::NoError )
        {
            qDebug() << "Error resolving hostname:" << i_hostinfo.errorString();
        }
        else
        {
            qDebug() << i_hostinfo.addresses() << i_hostinfo.hostName();
        }
    }

protected slots:
    void asyncResolvedSlot(QHostInfo i_hostinfo)
    {
        qDebug() << "Completed async dns resolution request with id " << i_hostinfo.lookupId();
        printResoved( i_hostinfo );
    }

public:
    DnsResolver() {}

    void resolve(const QString& i_hostname)
    {
        QTime dnsTimeMsec;
        dnsTimeMsec.start();
        // Sync DNS resolution
        QHostInfo resolvedHostname = QHostInfo::fromName( i_hostname );
        int dnsResolveTimeMsec = dnsTimeMsec.elapsed();

        qDebug() << QString("%1 resolved in %2 msec")
                    .arg(i_hostname)
                    .arg(dnsResolveTimeMsec);

        printResoved( resolvedHostname );
    }

    void asyncResolve(const QString& i_hostname)
    {
        int requestId = QHostInfo::lookupHost(i_hostname, this, SLOT(asyncResolvedSlot(QHostInfo)));
        qDebug() << "async dns resolution request queued with id " << requestId;
    }

};

#endif // DNSRESOLVER_H
