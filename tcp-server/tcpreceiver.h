#ifndef TCPRECEIVER_H
#define TCPRECEIVER_H

#include <QObject>
#include <QTcpServer>
#include <QString>
#include <QtDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDateTime>

class TcpReceiver : public QObject
{
    Q_OBJECT

    QTcpServer*  m_serverPtr;
    quint16 m_port;

public:
    explicit TcpReceiver(quint16 i_serverPort,
                         QObject *parent = nullptr) :
        m_port(i_serverPort)
    {
        m_serverPtr = new QTcpServer(this);

        connect ( m_serverPtr, SIGNAL(newConnection()),
                  this,        SLOT(someonesHereSlot()) );


    }

    void startServer()
    {
        bool listening = m_serverPtr->listen( QHostAddress::LocalHost, m_port );
        if ( !listening )
        {
            qCritical() << "Server is not listening! " << m_serverPtr->errorString();
            exit(1);
        }
        else
        {
            qDebug() << "The shop is open @" << m_port;
        }
    }


signals:

protected slots:
    void someonesHereSlot()
    {
        qDebug() << "Someone knocking...";
        QTcpSocket* sockPtr = m_serverPtr->nextPendingConnection();
        qDebug() << QString("Hello %1:%2, here's your token")
                    .arg( sockPtr->peerAddress().toString() )
                    .arg( sockPtr->peerPort() );

        qint64 ts = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
        QString token = QString::number(ts);
        sockPtr->write(token.toUtf8());
        sockPtr->close();
    }
};

#endif // TCPRECEIVER_H
