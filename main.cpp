#include <QCoreApplication>

#include "threadSubclass.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("T_MAIN");

    EventDrivenThread theFirstThread("T_FIRST");
    theFirstThread.start();

    EventDrivenThread theSecondThread("T_SECOND");
    theSecondThread.start();

    return a.exec();
}
