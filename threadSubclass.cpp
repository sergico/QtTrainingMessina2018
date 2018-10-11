#include "threadSubclass.h"
#include <QDebug>

#include <QTimer>

EventDrivenThread::EventDrivenThread(const QString i_threadName)
{
    this->setObjectName(i_threadName);

    connect ( this, SIGNAL(started()),  this, SLOT(onStartedSlot()), Qt::QueuedConnection );
    connect ( this, SIGNAL(finished()), this, SLOT(onFinishedSlot()), Qt::QueuedConnection );

    QString s("[%1][%2] thread created");
    qDebug() << s.arg(this->objectName())
                 .arg(QThread::currentThread()->objectName());
}

void EventDrivenThread::doSomeWork()
{
    for (qint64 i = 0; i < 5; i++)
    {
        QString s("[%1][%2] %3 sheeps... and counting");
        qDebug() << s.arg(this->objectName())
                     .arg(QThread::currentThread()->objectName())
                     .arg(i);
        QThread::sleep(1);
    }

    qDebug() << "job Done";
    /* someone could catcth and manage this one */
    emit jobDoneSignal();
}


void EventDrivenThread::onStartedSlot()
{
    QString s("[%1][%2] thread started");
    qDebug() << s.arg(this->objectName())
                 .arg(QThread::currentThread()->objectName());
    doSomeWork();
}

void EventDrivenThread::onFinishedSlot()
{
    QString s("[%1][%2] thread stopped");
    qDebug() << s.arg(this->objectName())
                 .arg(QThread::currentThread()->objectName());
}


void EventDrivenThread::run()
{
    QString s("[%1][%2] thread event-loop");
    qDebug() << s.arg(this->objectName())
                 .arg(QThread::currentThread()->objectName());
}
