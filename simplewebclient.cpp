#include "simplewebclient.h"

SimpleUrlDowloader::SimpleUrlDowloader() :
    m_url(QUrl("")),
    m_networkManagerPtr(nullptr)
{
    m_networkManagerPtr = new QNetworkAccessManager(this);

    connect( m_networkManagerPtr, SIGNAL(finished(QNetworkReply*)),
             this,                SLOT(onNetworkReplyReadySlot(QNetworkReply*)) );

    connect( m_networkManagerPtr, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
             this,                SLOT(onAuthenticationRequestSlot(QNetworkReply*, QAuthenticator*)) );

    connect( m_networkManagerPtr, SIGNAL(encrypted(QNetworkReply*)),
             this,                SLOT(onEncryptedConnectionSlot(QNetworkReply*)) );

    connect ( m_networkManagerPtr, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)),
              this,                SLOT(onSslErrorsSlot(QNetworkReply*, const QList<QSslError>&)) );
}

SimpleUrlDowloader::~SimpleUrlDowloader()
{
    if ( m_networkManagerPtr )
    {
        delete m_networkManagerPtr;
    }
}

bool SimpleUrlDowloader::download(const QString& i_url)
{
    m_url = QUrl(i_url);
    QNetworkReply* replyPtr = m_networkManagerPtr->get( QNetworkRequest(m_url) );
    qDebug() << replyPtr;
    if (replyPtr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SimpleUrlDowloader::onNetworkReplyReadySlot(QNetworkReply* i_reply)
{
    if ( QNetworkReply::NoError != i_reply->error())
    {
        qDebug() << "Error downloading " << m_url.toString();
        qDebug() << "Error is: " << i_reply->errorString();
    }
    else
    {
        QByteArray data = i_reply->readAll();
        qDebug() << "===="<< m_url.toString() << "====";
        qDebug() << data;
        qDebug() << i_reply;
    }
    i_reply->deleteLater();
}

void SimpleUrlDowloader::onAuthenticationRequestSlot(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);

    qDebug() << "Request for Authentication received...";
    authenticator->setUser("demo");
    authenticator->setPassword("password");
}

void SimpleUrlDowloader::onEncryptedConnectionSlot(QNetworkReply*)
{
    qDebug() << "Connection is going to be encrypted... do you extra check here";
}

void SimpleUrlDowloader::onSslErrorsSlot(QNetworkReply* i_replyPtr,
                                         const QList<QSslError>& i_sslErrorList)
{
    qDebug() << "SSL Errors occurred, please find details below:";
    foreach( QSslError e, i_sslErrorList )
    {
        qDebug() << e;
    }

    qDebug() << "!!WARNING!! Ignoring SSL Error on purpose; NOT SECRE AT ALL";
    i_replyPtr->ignoreSslErrors();
}
