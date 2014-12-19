#ifndef GLVIEW_H
#define GLVIEW_H

#include <QWidget>
#include <QGLWidget>
#include <QVector3D>
#include <QVector>
#include <QDebug>

class GLView : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLView(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void addToMassive(QVector <QVector3D> tempPoint, QVector3D n);

    QVector3D spherePoint(double phi, double psi);
    void countSpherePoints();

    QVector3D torusPoint(double phi, double psi);
    void countTorusPoints(); 

    QVector <QVector3D> yCharPoint();
    void countYCharPoints(); 

private:
    QVector<GLfloat> vertex;
    QVector<GLfloat> normal;
    QVector<GLuint> index; 

    float RXValue; // RotationXValue
    float RYValue;
    float RZValue;

    float LPXValue; // LightPositionXValue
    float LPYValue;
    float LPZValue;

    float FCRValue; // FigureColorRValue
    float FCGValue;
    float FCBValue;

    float LCRValue; // LightColorRValue
    float LCGValue;
    float LCBValue;

    float ACRValue; // AmbientColorRValue
    float ACGValue;
    float ACBValue;

    double radius;
    double count;

    QString figure;

signals:

public slots:
    void setRXValue(int value);
    void setRYValue(int value);
    void setRZValue(int value);

    void setLPXValue(int value);
    void setLPYValue(int value);
    void setLPZValue(int value);

    void setFCRValue(int value);
    void setFCGValue(int value);
    void setFCBValue(int value);

    void setLCRValue(int value);
    void setLCGValue(int value);
    void setLCBValue(int value);

    void setACRValue(int value);
    void setACGValue(int value);
    void setACBValue(int value);

    void setApproximation(int value);

    void changeFigure(QString newFigure);

};

#endif // GLVIEW_H
