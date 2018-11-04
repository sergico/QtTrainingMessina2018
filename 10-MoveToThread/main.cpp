#include <QCoreApplication>

#include "manager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("T_MAIN");
    ThreadManager theThreadManager;
    theThreadManager.start();

    return a.exec();
}
