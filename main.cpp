#include <QCoreApplication>

#include "threadSubclass.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // name main thread
    QThread::currentThread()->setObjectName("T_MAIN");

    // create a thread
    SimpleThread theFirstThread("T_FIRST");
    theFirstThread.start();

    // craete another thread
    SimpleThread theSecondThread("T_SECOND");
    theSecondThread.start();

    return a.exec();
}
