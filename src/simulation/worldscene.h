#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include <QGraphicsScene>
#include "object/car.h"

///
/// \brief The WorldScene class is used to show simulation on screen. It contains
/// objects which take part in simulation.
///
class WorldScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ///
    /// \brief The world scene constructor.
    ///
    WorldScene();

    ///
    /// \brief Returns the number of cars, which are alive (take part
    /// in simulation)
    /// \return The number of individuals, which are alive
    ///
    unsigned int nCarsAlive() const;

    ///
    /// \brief Returns the number of cars, which was created (added to b2World)
    /// since world simulation was started.
    /// \return The number of cars, which was created
    ///
    unsigned int nCarsCreated() const;

    ///
    /// \brief Returns the number of cars, which was killed (removed from b2World)
    /// since world simulation was started.
    /// \return The number of cars, which was killed
    ///
    unsigned int nCarsKilled() const;

private slots:
    void addItem(QGraphicsItem*);
    void removeItem(CarSPtr);

private:
    unsigned int nCarsAlive_;
    unsigned int nCarsCreated_;
    unsigned int nCarsKilled_;
};

#endif // WORLDSCENE_H
