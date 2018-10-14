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

    QThread m_workerThread;
    QList<Worker*> m_workerPtrList;

public:
    ThreadManager()
    {
        // name the worker thread
        m_workerThread.setObjectName("T_WORKER_THREAD");
        // create workers
        createWorker( "W_FIRST" );
        createWorker( "W_SECOND" );
    }

    ~ThreadManager()
    {
        qDebug() << "Thread manager destroyed... stopping worker thread";
        m_workerThread.quit();
        m_workerThread.wait();
        qDebug() << "Worker thread terminated correctly";
    }

    void createWorker(const QString& i_workerName)
    {
        // create the worker object
        Worker* workerPtr = new Worker(i_workerName);
        // move worker to thread
        workerPtr->moveToThread(&m_workerThread);
        // configure signals and slots
        connect( &m_workerThread, SIGNAL(started()), workerPtr, SLOT(start()) );
        connect( &m_workerThread, SIGNAL(finished()), workerPtr, SLOT(deleteLater()) );
        connect( workerPtr, SIGNAL(workerFinishedSignal()), workerPtr, SLOT(deleteLater()) );
        m_workerPtrList.append(workerPtr);
    }

    void start()
    {
        // start thread
        m_workerThread.start();
    }
};


#endif /* NR_THREAD_MANAGER_H */
