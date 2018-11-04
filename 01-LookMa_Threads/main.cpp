#include <QCoreApplication>

#include <QThread>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // naming threads
    QThread::currentThread()->setObjectName("T_Main");
    qDebug() << "Look Ma' a Thread... " <<
                QThread::currentThreadId() <<
                QThread::currentThread()->objectName();

    // create another thread
    QThread anotherThread;
    anotherThread.setObjectName("T_AnotherThread");
    // start the thread
    anotherThread.start();
    qDebug() << "Look Ma' another Thread... " <<
                anotherThread.currentThreadId() <<
                anotherThread.objectName();
    return a.exec();
}

