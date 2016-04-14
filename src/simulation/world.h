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

class World : public QWidget
{
    Q_OBJECT
public:
    explicit World(b2Vec2 gravity, QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);
    void start();
    void timerEvent(QTimerEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

signals:

public slots:


private:
    bool mousePressed_;
    QPointF oldPosition_;
    b2World world_;
    int timerId_;
    QTransform transform_;
    std::vector<Object*> objects_;
};

#endif // WORLD_H
