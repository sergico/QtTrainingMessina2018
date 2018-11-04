#ifndef NR_THREAD_MANAGER_H
#define NR_THREAD_MANAGER_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QDebug>
#include <QList>

#include "worker.h"

class ThreadManager :public QObject
{
    Q_OBJECT

    //QThread m_workerThread;
    QList<QThread*> m_threadPtrList;
    QList<Worker*> m_workerPtrList;

public:
    ThreadManager()
    {
        createWorker( "W_FIRST" );
        createWorker( "W_SECOND" );
    }

    ~ThreadManager()
    {
        qDebug() << "Thread manager destroyed... stopping worker thread";
        foreach( QThread* t, m_threadPtrList )
        {
            t->quit();
            t->wait();
        }
        qDebug() << "Worker thread terminated correctly";
    }

    void createWorker(const QString& i_workerName)
    {
        // create the thread
        QThread* threadPtr = new QThread;
        threadPtr->setObjectName( QString("T_").append(i_workerName) );
        // create the worker object
        Worker* workerPtr = new Worker(i_workerName);
        // move worker to thread
        workerPtr->moveToThread(threadPtr);
        // configure signals and slots
        connect( threadPtr, SIGNAL(started()), workerPtr, SLOT(start()) );
        connect( threadPtr, SIGNAL(finished()), workerPtr, SLOT(deleteLater()) );
        connect( workerPtr, SIGNAL(workerFinishedSignal()), workerPtr, SLOT(deleteLater()) );
        m_workerPtrList.append(workerPtr);
        m_threadPtrList.append(threadPtr);
    }

    void start()
    {
        // start thread
        foreach(QThread* t, m_threadPtrList)
        {
            t->start();
        }
    }
};

#endif /* NR_THREAD_MANAGER_H */
