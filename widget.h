#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QDebug>
#include <QMouseEvent>
#include <cmath>

namespace Ui {
	class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

public:
    float lastX, lastY;
    float alpha, beta;
    explicit Widget(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *mEvent);
    virtual void mouseMoveEvent(QMouseEvent *mEvent);
    ~Widget();

private slots:


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H