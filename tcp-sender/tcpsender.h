#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QSslSocket>

class TcpSender : public QObject
{
    Q_OBJECT

    QSslSocket* m_sslSocketPtr;

    QHostAddress m_targetAddress;
    quint16      m_targetPort;

    qint32      m_bytesToWrite;
    qint32      m_bytesWritten;

protected slots:
    void onSslSocketConnectedSlot()
    {
        qDebug() << QString("SSl socket connected!");
        qDebug() << QString("Now we are ready to send data... NOT ENCRYPTED YET!");
    }

    void onSslSocketEncryptedSlot()
    {
        qDebug() << QString("SSl socket connected!");
        qDebug() << QString("Now we are ready to send data... NOT ENCRYPTED YET!");
        QTimer::singleShot(100, this, SLOT(sendDataSlot()) );
    }

    void sendDataSlot()
    {
        QString dataToSend;
        dataToSend = "This is the stream of data we want to send... but no one will be able to read it!!!!";
        this->sendSomeData( dataToSend );
    }

    void onSslSocketErrorSlot(const QList<QSslError>& i_errors)
    {
        qDebug() << "SSL ERROR... connection might be unsecure... BEWARE!";
        foreach ( QSslError e, i_errors )
        {
            qDebug() << QString("- %1").arg(e.errorString());
        }
        /*
         * !!WARNING!! Do it at your own risk
         */
        m_sslSocketPtr->ignoreSslErrors();
    }

    void onSslSocketDisconnectedSlot()
    {
        qDebug() << QString("TCP socket disconnected");
    }

    void onSslSocketErrorSlot(QAbstractSocket::SocketError socketError)
    {
        qDebug() << QString("TCP socket error! / %1 / %2")
                    .arg(m_sslSocketPtr->errorString())
                    .arg(socketError);

        m_sslSocketPtr->close();
        m_sslSocketPtr->deleteLater();
    }

    void onBytesWrittenSlot(qint64 i_bw)
    {
        m_bytesWritten += i_bw;
        qDebug() << QString("Bytes written: %1/%2")
                    .arg(m_bytesWritten)
                    .arg(m_bytesToWrite);
        if ( m_bytesToWrite == m_bytesWritten )
        {
            m_sslSocketPtr->disconnectFromHost();
        }
    }

public:
    TcpSender(const QString& i_address, quint16 i_port) :
        m_sslSocketPtr( new QSslSocket(this) ),
        m_targetAddress(i_address),
        m_targetPort(i_port),
        m_bytesToWrite(0),
        m_bytesWritten(0)
    {
        qDebug() << "TCP Socket created";

        connect( m_sslSocketPtr, SIGNAL(connected()),
                 this,           SLOT(onSslSocketConnectedSlot()) );

        connect( m_sslSocketPtr, SIGNAL(disconnected()),
                 this,           SLOT(onSslSocketDisconnectedSlot()) );

        connect( m_sslSocketPtr, SIGNAL(error(QAbstractSocket::SocketError)),
                 this,           SLOT(onSslSocketErrorSlot(QAbstractSocket::SocketError)) );

        connect( m_sslSocketPtr, SIGNAL(bytesWritten(qint64)),
                 this,           SLOT(onBytesWrittenSlot(qint64)) );

        /* Enctyption specific sig/slots */

        connect( m_sslSocketPtr, SIGNAL(encrypted()),
                 this,           SLOT(onSslSocketEncryptedSlot()) );

        connect( m_sslSocketPtr, SIGNAL(sslErrors(const QList<QSslError>&)),
                 this,           SLOT(onSslSocketErrorSlot(const QList<QSslError>&)) );
    }

    ~TcpSender()
    {
        m_sslSocketPtr->close();
        m_sslSocketPtr->deleteLater();
    }

    void connecteMe()
    {
#if (0)
        m_sslSocketPtr->connectToHost(m_targetAddress, m_targetPort);
#endif
        m_sslSocketPtr->connectToHostEncrypted(m_targetAddress.toString(), m_targetPort);
    }

    void disconnectMe()
    {
        m_sslSocketPtr->close();
    }

    void sendSomeData(const QString& i_data)
    {
        m_bytesToWrite = i_data.size();

        int bw = m_sslSocketPtr->write(i_data.toUtf8());
        if ( bw != m_bytesToWrite )
        {
            qDebug() << "!!WARNING!! Partal write... or error";
            if ( -1 == bw )
            {
                qDebug() << "!!CRITICAL!! this was an error... ";
            }
        }
    }

};

#endif // TCPSENDER_H
