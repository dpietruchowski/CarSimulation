#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include <QGraphicsScene>
#include "object/car.h"


class WorldScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WorldScene();

    unsigned int nCarsAlive() const
        { return nCarsAlive_; }
    unsigned int nCarsCreated() const
        { return nCarsCreated_; }
    unsigned int nCarsKilled() const
        { return nCarsKilled_; }

private slots:
    void addItem(QGraphicsItem*);
    void removeItem(CarSPtr);

private:
    unsigned int nCarsAlive_;
    unsigned int nCarsCreated_;
    unsigned int nCarsKilled_;
};

#endif // WORLDSCENE_H
