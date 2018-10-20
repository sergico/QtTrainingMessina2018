#include "simplewebclient.h"

SimpleUrlDowloader::SimpleUrlDowloader() :
    m_url(QUrl("")),
    m_networkManagerPtr(nullptr)
{
    m_networkManagerPtr = new QNetworkAccessManager(this);
    connect( m_networkManagerPtr, SIGNAL(finished(QNetworkReply*)),
             this,                SLOT(onNetworkReplyReadySlot(QNetworkReply*)) );
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
    }
    else
    {
        QByteArray data = i_reply->readAll();
        qDebug() << "===="<< m_url << "====";
        qDebug() << data;
        qDebug() << i_reply;
    }
    i_reply->deleteLater();
}
