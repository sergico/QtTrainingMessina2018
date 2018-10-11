#ifndef SIMPLETHREAD_H
#define SIMPLETHREAD_H

#include <QThread>
#include <QString>

class SimpleThread : public QThread
{
    Q_OBJECT

signals:
    void jobDoneSignal();

private:
    void doSomeWork();

protected slots:
    void onStartedSlot();
    void onFinishedSlot();

    void onTriggerThreadJobSlot();

protected:
    /* reimplement with your thread code */
    void run();

public:
    SimpleThread(const QString& i_threadName);
};

#endif // SIMPLETHREAD_H
