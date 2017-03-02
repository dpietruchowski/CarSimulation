#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <Box2D/Box2D.h>
#include <vector>

#include "object/object.h"
#include "object/car.h"
#include "object/ground.h"
#include "buffer.h"
#include "genetic/geneticalgorithm.h"
#include "gui/dialog.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    static const float32 CLICKED_DISTANCE;
    explicit Simulation(b2Vec2 initPosition, b2Vec2 gravity, b2Vec2 size, size_t bufferSize,
                        const GeneticParameters& params);
    ~Simulation() = default;

    void setInterval(double interval);
    double time() const { return time_; }
    GeneticAlgorithm& genetic()
        { return genetic_; }

signals:
    void addItem(QGraphicsItem*);
    void removeItem(CarSPtr);
    void setTime(double time);

private slots:
    void initialize();
    void onUpdateTimeout();
    void onCreateObjectTimeout();

private:
    void update();
    void showUpdate();
    void killObject(Objects::iterator &it);
    void createObject();

private:
    b2Vec2 initPosition_;
    b2World world_;
    Objects objects_;
    Ground ground_;
    b2Vec2 size_;
    GeneticAlgorithm genetic_;
    Buffer buffer_;
    double interval_;
    double time_;
};

#endif // SIMULATION_H
