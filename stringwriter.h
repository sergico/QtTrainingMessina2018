#ifndef STRINGWRITER_H
#define STRINGWRITER_H

#include <QString>
#include <QThread>
#include <QDebug>

#include <QMutex>

extern "C" QString g_sharedResourse;
extern "C" QMutex g_mutex;

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
        while( true )
        {
            g_mutex.lock();    // start critical section
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
            g_mutex.lock();  // terminate critical section... you sure?
        }
    }
};

#endif // STRINGWRITER_H
