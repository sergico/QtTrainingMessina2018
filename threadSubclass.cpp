#include "threadSubclass.h"
#include <QDebug>

#include <QDateTime>
#include <QTimer>

SimpleThread::SimpleThread(const QString &i_threadName) :
    m_timerPtr(nullptr)
{
    // init random seed
    qsrand( static_cast<quint32>(QDateTime::currentMSecsSinceEpoch()) );

    this->setObjectName(i_threadName);

    connect ( this, SIGNAL(started()),  this, SLOT(onStartedSlot()), Qt::QueuedConnection );
    connect ( this, SIGNAL(finished()), this, SLOT(onFinishedSlot()), Qt::QueuedConnection );

    QString s("[%1][%2] thread created");
    qDebug() << s.arg(this->objectName())
                 .arg(QThread::currentThread()->objectName());
}

void SimpleThread::doSomeWork()
{
    for (qint64 i = 0; i < 10; i++)
    {
        QString s("[%1][%2] %3 sheeps... and counting");
        qDebug() << s.arg(this->objectName())
                     .arg(QThread::currentThread()->objectName())
                     .arg(i);
        QThread::usleep( (qrand() % 100) * 100 );
    }

    qDebug() << QString("[%1][%2] Job Done")
                .arg(this->objectName())
                .arg(QThread::currentThread()->objectName());

    /* someone could catcth and manage this one */
    emit jobDoneSignal();
}


void SimpleThread::onStartedSlot()
{
    QString s("[%1][%2] thread started");
    qDebug() << s.arg(this->objectName())
                 .arg(QThread::currentThread()->objectName());

}

void SimpleThread::onFinishedSlot()
{
    QString s("[%1][%2] thread stopped");
    qDebug() << s.arg(this->objectName())
                 .arg(QThread::currentThread()->objectName());
}

void SimpleThread::run()
{
    QString s("[%1][%2] thread run()");
    qDebug() << s.arg(this->objectName())
                 .arg(QThread::currentThread()->objectName());

    m_timerPtr = new QTimer;
    m_timerPtr->setSingleShot(true);
    connect( m_timerPtr, SIGNAL(timeout()), SLOT(doSomeWork()), Qt::QueuedConnection );
    m_timerPtr->start(1000);

    exec();
}
