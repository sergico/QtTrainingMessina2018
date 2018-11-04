#ifndef UDPDATARECEIVER_H
#define UDPDATARECEIVER_H

#include <QUdpSocket>
#include <QString>
#include <QByteArray>
#include <QDebug>



class UdpDataReceiver : public QObject
{
    Q_OBJECT

    QUdpSocket*  m_udpSocketPtr;
    QHostAddress m_bindAddress;
    quint16      m_bindPort;

protected slots:
    void onIncomingDatagramSlot()
    {
        QByteArray datagram;
        QHostAddress sourceAddress;
        quint16 sourcePort;

        while ( m_udpSocketPtr->hasPendingDatagrams() )
        {
            datagram.resize( m_udpSocketPtr->pendingDatagramSize() );
            m_udpSocketPtr->readDatagram( datagram.data(),
                                          datagram.size(),
                                          &sourceAddress,
                                          &sourcePort);

            qDebug() << QString("Received datagram [%1] <- %2:%3")
                        .arg(datagram.constData())
                        .arg(sourceAddress.toString())
                        .arg(sourcePort);
        }
    }

public:
    UdpDataReceiver(const QString& i_bindAddress, quint16 i_bindPort) :
        m_udpSocketPtr( new QUdpSocket(this) ) ,
        m_bindAddress(i_bindAddress),
        m_bindPort(i_bindPort)
    {

    }

    void start()
    {
        /* bind the socket to listen for incoming datagrans */
        bool socketBound = m_udpSocketPtr->bind(m_bindAddress, m_bindPort);
        if (socketBound)
        {
            qDebug() << QString("UDP socket listening on %1:%2")
                        .arg(m_bindAddress.toString())
                        .arg(m_bindPort);
        }
        else
        {
            qDebug() << QString("Error binding UDP socket to %1:%2 / %3")
                        .arg(m_bindAddress.toString())
                        .arg(m_bindPort)
                        .arg(m_udpSocketPtr->errorString());
        }

        connect( m_udpSocketPtr, SIGNAL(readyRead()),
                 this,           SLOT(onIncomingDatagramSlot()) );
    }
};

#endif // UDPDATARECEIVER_H
