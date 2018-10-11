#ifndef SIMPLETHREAD_H
#define SIMPLETHREAD_H

#include <QThread>
#include <QString>

class SimpleThread : public QThread
{
    Q_OBJECT

signals:
    void jobDoneSignal();

protected slots:
    void onStartedSlot();
    void onFinishedSlot();

    void doSomeWork();

protected:
    /* reimplement with your thread code */
    void run();

public:
    SimpleThread(const QString& i_threadName);
};

#endif // SIMPLETHREAD_H
