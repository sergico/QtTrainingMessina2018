#include <QCoreApplication>

#include <QString>
#include <QMutex>
#include <QSemaphore>

#include "stringwriter.h"

QString g_sharedResourse;
QMutex g_mutex;
QSemaphore g_semaphore(1); // this is a basically a mutex

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("T_MAIN");

    StringWriterThread t1("Tommaso");
    StringWriterThread t2("Lorenzo");

    t1.start();
    t2.start();

    return a.exec();
}
