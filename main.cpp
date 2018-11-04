#include <QCoreApplication>
#include <QDebug>

#include "threadmanager.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // name main thread
    QThread::currentThread()->setObjectName("T_MAIN");

    ThreadManager theThreadManager;

    return a.exec();
}
