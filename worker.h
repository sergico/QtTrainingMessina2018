#ifndef NR_WORKER_H
#define NR_WORKER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QDebug>
#include <QDateTime>

class Worker : public QObject
{
    Q_OBJECT

    QString m_workerName;

signals:
    void workerFinishedSignal();

public slots:
    void start()
    {
        qDebug() << QString("[%1][%2] start() method")
                  .arg(QThread::currentThread()->objectName())
                  .arg(m_workerName);
        for (int i = 0; i < 10; i++)
        {
            qDebug() << QString("[%1][%2] Step %3")
                        .arg(QThread::currentThread()->objectName())
                        .arg(m_workerName)
                        .arg(i);
            QThread::sleep(1);
        }
        emit workerFinishedSignal();
    }

public:
    Worker(const QString& i_name) :
        m_workerName(i_name)
    {
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
