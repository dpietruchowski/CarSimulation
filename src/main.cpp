#include <QApplication>
#include "simulation/simulation.h"
#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
//    srand(time(0));
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
   /* World world(b2Vec2(0.0f, -80.0f), b2Vec2(5000.0f, 100.0f));
    world.resize(700, 500);
    world.show();
    world.start();*/
    return app.exec();
}
