#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QDateTime>

static const qint32 MAP_SIZE = 3;


class Map
{
    static qint32 m_map[MAP_SIZE][MAP_SIZE];
public:
    bool isEmpty(qint32 x, qint32 y) const
    {
        if ( m_map[x][y] == 0 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void moveTo(qint32 x, qint32 y, int id)
    {
        Map::m_map[x][y] = id;
    }

    void print() const
    {

        QDebug deb = qDebug();
        for(int x = 0; x < MAP_SIZE; x++)
        {
            for (int y = 0; y < MAP_SIZE; y++)
            {
                deb.noquote().nospace() << QString("[%1]").arg(Map::m_map[x][y]);
            }
            deb << "\n\n";

        }
    }

    int mapValue()
    {
        int s = 0;
        for(int x = 0; x < MAP_SIZE; x++)
        {
            for (int y = 0; y < MAP_SIZE; y++)
            {
                s += s + Map::m_map[x][y];
            }
        }
        return s;
    }
};

class Robot
{
    qint32 m_id;
    Map m_map;

    int current_x;
    int current_y;

public:
    Robot(int i_robotId, Map i_map, int xStart, int yStart) :
        m_id(i_robotId),
        m_map(i_map),
        current_x(xStart),
        current_y(yStart)
    {}

    bool check(int x, int y)
    {
        if (m_map.isEmpty(x, y))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void teleportTo(int x, int y)
    {
        m_map.moveTo(current_x, current_y, 0);
        current_x = x;
        current_y = y;
        m_map.moveTo(x, y, m_id);
    }

    Map& getMap() { return m_map; }
};

class RobotWanderingThread: public QThread
{
    Robot m_robot;
public:
    RobotWanderingThread(Robot i_robot) :
        m_robot(i_robot)
    {
        qsrand( QDateTime::currentDateTimeUtc().toMSecsSinceEpoch() );
    }

    bool collision()
    {
        if ( m_robot.getMap().mapValue() < 3 )
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    void run()
    {
        while(1)
        {
            int x = qrand() % MAP_SIZE;
            int y = qrand() % MAP_SIZE;

            bool isFree = m_robot.check(x, y);
            if (isFree)
            {
                m_robot.teleportTo(x, y);
            }

            QThread::msleep( qrand() % 100 );
            m_robot.getMap().print();
            if ( collision() )
            {
                qDebug() << "BOOOOOM!";
                exit();
            }
        }
    }

};

#endif // ROBOT_H
