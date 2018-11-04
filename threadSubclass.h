#ifndef SIMPLETHREAD_H
#define SIMPLETHREAD_H

#include <QThread>
#include <QString>
#include <QTimer>

class SimpleThread : public QThread
{
    Q_OBJECT

    QTimer* m_timerPtr;

signals:
    void jobDoneSignal();

private:

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
