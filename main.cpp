#include <QCoreApplication>

#include "eventdriventhread.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("T_MAIN");

    EventDrivenThread theFirstThread("T_FIRST");
    theFirstThread.start();

    qDebug() << "000000000";

    EventDrivenThread theSecondThread("T_SECOND");
    theSecondThread.start();

    qDebug() << "111111111";

    return a.exec();
}
