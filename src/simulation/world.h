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
    void pause();
    void stop();
    void forward(bool clicked);
    void setUpdateInterval(int interval);
    void setCreateObjectInterval(int interval);

signals:
    void initialize();

private slots:
    void incTimeout();
    void addItem(QGraphicsItem*);
    void removeItem(CarSPtr);
    void setTime(double);

private:
    QThread thread_;
    QTimer drawTimer_;
    QTimer updateTimer_;
    QTimer createObjectTimer_;
    Simulation simulation_;
    QGraphicsTextItem timeDrawer_;
};

#endif // WORLD_H
