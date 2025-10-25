//
// Created by vasimasr on 25-Oct-25.
//

#ifndef CODING41324_SKETCH_H
#define CODING41324_SKETCH_H


#include <QMainWindow>
#include <QPainter>
#include <qDebug>
#include <QMouseEvent>
#include <QStaticText>
#include <cmath>
#include "Point2D.h"

using namespace std;

class Sketch : public QMainWindow {
    Q_OBJECT
    float mouseX = 0;
    float mouseY = 0;

public:
    explicit Sketch(QMainWindow *parent = nullptr) : QMainWindow(parent) {
        setFixedSize(600, 600);
        setWindowTitle("coding4145");
        QIcon logo = QIcon("E:\\CLionProjects\\GraphicsPrograms\\Graphics\\coding4452345\\img.png");
        setWindowIcon(logo);
        show();
    }
private:
    float x;
    float y;
    float velocity;
    float radius;
    float width;
    float height;
    float distance = 150;
    float penWidth = 1;
    float x1 = 0;
    float y1 = 0;
    float z1 = 0;
    float angle;
    bool setupProgram = true;
    const double PI = 3.141592653589793;
    const double HALF_PI = PI / 2;
    void setup() {
        x = 0;
        y = 0;
        velocity = 0;
        radius = 200;
        width = 600;
        height = 600;
        angle = 0;
    }

    void background(QPainter *drawTool, QColor color) {
        drawTool->setPen(Qt::NoPen);
        QBrush backgroundColor;
        backgroundColor.setColor(color);
        backgroundColor.setStyle(Qt::SolidPattern);
        drawTool->setBrush(backgroundColor);
        drawTool->drawRect(-width / 2, -height / 2, width, height);
    }

    float zx(float x, float z) {
        return  x / (1 + z / distance);
    }

    float zy(float y, float z) {
        return y / (1 + z / distance);
    }

    void strokeWeight(float width) {
        penWidth = width;
    }

    void rotateX(float x, float y, float z, float a) {
        x1 = x;
        y1 = y * cos(a) - z * sin(a);
        z1 = y * sin(a) + z * cos(a);
    }
    void rotateY(float x, float y, float z, float a) {
        x1 = x * cos(a) + z * sin(a);
        y1 = y;
        z1 = -x * sin(a) + z * cos(a);
    }
    void rotateZ(float x, float y, float z, float a) {
        x1 = x * cos(a) - y * sin(a);
        y1 = x * sin(a) + y * cos(a);
        z1 = z;
    }

    void stroke(QPainter *drawTool, float r, float g, float b) {
        QPen pen;
        pen.setColor(QColor(r, g, b));
        pen.setWidth(penWidth);
        drawTool->setPen(pen);
    }

    void fill(QPainter *drawTool, float r, float g, float b) {
        drawTool->setBrush(QColor(r, g, b));
    }

    void point(QPainter *drawTool, float x, float y, float z) {
        const auto *point = new Point2D(zx(x, z), zy(y, z));
        drawTool->drawPoint(point->x, point->y);
    }

    void box(QPainter *drawTool, float extents) {
        rotateX(extents, extents, extents, angle);
        rotateY(x1, y1, z1, angle);
        rotateZ(x1, y1, z1, angle);
        point(drawTool, x1, y1, z1);
        rotateX(-extents, extents, extents, angle);
        rotateY(x1, y1, z1, angle);
        rotateZ(x1, y1, z1, angle);
        point(drawTool, x1, y1, z1);
        rotateX(extents, -extents, extents, angle);
        rotateY(x1, y1, z1, angle);
        rotateZ(x1, y1, z1, angle);
        point(drawTool, x1, y1, z1);
        rotateX(-extents, -extents, extents, angle);
        rotateY(x1, y1, z1, angle);
        rotateZ(x1, y1, z1, angle);
        point(drawTool, x1, y1, z1);
        rotateX(extents, extents, -extents, angle);
        rotateY(x1, y1, z1, angle);
        rotateZ(x1, y1, z1, angle);
        point(drawTool, x1, y1, z1);
        rotateX(extents, -extents, -extents, angle);
        rotateY(x1, y1, z1, angle);
        rotateZ(x1, y1, z1, angle);
        point(drawTool, x1, y1, z1);
        rotateX(-extents, extents, -extents, angle);
        rotateY(x1, y1, z1, angle);
        rotateZ(x1, y1, z1, angle);
        point(drawTool, x1, y1, z1);
        rotateX(-extents, -extents, -extents, angle);
        rotateY(x1, y1, z1, angle);
        rotateZ(x1, y1, z1, angle);
        point(drawTool, x1, y1, z1);
    }

    float map(float value, float mini1, float max1, float mini2, float max2) {
        float mapped = mini2 + (value - mini1) * (max2 - mini2) / mini2 - mini1;
        return mapped;
    }

    void sphere(QPainter *drawTool, float radius, int res) {
        for (int i = 0; i < res; i++) {
            float lat = map(i, 0, res, -HALF_PI, HALF_PI);
            for (int j = 0; j < res; j++) {
                float lon = map(j, 0, res, -PI, PI);
                float x = radius * sin(lon) * cos(lat);
                float y = radius * sin(lon) * sin(lat);
                float z = radius * cos(lon);
                rotateX(x, y, z, angle);
                rotateY(x1, y1, z1, angle);
                rotateZ(x1, y1, z1, angle);
                strokeWeight(1);
                stroke(drawTool, 0, 255, 0);
                point(drawTool, x1, y1, z1);
            }
        }
        strokeWeight(4);
    }

    void draw(QPainter *drawTool) {
        // background
        background(drawTool, Qt::black);
        sphere(drawTool, 130, 130);
        angle += 0.001;
    }
    void paintEvent(QPaintEvent *) override {
        QPainter drawTool(this);
        drawTool.save();
        drawTool.translate(width / 2, height / 2);
        if (setupProgram) {
            setup();
            setupProgram = false;
        }
        draw(&drawTool);
        drawTool.restore();
        update();
    }
    void mousePressEvent(QMouseEvent * mouse ) override {
        QPoint mousePoint = mouse->pos();
        mouseX = mousePoint.x();
        mouseY = mousePoint.y();
        qDebug() << mouseX << " " << mouseY;
        repaint();
    }
    void mouseMoveEvent(QMouseEvent* mouse) override {
        QPoint mousePoint = mouse->pos();
        mouseX = mousePoint.x();
        mouseY = mousePoint.y();
        qDebug() << mouseX << " " << mouseY;
        update();
        repaint();
    }
};


#endif //CODING41324_SKETCH_H