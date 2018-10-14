#ifndef NR_WORKER_H
#define NR_WORKER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QTimer>

class Worker : public QObject
{
    Q_OBJECT

    QString m_workerName;
    QTimer* m_timerPtr;
    qint32 m_counter;

signals:
    void workerFinishedSignal();

public slots:
    void start()
    {
        qDebug() << QString("[%1][%2] start() method")
                  .arg(QThread::currentThread()->objectName())
                  .arg(m_workerName);

        m_timerPtr = new QTimer(this);
        m_timerPtr->setSingleShot(false);
        connect( m_timerPtr, SIGNAL(timeout()), this, SLOT(startInternal()) );
        m_timerPtr->start(1000);
    }

protected slots:
    void startInternal()
    {
        m_counter++;
        qDebug() << QString("[%1][%2] Step %3")
                    .arg(QThread::currentThread()->objectName())
                    .arg(m_workerName)
                    .arg(m_counter);
        QThread::msleep( qrand() % 1000 );
        if ( m_counter == 10  )
        {
            m_timerPtr->stop();
            emit workerFinishedSignal();
        }
    }

public:
    Worker(const QString& i_name) :
        m_workerName(i_name),
        m_timerPtr(nullptr),
        m_counter(0)
    {
        // Do NOT instantiate the QTimer here!
        qsrand( static_cast<quint32>(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()) );

        qDebug() << QString("[%1][%2] Worker created")
                    .arg(QThread::currentThread()->objectName())
                    .arg(m_workerName);
    }

    ~Worker()
    {
        qDebug() << QString("[%1][%2] Worker deleted")
                    .arg(QThread::currentThread()->objectName())
                    .arg(m_workerName);
    }
};

#endif /* NR_WORKER_H */
