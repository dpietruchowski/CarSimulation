#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QGraphicsScene>
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
    explicit Simulation(b2Vec2 gravity, b2Vec2 size, size_t bufferSize,
                        const GeneticParameters& params);
    ~Simulation() = default;

    void initialize(QGraphicsScene &scene);

signals:
    void addItem(Car*);
    void removeItem(CarSPtr);

private slots:
    void onUpdateTimeout();
    void onCreateObjectTimeout();

private:
    void update();
    void showUpdate();
    void killObject(Objects::iterator &it);
    void createObject();

private:
    b2World world_;
    Objects objects_;
    Ground ground_;
    b2Vec2 size_;
    GeneticAlgorithm genetic_;
    Buffer buffer_;
    Buffer removed_;
    Dialog console_;
};

#endif // SIMULATION_H
