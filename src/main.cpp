#include <QApplication>
#include "simulation/world.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    World world(b2Vec2(0.0f, -80.0f));
    world.resize(700, 500);
    world.show();
    world.start();
    return app.exec();
}
