#include <QCoreApplication>

#include <QString>
#include <QMutex>
#include <QSemaphore>
#include <QList>

#include "stringwriter.h"

static const int g_noOfPeopleToMeet = 4;

QString g_sharedResourse;
QMutex g_mutex;
QSemaphore g_semaphore;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("T_MAIN");

    StringWriterThread* tPtr = nullptr;
    QList<StringWriterThread*> threadList;

    qDebug() << "Let's meet at the pub...";

    for (int i = 0; i < g_noOfPeopleToMeet; i++)
    {
      tPtr = new StringWriterThread( QString("Person_no_%1").arg(i) );
      threadList.append(tPtr);
      tPtr->start();
    }

    g_semaphore.acquire( g_noOfPeopleToMeet );
    qDebug() << "Good! you are all here finally!";

    return a.exec();
}
