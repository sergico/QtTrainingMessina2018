#include <QCoreApplication>

#include "simplewebclient.h"
#include <QUrl>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleUrlDowloader theDownloader;

    QString urlStr = "ftp://test.rebex.net/readme.txt";
    QUrl url(urlStr);

    if ( theDownloader.download( url.toString() ) )
    {
        qDebug() << "Downloading " << urlStr;
    }
    else
    {
        qDebug() << "Error downloading " << urlStr;
    }

    return a.exec();
}


