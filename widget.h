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
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
