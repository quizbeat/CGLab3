#include "widget.h"
#include "ui_widget.h"
#include <QVector3D>
#include <ctime>

Widget::Widget(QWidget *parent):QWidget(parent), ui(new Ui::Widget) {
    lastX = 0;
    lastY = 0;
    alpha = 0;
    beta  = 0;
    ui->setupUi(this);
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *) {

}

void Widget::mousePressEvent(QMouseEvent *mEvent) {
    lastX = mEvent->x();
    lastY = mEvent->y();
}

void Widget::mouseMoveEvent(QMouseEvent *mEvent) {
    beta  -= (mEvent->x() - lastX) / 111;
    alpha += (mEvent->y() - lastY) / 111;
    lastX = mEvent->x();
    lastY = mEvent->y();
    update();
}
