#ifndef WORLD_H
#define WORLD_H

#include <QtGui>
#include <QtOpenGL>
#include <QWidget>
#include <QTimerEvent>
#include <QPaintEvent>
#include <Box2D/Box2D.h>
#include <vector>

#include "object.h"
#include "car.h"
#include "ground.h"
#include "genetic/geneticalgorithm.h"

class World : public QWidget
{
    Q_OBJECT
public:
    static const float32 CLICKED_DISTANCE;
    explicit World(b2Vec2 gravity, b2Vec2 size, QWidget *parent = 0);
    ~World() = default;

    void paintEvent(QPaintEvent *event);
    void start();
    void myUpdate();
    void timerEvent(QTimerEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

signals:

public slots:

private:
    void updateClickedPosition();


private:
    typedef std::vector<CarPtr> Objects_;
    bool mousePressed_;
    b2Vec2 clickedPosition_;
    QPointF oldPosition_;
    b2World world_;
    int timerId_;
    int secTimerId_;
    QTransform transform_;
    Objects_ objects_;
    Ground ground_;
    b2Vec2 size_;
    GeneticAlgorithm genetic_;
};

#endif // WORLD_H
