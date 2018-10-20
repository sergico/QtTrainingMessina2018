#ifndef SIMPLEWEBCLIENT_H
#define SIMPLEWEBCLIENT_H


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QUrl>
#include <QString>
#include <QDebug>

class SimpleUrlDowloader : public QObject
{
    Q_OBJECT

    QUrl m_url;
    QNetworkAccessManager* m_networkManagerPtr;

protected slots:
    void onNetworkReplyReadySlot(QNetworkReply* i_reply);

public:
    SimpleUrlDowloader();
    ~SimpleUrlDowloader();

    bool download(const QString& i_url);
};

#endif // SIMPLEWEBCLIENT_H
