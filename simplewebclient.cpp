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
