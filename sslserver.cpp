#include "sslserver.h"
#include <QDebug>

/*!
  \class
  \brief a QTcpServer based SSL server
  This class derives from QTcpServer, overloading the incomingConnection method in order to handle SSL connections from tcp clients.
  It also provides a different Queue to handle SSL connections because Qt < 4.7 do not support the addition of a socket to the pendingConnections list
  */
SslServer::SslServer(const NrServerConfig &aSslConfig, QObject *parent) :
    QTcpServer(parent),
    m_ServerConfig(aSslConfig)
{
    qDebug() << "SSL Server created";
}


bool
SslServer::listen(const QHostAddress &address, quint16 i_minPort, quint16 i_maxPort)
{
    bool res = false;

	for (quint16 i = i_minPort; i < i_maxPort; i++) {
        res = QTcpServer::listen(address, i);
		if (res)
			break;
	}

	return res;
}


bool
SslServer::listen()
{
    bool res = false;

    if (m_ServerConfig.portBindingPolicy == NrServerConfig::E_BindUsingPortRange) {
        for (quint16 i = m_ServerConfig.serverMinPort; i < m_ServerConfig.serverMaxPort; i++) {
            res = QTcpServer::listen(m_ServerConfig.serverAddress, i);
            if (res)
                break;
        }
    }
    else
        res = QTcpServer::listen(m_ServerConfig.serverAddress, m_ServerConfig.serverPort);

    return res;
}


bool SslServer::listen(const QHostAddress &address, quint16 port)
{
    return QTcpServer::listen(address, port);
}


/*!
  \brief we overload the virtual QTcpServer::incomingConnection(int) method in order to start the SSL Encryption
  */
void
SslServer::incomingConnection(qintptr socketDescriptor)
{
	QSslSocket *serverSocket = new QSslSocket;
    serverSocket->setProtocol(QSsl::AnyProtocol);
    
    MTSDBG << "using ssl socket at address " << serverSocket;

    if (serverSocket->setSocketDescriptor(socketDescriptor))
    {
        MTSDBG << "Incoming connection from " << serverSocket->peerAddress().toString() << ":" << serverSocket->peerPort();
        MTSDBG << serverSocket;
        if (serverSocket->peerAddress().toString().isEmpty())
        {
            qDebug() << QString("Connecting socket seems to be disconnected: aborting!");

            qCritical() << "#########> Connecting socket seems to be disconnected: aborting!";
            serverSocket->abort();
            serverSocket->close();
            serverSocket->deleteLater();
            return;
        }

        qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
        connect(serverSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));

        if (!m_ServerConfig.disableEncryption)
        {
            connect(serverSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSslErrors(QList<QSslError>)));

            serverSocket->setLocalCertificate(m_ServerConfig.certfile, QSsl::Pem);
            serverSocket->setPrivateKey(m_ServerConfig.keyfile, QSsl::Rsa, QSsl::Pem, m_ServerConfig.passphrase);

            if(serverSocket->localCertificate().isBlacklisted())
            {
                qDebug() << QString("BlackListed certificate %1")
                            .arg( m_ServerConfig.certfile );
            }

            if(serverSocket->privateKey().isNull())
            {
                qDebug() << QString("Invalid private key (NULL) %1")
                            .arg(m_ServerConfig.keyfile);
            }

            MTSDBG << "SSL Server key" << serverSocket->privateKey();
            MTSDBG << "SSL Server certificate"  << serverSocket->localCertificate();
            serverSocket->startServerEncryption();
        }

        this->addPendingConnection(serverSocket); //this does not work with qt < 4.7
        emit connectedClient();
    }
    else
    {
        qDebug() << QString("Invalid set socket descriptor operation");
        qCritical() << "Could not set socket descriptor!!! ";
        serverSocket->deleteLater();
        //delete serverSocket; //FIXME - this might be better replaced by deleteLater()
    }
}


void SslServer::onSocketError(QAbstractSocket::SocketError e)
{
    QTcpSocket *sock = (QTcpSocket*) sender();
    if (sock)
    {
        MTSDBG << "socket " << sock << " error " << e;

        QString err = "Server reports error: %1 / peer address: %2:%3";
        err = err.arg(sock->errorString()).arg(sock->peerAddress().toString()).arg(sock->peerPort());

        qDebug() << QString("WARNING %1").arg(err);
        MTSDBG << "current socket state" << sock->state();
    }
    else
    {
        QString err = "Socket error event received but the socket is invalid (null)";
        qDebug() << QString("CRITICAL %1").arg(err);
    }
}


void SslServer::onSslErrors(QList<QSslError> aErrorList)
{
    MTSDBG << "ssl error " << aErrorList;
    QList<QSslError> errorsToIgnore;

    foreach (QSslError se, aErrorList) {
		if (se != QSslError::NoError) {
            MTSDBG << se.errorString();
            qDebug() << QString("CRITICAL Server reports SSL error: %1").arg(se.errorString());
            if (se.error() == QSslError::SelfSignedCertificate || se.error() == QSslError::SelfSignedCertificateInChain)
			{
				if (m_ServerConfig.allowUntrustedCerts) {
                    MTSDBG << "Cert is SelfSigned... but we're ok with that...";
                    qDebug() << QString("WARNING: Client certificate is untrusted but we're ok with that");
                    errorsToIgnore << se;
				}
			}
		}
    }

    QSslSocket *sslsock = (QSslSocket*) sender();
    if (sslsock) {
        if (m_ServerConfig.ignoreSslErrors) {
            qDebug() << QString("There were SSL errors but server is configured to ignore them all");

            sslsock->ignoreSslErrors();
        }
        else {
            qDebug() << QString("Ignoring some SSL errors...");

            if (errorsToIgnore.count() > 0)
                sslsock->ignoreSslErrors(errorsToIgnore);
        }
        MTSDBG << "socket is encrypted: " << sslsock->isEncrypted();
    }
}
 

