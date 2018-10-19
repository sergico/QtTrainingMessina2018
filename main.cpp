#include <QCoreApplication>

#include <QString>
#include "stringwriter.h"

QString g_sharedResourse;


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
