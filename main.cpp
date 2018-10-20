#include <QCoreApplication>

#include "simplewebclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleUrlDowloader theDownloader;

    QString url = "ftp://ftp.cs.brown.edu/pub/COPYING_POLICY";

    if ( theDownloader.download( url ) )
    {
        qDebug() << "Downloading " << url;
    }
    else
    {
        qDebug() << "Error downloading " << url;
    }

    return a.exec();
}


