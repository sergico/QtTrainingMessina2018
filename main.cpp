#include <QCoreApplication>

#include <QThread>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Look Ma' a Thread... " << QThread::currentThreadId();

    QThread anotherThread;
    anotherThread.start();
    qDebug() << "Look Ma' another Thread... " << anotherThread.currentThreadId();
    return a.exec();
}

