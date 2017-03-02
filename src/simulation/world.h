#ifndef WORLD_H
#define WORLD_H

#include <QTimer>
#include <QThread>
#include "simulation.h"
#include "worldscene.h"

class World: public QObject
{
    Q_OBJECT
public:
    typedef std::map<double, CarSPtr, std::greater<double>> Individuals;
    World(b2Vec2 gravity, b2Vec2 size, size_t bufferSize,
          GeneticParameters params);
    ~World();

    void start();
    void pause();
    void stop();
    void forward(bool clicked);
    void setUpdateInterval(int interval);
    void setCreateObjectInterval(int interval);

    WorldScene& scene()
        { return scene_; }
    double time() const
        { return time_; }
    Individuals& individuals()
        { return individuals_; }
    const Simulation &simulation() const
        { return simulation_; }

signals:
    void initialize();
    void addObject(int, CarSPtr);
    void removeObject(int, CarSPtr);
    void updateTime();

private slots:
    void incTimeout();
    void addObject(CarSPtr);
    void removeObject(CarSPtr);
    void setTime(double);

private:
    QThread thread_;
    QTimer drawTimer_;
    QTimer updateTimer_;
    QTimer createObjectTimer_;
    WorldScene scene_;
    Simulation simulation_;
    Individuals individuals_;
    double time_;
};

#endif // WORLD_H
