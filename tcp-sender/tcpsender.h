#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QDebug>
#include <QTimer>

class TcpSender : public QObject
{
    Q_OBJECT

    QTcpSocket* m_tcpSocketPtr;

    QHostAddress m_targetAddress;
    quint16      m_targetPort;

    qint32      m_bytesToWrite;
    qint32      m_bytesWritten;

protected slots:
    void onTcpSocketConnectedSlot()
    {
        qDebug() << QString("TCP socket connected!");
        qDebug() << QString("Now we are ready to send data");
        QTimer::singleShot(100, this, SLOT(sendDataSlot()) );
    }
    void sendDataSlot()
    {
        QString dataToSend;
        dataToSend = "This is the stream of data we want to send...";
        this->sendSomeData( dataToSend );
    }

    void onTcpSocketDisconnectedSlot()
    {
        qDebug() << QString("TCP socket disconnected");
    }

    void onTcpSocketErrorSlot(QAbstractSocket::SocketError socketError)
    {
        qDebug() << QString("TCP socket error! / %1 / %2")
                    .arg(m_tcpSocketPtr->errorString())
                    .arg(socketError);

        m_tcpSocketPtr->close();
        m_tcpSocketPtr->deleteLater();
    }

    void onBytesWrittenSlot(qint64 i_bw)
    {
        m_bytesWritten += i_bw;
        qDebug() << QString("Bytes written: %1/%2")
                    .arg(m_bytesWritten)
                    .arg(m_bytesToWrite);
        if ( m_bytesToWrite == m_bytesWritten )
        {
            m_tcpSocketPtr->disconnectFromHost();
        }
    }

public:
    TcpSender(const QString& i_address, quint16 i_port) :
        m_tcpSocketPtr( new QTcpSocket(this) ),
        m_targetAddress(i_address),
        m_targetPort(i_port),
        m_bytesToWrite(0),
        m_bytesWritten(0)
    {
        qDebug() << "TCP Socket created";

        connect( m_tcpSocketPtr, SIGNAL(connected()),
                 this,           SLOT(onTcpSocketConnectedSlot()) );

        connect( m_tcpSocketPtr, SIGNAL(disconnected()),
                 this,           SLOT(onTcpSocketDisconnectedSlot()) );

        connect( m_tcpSocketPtr, SIGNAL(error(QAbstractSocket::SocketError)),
                 this,           SLOT(onTcpSocketErrorSlot(QAbstractSocket::SocketError)) );

        connect( m_tcpSocketPtr, SIGNAL(bytesWritten(qint64)),
                 this,           SLOT(onBytesWrittenSlot(qint64)) );
    }

    ~TcpSender()
    {
        m_tcpSocketPtr->close();
        m_tcpSocketPtr->deleteLater();
    }

    void connecteMe()
    {
        m_tcpSocketPtr->connectToHost(m_targetAddress, m_targetPort);
    }

    void disconnectMe()
    {
        m_tcpSocketPtr->close();
    }

    void sendSomeData(const QString& i_data)
    {
        m_bytesToWrite = i_data.size();

        int bw = m_tcpSocketPtr->write(i_data.toUtf8());
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
