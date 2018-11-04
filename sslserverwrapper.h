#ifndef SSLSERVERWRAPPER_H
#define SSLSERVERWRAPPER_H

#include "sslserver.h"

class SslServerWrapper : public QObject
{
    Q_OBJECT

    SslServer* m_serverPtr;

protected slots:
    void onNewClientConnected()
    {
        qDebug() << QString("New SSL Connection");
        QTcpSocket* connectionPtr = m_serverPtr->nextPendingConnection();
        connectionPtr->write("HELLO SSL CLIENT");
    }

public:
    SslServerWrapper()
    {
        /* create the server configuration */
        NrServerConfig cfg;
        cfg.serverAddress       = QHostAddress::LocalHost;
        cfg.serverPort          = 10022;
        cfg.portBindingPolicy   = NrServerConfig::E_BindToSpecificPort;
        cfg.keyfile             = "/home/sergio/Documents/Qt-Training-2018/src/80-qssl-server/selfsigned.key";
        cfg.certfile            = "/home/sergio/Documents/Qt-Training-2018/src/80-qssl-server/selfsigned.crt";
        cfg.passphrase          = "";
        cfg.ignoreSslErrors     = true;
        cfg.disableEncryption   = false;

        /* instantiate the server */
        m_serverPtr = new SslServer(cfg);
        bool ok = m_serverPtr->listen();
        if (!ok)
        {
            qDebug() << "Error starting ssl server";
            exit(1);
        }

        connect ( m_serverPtr, SIGNAL(connectedClient()),
                  this,        SLOT(onNewClientConnected()) );
    }

};

#endif // SSLSERVERWRAPPER_H
