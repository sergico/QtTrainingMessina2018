#ifndef NR_THREAD_MANAGER_H
#define NR_THREAD_MANAGER_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QDebug>

#include "worker.h"

class ThreadManager :public QObject
{
    Q_OBJECT

    Worker* m_workerPtr;
    QThread m_workerThread;

public:
    ThreadManager()
    {
        // create the worker object
        m_workerPtr = new Worker("W_FIRST_WORKER");
        // name the worker thread
        m_workerThread.setObjectName("T_WORKER_THREAD");
        // move worker to thread
        m_workerPtr->moveToThread(&m_workerThread);
        // configure signals and slots
        connect( &m_workerThread, SIGNAL(started()), m_workerPtr, SLOT(start()) );
        connect( m_workerPtr, SIGNAL(workerFinishedSignal()), m_workerPtr, SLOT(deleteLater()) );
    }

    ~ThreadManager()
    {
        if (m_workerPtr) { delete m_workerPtr; }
        qDebug() << "Thread manager destroyed... stopping worker thread";
        m_workerThread.quit();
        m_workerThread.wait();
        qDebug() << "Worker thread terminated correctly";
    }

    void start()
    {
        // start thread
        m_workerThread.start();
    }
};


#endif /* NR_THREAD_MANAGER_H */
