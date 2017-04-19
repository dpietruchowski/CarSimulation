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
    ///
    /// \brief Individuals Container for individual that contains key, which is
    /// individual's score.
    ///
    typedef std::map<double, CarSPtr, std::greater<double>> Individuals;

    ///
    /// \brief A World constructor.
    /// \param gravity The b2World gravity used to simulate physics.
    /// \param size The size of the world
    /// \param bufferSize The size of the buffer, which stores newly created
    /// individuals, which waiting to be added to world simulation
    /// \param params Genetic parameters which defines population size,
    /// type of selection, mutation and crossover probabilities
    /// \param maxTime Maximum time of the world. After that time simulation will
    /// be stopped.
    ///
    World(b2Vec2 gravity, b2Vec2 size, size_t bufferSize,
          const GeneticParameters& params, double maxTime);
    World(const World& other) = delete;
    World(World&& other) = delete;

    ///
    /// \brief A World destructor.
    ///
    ~World();

    ///
    /// \brief Starts all timers.
    ///
    void start();

    ///
    /// \brief Pauses all timers.
    ///
    void pause();

    ///
    /// \brief Stops all timers.
    ///
    void stop();

    ///
    /// \brief Stops drawing timer.
    ///
    void stopDrawing();

    ///
    /// \brief Starts drawing timer.
    ///
    void startDrawing();

    ///
    /// \brief Speeds up simulation.
    /// \param clicked
    ///
    void forward(bool clicked);

    ///
    /// \brief Sets the update timer's interval.
    /// \param interval New interval value
    ///
    void setUpdateInterval(int interval);

    ///
    /// \brief Sets the create object timer's interval.
    /// \param interval New interval value
    ///
    void setCreateObjectInterval(int interval);

    ///
    /// \brief Calculates and returns avarage score in population.
    /// \return Avarage score in population
    ///
    double avarageScore() const;

    ///
    /// \brief Returns best score in population.
    /// \return Best score in population.
    ///
    double bestScore() const;

    ///
    /// \brief Query whether world is running. Returned value depends on timer's
    /// states (stopped or running).
    /// \return @c true is world is running, otherwise @c false
    ///
    bool isRunning() const;

    ///
    /// \brief Returns world's scene, where simulation is being drawn.
    /// \return World's scene
    ///
    WorldScene& scene();

    ///
    /// \brief Returns time elapsed since world simulation was started.
    /// \return Time elapsed since world simulation was started
    ///
    double time() const;

    ///
    /// \brief Returns maximum time of the world. After that time simulation will
    /// be stopped.
    /// \return Maximum time of the world. After that time simulation will
    /// be stopped.
    ///
    double maxTime() const;

    ///
    /// \brief Returns all individuals in population.
    /// \return Individuals in population.
    ///
    Individuals& individuals();

    ///
    /// \brief Returns simulation object.
    /// \return The simulation
    ///
    const Simulation &simulation() const;

signals:
    ///
    /// \brief This signal is emitted when
    ///
    void initialize();
    ///
    /// \brief This signal is emitted when individual is added to population.
    /// \param index The index of added individual
    /// \param individual Added individual
    ///
    void addObject(int index, CarSPtr individual);
    ///
    /// \brief This signal is emitted when individual is removed from population.
    /// \param index The index of removed individual
    /// \param individual Removed individaul
    ///
    void removeObject(int index, CarSPtr individual);
    ///
    /// \brief This signal is emitted when world is updated.
    ///
    void update();

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
    double maxTime_;
    bool isRunning_;
};

#endif // WORLD_H
