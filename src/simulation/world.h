#ifndef WORLD_H
#define WORLD_H

#include <QGraphicsScene>
#include <QTimer>
#include <QThread>
#include "simulation.h"

class World: public QGraphicsScene
{
    Q_OBJECT
public:
    World(b2Vec2 gravity, b2Vec2 size, size_t bufferSize,
          GeneticParameters params);
    ~World();

    void start();
    void stop();
    void setUpdateInterval(int interval);
    void setCreateObjectInterval(int interval);

signals:
    void addObject();
    void removeObject();

private slots:
    void pause();
    void removeItem(Car*);
    void addItem(Car*);

private:
    QThread thread_;
    QTimer drawTimer_;
    QTimer updateTimer_;
    QTimer createObjectTimer_;
    Simulation simulation_;
};

#endif // WORLD_H
