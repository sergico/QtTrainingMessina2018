#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H

#include <QRunnable>
#include <QString>
#include <QDebug>

class RunnableTask : public QRunnable
{
    QString m_name;

    void run()
    {
        qDebug() << QString("Runnig task %1").arg(m_name);
    }

public:
    RunnableTask(const QString& i_name) :
        m_name(i_name)
    {}

};

#endif // RUNNABLETASK_H
