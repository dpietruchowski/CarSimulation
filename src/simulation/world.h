#ifndef WORLD_H
#define WORLD_H

#include <QtGui>
#include <QtOpenGL>
#include <QWidget>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QPushButton>
#include <Box2D/Box2D.h>
#include <vector>

#include "object.h"
#include "car.h"
#include "ground.h"
#include "buffer.h"
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
    void showUpdate();
    void timerEvent(QTimerEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

signals:

public slots:
    void forward(bool);

private:
    typedef std::vector<CarPtr> Objects_;
    void updateClickedPosition();
    void killObject(Objects_::iterator &it);
    void createObject();


private:
    QPushButton *forward_;
    bool mousePressed_;
    b2Vec2 clickedPosition_;
    QPointF oldPosition_;
    b2World world_;
    Objects_ objects_;
    Ground ground_;
    b2Vec2 size_;
    GeneticAlgorithm genetic_;
    // interval must be "wielokrotnoscia" 1000/60 (60 fps) because
    // car time alive is counted by that
    double interval_;
    Buffer buffer_;
    int worldTimerId_;
    int createTimerId_;
    int drawTimerId_;
    QTransform transform_;
};

#endif // WORLD_H
