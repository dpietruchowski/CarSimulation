#include "worldscene.h"

WorldScene::WorldScene(): nCarsAlive_(0), nCarsCreated_(0), nCarsKilled_(0)
{
}

void WorldScene::addItem(QGraphicsItem* o)
{
//    qDebug() << "SCENE: Adding item[" << o->id() << "]";
    QGraphicsScene::addItem(o);
    ++nCarsAlive_;
    ++nCarsCreated_;
}

void WorldScene::removeItem(CarSPtr o)
{
//    qDebug() << "SCENE: Removing item[" << o->id() << "]";
    QGraphicsScene::removeItem(o.get());
    --nCarsAlive_;
    ++nCarsKilled_;
}
