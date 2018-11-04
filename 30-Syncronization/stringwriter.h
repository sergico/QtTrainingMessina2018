#ifndef STRINGWRITER_H
#define STRINGWRITER_H

#include <QString>
#include <QThread>
#include <QDebug>

#include <QMutex>
#include <QMutexLocker>
#include <QSemaphore>
#include <QDateTime>

extern "C" QString g_sharedResourse;
extern "C" QMutex g_mutex;
extern "C" QSemaphore g_semaphore; // this is a basically a mutex


class TalkingMutexLocker : public QMutexLocker
{
public:
    TalkingMutexLocker(QMutex* io_mutex) :
        QMutexLocker(io_mutex)
    {
        qDebug() << Q_FUNC_INFO;
    }
    ~TalkingMutexLocker()
    {
        qDebug() << Q_FUNC_INFO;
    }
};

class StringWriterThread : public QThread
{
    Q_OBJECT

    QString m_tag;

signals:
    void syncErrorSignal();

public:
    StringWriterThread(const QString i_tag) :
        m_tag(i_tag)
    {
        this->setObjectName( QString("T_%1").arg(m_tag) );
    }

    void run()
    {
        qint32 seed = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
        qsrand( seed );

        qDebug() << QString("[%1] %2 is going to the appointment... ")
                    .arg(QThread::currentThread()->objectName())
                    .arg(m_tag);

        // doing stuff...
        qint32 timeToArriveSec = qrand() % 10;
        qDebug() << QString("[%1] %2 will be there in %3 ")
                    .arg(QThread::currentThread()->objectName())
                    .arg(m_tag)
                    .arg(timeToArriveSec);

        QThread::currentThread()->sleep( timeToArriveSec );
        qDebug() << QString("[%1] %2 just arrived to the appointment... ")
                    .arg(QThread::currentThread()->objectName())
                    .arg(m_tag);
        QThread::currentThread()->sleep( 1 );

        g_semaphore.release();

    }
};

#endif // STRINGWRITER_H
