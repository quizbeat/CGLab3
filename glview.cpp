#include "GLView.h"
#define pi 3.1415

GLView::GLView(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	radius = 1;
    count = 20;

	RXValue = 0;
	RYValue = 0;
	RZValue = 0;

	LPXValue = 2;
	LPYValue = 0;
	LPZValue = 10;

    FCRValue = 0;
    FCGValue = 0;
    FCBValue = 1;

	LCRValue = 1;
	LCGValue = 1;
	LCBValue = 1;

    ACRValue = 0;
    ACGValue = 0;
    ACBValue = 0;

    figure = "Sphere";
}

QVector3D GLView::spherePoint(double phi, double psi) {
    QVector3D point;
    point.setX((double)(radius * sin(phi) * cos(psi)));
    point.setY((double)(radius * sin(phi) * sin(psi)));
    point.setZ((double)(radius * cos(phi)));
    return point;
}

QVector3D GLView::torusPoint(double phi, double psi) {
    QVector3D point;
    point.setX((double)((1 + 0.5 * cos(phi)) * cos(psi)));
    point.setY((double)((1 + 0.5 * cos(phi)) * sin(psi)));
    point.setZ((double)(0.5 * sin(phi)));
    return point;
}

QVector<QVector3D> GLView::yCharPoint() {
    QVector<QVector3D> yCharPoints;

    yCharPoints.push_back(QVector3D(0, 0, 0));

    yCharPoints.push_back(QVector3D(-0.25, -1, 0.25)); // 1
    yCharPoints.push_back(QVector3D(0.25, -1, 0.25));  // 2
    yCharPoints.push_back(QVector3D(0.25, 0, 0.25));   // 3
    yCharPoints.push_back(QVector3D(-0.25, 0, 0.25));  // 4
    yCharPoints.push_back(QVector3D(0.25, -1, -0.25)); // 5
    yCharPoints.push_back(QVector3D(0.25, 0, -0.25));  // 6
    yCharPoints.push_back(QVector3D(-0.25, -1, -0.25));// 7
    yCharPoints.push_back(QVector3D(-0.25, 0, -0.25)); // 8

    yCharPoints.push_back(QVector3D(0.75, 1, 0.25));   // 9
    yCharPoints.push_back(QVector3D(0.75, 1, -0.25));  // 10
    yCharPoints.push_back(QVector3D(0.25, 1, -0.25));  // 11
    yCharPoints.push_back(QVector3D(0.25, 1, 0.25));   // 12

    yCharPoints.push_back(QVector3D(-0.25, 1, 0.25));  // 13
    yCharPoints.push_back(QVector3D(-0.25, 1, -0.25)); // 14
    yCharPoints.push_back(QVector3D(-0.75, 1, -0.25)); // 15
    yCharPoints.push_back(QVector3D(-0.75, 1, 0.25));  // 16

    return yCharPoints;
}

void GLView::addToMassive(QVector <QVector3D> tempPoint, QVector3D tempNormal){
    unsigned long long size = tempPoint.size();
    for(unsigned long long i = 0; i < size; i++) {
        vertex.push_back(tempPoint[i].x());
        vertex.push_back(tempPoint[i].y());
        vertex.push_back(tempPoint[i].z());

        normal.push_back(tempNormal.x());
        normal.push_back(tempNormal.y());
        normal.push_back(tempNormal.z());

        index.push_back(index.size());
    }
}

void GLView::countSpherePoints() {
    vertex.clear();
    normal.clear();
    index.clear();

    double step_phi = pi / count;
    double step_psi = pi / count * 2;
    double phi = pi/360;
    double psi = 0;

    QVector <QVector3D> tempPoint;
    QVector3D tempNormal;

    for (int i = 0; i < count; phi += step_phi, i++) {
        psi = 0;
        for (int j = 0; j < count; psi += step_psi, j++) {
	        tempPoint.push_back(spherePoint(phi, psi));
	        tempPoint.push_back(spherePoint(phi + step_phi, psi));
	        tempPoint.push_back(spherePoint(phi + step_phi, psi + step_psi));
	        tempPoint.push_back(spherePoint(phi, psi + step_psi));
            tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
            addToMassive(tempPoint, tempNormal);
	        tempPoint.clear();
        }
    }
}

void GLView::countTorusPoints() {
    vertex.clear();
    normal.clear();
    index.clear();

    double step_phi = pi / count * 2;
    double step_psi = pi / count * 2;
    double phi = pi/360;
    double psi = 0;

    QVector <QVector3D> tempPoint;
    QVector3D tempNormal;

    for(int i = 0; i < count; phi += step_phi, i++) {
        psi = 0;
        for(int j = 0; j < count; psi += step_psi, j++) {
	        tempPoint.push_back(torusPoint(phi, psi));
	        tempPoint.push_back(torusPoint(phi + step_phi, psi));
	        tempPoint.push_back(torusPoint(phi + step_phi, psi + step_psi));
	        tempPoint.push_back(torusPoint(phi, psi + step_psi));
            tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
            addToMassive(tempPoint, tempNormal);
	        tempPoint.clear();
        }
    }
}

void GLView::countYCharPoints() {
    vertex.clear();
    normal.clear();
    index.clear();

    QVector <QVector3D> tempY;
    tempY = yCharPoint();
    QVector <QVector3D> tempPoint;
    QVector3D tempNormal;


    /*  down  */
    tempPoint.push_back(tempY[1]);
    tempPoint.push_back(tempY[2]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[4]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[2]);
    tempPoint.push_back(tempY[5]);
    tempPoint.push_back(tempY[6]);
    tempPoint.push_back(tempY[3]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[5]);
    tempPoint.push_back(tempY[7]);
    tempPoint.push_back(tempY[8]);
    tempPoint.push_back(tempY[6]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[7]);
    tempPoint.push_back(tempY[1]);
    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[8]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[7]);
    tempPoint.push_back(tempY[5]);
    tempPoint.push_back(tempY[2]);
    tempPoint.push_back(tempY[1]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    /*  left  */
    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[13]);
    tempPoint.push_back(tempY[16]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[6]);
    tempPoint.push_back(tempY[14]);
    tempPoint.push_back(tempY[13]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[6]);
    tempPoint.push_back(tempY[8]);
    tempPoint.push_back(tempY[15]);
    tempPoint.push_back(tempY[14]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[8]);
    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[16]);
    tempPoint.push_back(tempY[15]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[16]);
    tempPoint.push_back(tempY[13]);
    tempPoint.push_back(tempY[14]);
    tempPoint.push_back(tempY[15]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    /*  right  */
    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[9]);
    tempPoint.push_back(tempY[12]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[6]);
    tempPoint.push_back(tempY[10]);
    tempPoint.push_back(tempY[9]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[6]);
    tempPoint.push_back(tempY[8]);
    tempPoint.push_back(tempY[11]);
    tempPoint.push_back(tempY[10]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[8]);
    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[12]);
    tempPoint.push_back(tempY[11]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();


    tempPoint.push_back(tempY[12]);
    tempPoint.push_back(tempY[9]);
    tempPoint.push_back(tempY[10]);
    tempPoint.push_back(tempY[11]);
    tempNormal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, tempNormal);
    tempPoint.clear();
}

void GLView::initializeGL() {

    glClearColor(ACRValue, ACGValue, ACBValue, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

}

void GLView::paintGL() {

    if (figure == "Sphere") {
        countSpherePoints();
        glDepthRange (0, 1);
    }
    else if (figure == "Torus") {
        countTorusPoints();
        glDepthRange (1, 0);
    }
    else if (figure == "Ychar") {
        glDepthRange (0, 1);
        countYCharPoints();
    }

    glClearColor(ACRValue, ACGValue, ACBValue, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,-2,2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat lightPosition[4] = {LPXValue, LPYValue, LPZValue, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat lightColor[4] = {LCRValue, LCGValue, LCBValue, 1};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

    GLfloat ambientColor[4] = {ACRValue, ACGValue, ACBValue, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);

    GLfloat materialColor[4] = {FCRValue, FCGValue, FCBValue, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialColor);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glRotatef(-RXValue, 1, 0, 0);
    glRotatef( RYValue, 0, 1, 0);
    glRotatef(-RZValue, 0, 0, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex.data());
    glNormalPointer(GL_FLOAT, 0, normal.data());

    glDrawElements(GL_QUADS, index.size(), GL_UNSIGNED_INT, index.data());
}

void GLView::resizeGL(int width, int height){
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}



void GLView::setRXValue(int value) {
	RXValue = (double)value;
	updateGL();
}

void GLView::setRYValue(int value) {
	RYValue = (double)value;
	updateGL();
}

void GLView::setRZValue(int value) {
	RZValue = (double)value;
	updateGL();
}

void GLView::setLPXValue(int value) {
	LPXValue = (float)value;
	updateGL();
}

void GLView::setLPYValue(int value) {
	LPYValue = (float)value;
	updateGL();
}

void GLView::setLPZValue(int value) {
	LPZValue = (float)value;
	updateGL();
}

void GLView::setFCRValue(int value) {
	FCRValue = (float)value / 255;
	updateGL();
}

void GLView::setFCGValue(int value) {
	FCGValue = (float)value / 255;
	updateGL();
}

void GLView::setFCBValue(int value) {
	FCBValue = (float)value / 255;
	updateGL();
}

void GLView::setLCRValue(int value) {
	LCRValue = (float)value / 255;
	updateGL();
}

void GLView::setLCGValue(int value) {
	LCGValue = (float)value / 255;
	updateGL();
}

void GLView::setLCBValue(int value) {
	LCBValue = (float)value / 255;
	updateGL();
}

void GLView::setACRValue(int value) {
	ACRValue = (float)value / 255;
	updateGL();
}

void GLView::setACGValue(int value) {
	ACGValue = (float)value / 255;
	updateGL();
}

void GLView::setACBValue(int value) {
	ACBValue = (float)value / 255;
	updateGL();
}

void GLView::setApproximation(int value) {
	count = value;
	updateGL();
}

void GLView::changeFigure(QString newFigure) {
	figure = newFigure;
	updateGL();
}
