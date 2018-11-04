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

protected slots:

public:
    ThreadManager() :
        m_theFirstThread("T_FIRST")
    {
        // start the thread
        m_theFirstThread.start();
    }
};

#endif // THREADMANAGER_H
