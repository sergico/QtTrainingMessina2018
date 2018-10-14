#include <QCoreApplication>

#include "runnabletask.h"
#include <QThreadPool>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int maxThreadCount = QThreadPool::globalInstance()->maxThreadCount();
    qDebug() << "Maximum no. of threads on the global pool is " << maxThreadCount;
    qDebug() << "No. of pool's thread in use:" << QThreadPool::globalInstance()->activeThreadCount();

    QThreadPool myCustomeThreadPool;
    myCustomeThreadPool.setMaxThreadCount(8);
    qDebug() << "Maximum no. of threads on my custom pool is " << myCustomeThreadPool.maxThreadCount();
    qDebug() << "No. of my custom pool's thread in use:" << myCustomeThreadPool.activeThreadCount();

    RunnableTask t1("T_ONE");
    RunnableTask t2("T_TWO");

    qDebug() << "t1 Runnable auto delete" << t1.autoDelete();
    qDebug() << "t2 Runnable auto delete" << t2.autoDelete();

    QThreadPool::globalInstance()->start(&t1);
    QThreadPool::globalInstance()->start(&t2);

    return a.exec();
}
