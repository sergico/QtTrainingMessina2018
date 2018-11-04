#ifndef UDPDATASENDER_H
#define UDPDATASENDER_H

#include <QUdpSocket>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QThread>

class UdpDataSender : public QObject
{
    Q_OBJECT

    QHostAddress m_targetAddress;
    quint16      m_targetPort;
    QUdpSocket* m_udpSocketPtr;

protected slots:
    void onDatagramWrittenSlot(qint64 i_byteWritten)
    {
        qDebug() << QString("Written %1 bytes to UDP socket").arg(i_byteWritten);
    }

public:
    UdpDataSender(const QString& i_address, quint16 i_port) :
        m_targetAddress(i_address),
        m_targetPort(i_port),
        m_udpSocketPtr( new QUdpSocket(this) )
    {
        qDebug() << "Created UDP socket";
        connect( m_udpSocketPtr, SIGNAL(bytesWritten(qint64)),
                 this,           SLOT(onDatagramWrittenSlot(qint64)) );
    }

    ~UdpDataSender()
    {
        if (m_udpSocketPtr)
        {
            delete m_udpSocketPtr;
        }
    }

    void sendingDatagrams(int i_noOfDatagramToSend)
    {
        QString dataStrFrm("datagram_#%1");

        for (int i = 0; i < i_noOfDatagramToSend; i++)
        {
            QString dataStr = dataStrFrm.arg(i+1);
            quint64 bw = m_udpSocketPtr->writeDatagram(dataStr.toUtf8(),
                                          m_targetAddress,
                                          m_targetPort);
            if ( -1 == bw )
            {
                qDebug() << QString("Error writing data on UDP socket -> %1:%2 / %3")
                            .arg(m_targetAddress.toString())
                            .arg(m_targetPort)
                            .arg(m_udpSocketPtr->errorString());
            }
            else
            {
                qDebug() << QString("Datagram [%1] written to UDP socket -> %2:%3")
                            .arg(dataStr)
                            .arg(m_targetAddress.toString())
                            .arg(m_targetPort);
            }
            QThread::currentThread()->msleep(500);
        }
    }
};

#endif // UDPDATASENDER_H
