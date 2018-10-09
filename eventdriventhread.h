#ifndef EVENTDRIVENTHREAD_H
#define EVENTDRIVENTHREAD_H

#include <QThread>
#include <QString>

class EventDrivenThread : public QThread
{
    Q_OBJECT

private:
    void doSomeWork();

protected slots:
    void onStartedSlot();
    void onFinishedSlot();

protected:
    void run();

public:
    EventDrivenThread(const QString i_threadName);
};

#endif // EVENTDRIVENTHREAD_H
