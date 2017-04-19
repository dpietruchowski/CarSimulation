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

///
/// \brief The Simulation class represents world simulation. It contains b2World
/// instance, which manages all physics entities, dynamic simulation and
/// asynchronous queries. In this instance individuals are tested. When
/// individual stops or ends the map, then it is moved to GeneticAlgorithm
/// object and became part of population. New individuals, created in
/// GeneticAlgorithm are moved to buffer and set in queue to get into world.
///
class Simulation : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief A Simulation constructor.
    /// \param initPosition The init position of created cars
    /// \param gravity The b2World gravity used to simulate physics
    /// \param size The size of the world
    /// \param bufferSize The size of the buffer, which stores newly created
    /// individuals, which waiting to be added to world simulation
    /// \param params Genetic parameters which defines population size,
    /// type of selection, mutation and crossover probabilities
    ///
    explicit Simulation(b2Vec2 initPosition, b2Vec2 gravity, b2Vec2 size,
                        size_t bufferSize, const GeneticParameters& params);
    ~Simulation() = default;

    ///
    /// \brief Sets the interval, which is time elapsed between updates.
    /// \param interval New interval value
    ///
    void setInterval(double interval);

    ///
    /// \brief Returns time elapsed since world simulation was started.
    /// \return Time elapsed since world simulation was started
    ///
    double time() const;

    ///
    /// \brief Returns reference to GeneticAlgorithm object, which is responsible
    /// for creating new individuals.
    /// \return The GeneticAlgorithm instance
    ///
    const GeneticAlgorithm& genetic() const;

signals:
    ///
    /// \brief This signal is emitted when individual is added to b2World simulation.
    /// \param item Individual added to b2World simulation
    ///
    void addItem(QGraphicsItem* item);

    ///
    /// \brief This signal is emitted when individual is removed from b2World simulation.
    /// \param car Individual removed from b2World simulation.
    ///
    void removeItem(CarSPtr car);

    ///
    /// \brief This signal is emitted when world time was changed (next step of simulation)
    /// \param time New value of world time
    ///
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
