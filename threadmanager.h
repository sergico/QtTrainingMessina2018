#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QThread>
#include <QDebug>
#include <QString>

#include "threadSubclass.h"

class ThreadManager : public QObject
{
    Q_OBJECT

    SimpleThread m_theFirstThread;

signals:
    void triggerThreadJobSignal();

public:
    ThreadManager() :
        m_theFirstThread("T_FIRST")
    {
        // create a thread
        m_theFirstThread.start();

        connect( this,            SIGNAL(triggerThreadJobSignal()),
                 &m_theFirstThread, SLOT(onTriggerThreadJobSlot()), Qt::QueuedConnection);

        while ( !m_theFirstThread.isRunning() )
        {
            QThread::usleep(10);
            qDebug() << ".";
        }
        emit triggerThreadJobSignal();

    }
};

#endif // THREADMANAGER_H
