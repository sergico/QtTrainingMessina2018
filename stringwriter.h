#ifndef STRINGWRITER_H
#define STRINGWRITER_H

#include <QString>
#include <QThread>
#include <QDebug>

#include <QMutex>

extern "C" QString g_sharedResourse;

class StringWriterThread : public QThread
{
    Q_OBJECT

    QString m_tag;
    QMutex m_localMutex;

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
        while( true )
        {
            m_localMutex.lock();    // start critical section
            {
                g_sharedResourse = m_tag;
                if ( !g_sharedResourse.contains(m_tag) )
                {
                    emit syncErrorSignal();
                    qDebug() << "SYNC ERROR!" << g_sharedResourse;
                    exit (1);
                }
                qDebug() << QString("[%1] %2")
                          .arg(QThread::currentThread()->objectName())
                          .arg(g_sharedResourse);
            }
            m_localMutex.unlock();  // terminate critical section
        }
    }
};

#endif // STRINGWRITER_H
