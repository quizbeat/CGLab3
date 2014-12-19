#include "XGLView.h"

XGLView::XGLView(QWidget *parent) :
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

	FCRValue = 1;
	FCGValue = 0.1;
	FCBValue = 1;

	LCRValue = 1;
	LCGValue = 1;
	LCBValue = 1;

	ACRValue = 1;
	ACGValue = 1;
	ACBValue = 1;

	materialShiness = 10;
	figure = "sphere";
}

QVector3D XGLView::spherePoint(double phi, double psi) {
    QVector3D point;
    point.setX((double)(radius * sin(phi) * cos(psi)));
    point.setY((double)(radius * sin(phi) * sin(psi)));
    point.setZ((double)(radius * cos(phi)));
    return point;
}

QVector3D XGLView::torusPoint(double phi, double psi) {
    QVector3D point;
    point.setX((double)((1 + 0.5 * cos(phi)) * cos(psi)));
    point.setY((double)((1 + 0.5 * cos(phi)) * sin(psi)));
    point.setZ((double)(0.5 * sin(phi)));
    return point;
}

QVector<QVector3D> XGLView::yCharPoint() {
    QVector<QVector3D> yCharPoints;

    yCharPoints.push_back(QVector3D(-0.25, -1, 0.5));
    yCharPoints.push_back(QVector3D(0, -1, 0.5));
    yCharPoints.push_back(QVector3D(0, -1, -0.5));
    yCharPoints.push_back(QVector3D(0, 0, -0.5));
    yCharPoints.push_back(QVector3D(0, 0, 0.5));
    yCharPoints.push_back(QVector3D(0.5, 1, -0.5));
    yCharPoints.push_back(QVector3D(0.5, 1, 0.5));
    yCharPoints.push_back(QVector3D(-0.5, 1, -0.5));
    yCharPoints.push_back(QVector3D(-0.5, 1, 0.5));

    return yCharPoints;
}

void XGLView::addToMassive(QVector <QVector3D> tempPoint, QVector3D normal){
    unsigned long long size = tempPoint.size();
    for(unsigned long long i = 0; i < size; i++) {
        vertex.push_back(tempPoint[i].x());
        vertex.push_back(tempPoint[i].y());
        vertex.push_back(tempPoint[i].z());

        normal.push_back(n.x());
        normal.push_back(n.y());
        normal.push_back(n.z());

        index.push_back(index.size());
    }
}

void XGLView::countSpherePoints() {
    vertex.clear();
    normal.clear();
    index.clear();

    double step_phi = pi / count;
    double step_psi = pi / count * 2;
    double phi = pi/360;
    double psi = 0;

    QVector <QVector3D> tempPoint;
    QVector3D normal;

    for (int i = 0; i < count; phi += step_phi, i++) {
        psi = 0;
        for (int j = 0; j < count; psi += step_psi, j++) {
	        tempPoint.push_back(spherePoint(phi, psi));
	        tempPoint.push_back(spherePoint(phi + step_phi, psi));
	        tempPoint.push_back(spherePoint(phi + step_phi, psi + step_psi));
	        tempPoint.push_back(spherePoint(phi, psi + step_psi));
	        normal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
	        addToMassive(tempPoint, normal);
	        tempPoint.clear();
        }
    }
}

void XGLView::countTorusPoints() {
    vertex.clear();
    normal.clear();
    index.clear();

    double step_phi = pi / count * 2;
    double step_psi = pi / count * 2;
    double phi = pi/360;
    double psi = 0;

    QVector <QVector3D> tempPoint;
    QVector3D normal;

    for(int i = 0; i < count; phi += step_phi, i++) {
        psi = 0;
        for(int j = 0; j < count; psi += step_psi, j++) {
	        tempPoint.push_back(torusPoint(phi, psi));
	        tempPoint.push_back(torusPoint(phi + step_phi, psi));
	        tempPoint.push_back(torusPoint(phi + step_phi, psi + step_psi));
	        tempPoint.push_back(torusPoint(phi, psi + step_psi));
	        normal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
	        addToMassive(tempPoint, normal);
	        tempPoint.clear();
        }
    }
}

void XGLView::countYPoints() {
    vertex.clear();
    normal.clear();
    index.clear();

    QVector <QVector3D> tempY;
    tempY = yPoint();
    QVector <QVector3D> tempPoint;
    QVector3D n;

    tempPoint.push_back(tempY[1]);
    tempPoint.push_back(tempY[2]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[4]);

    normal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, normal);
    tempPoint.clear();

    tempPoint.push_back(tempY[1]);
    tempPoint.push_back(tempY[2]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[4]);

    normal = QVector3D::normal(tempPoint[3] - tempPoint[0], tempPoint[1] - tempPoint[0]);
    addToMassive(tempPoint, normal);
    tempPoint.clear();

    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[5]);
    tempPoint.push_back(tempY[6]);

    normal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, normal);
    tempPoint.clear();

    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[5]);
    tempPoint.push_back(tempY[6]);

    normal = QVector3D::normal(tempPoint[3] - tempPoint[0], tempPoint[1] - tempPoint[0]);
    addToMassive(tempPoint, normal);
    tempPoint.clear();

    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[7]);
    tempPoint.push_back(tempY[8]);

    normal = QVector3D::normal(tempPoint[1] - tempPoint[0], tempPoint[3] - tempPoint[0]);
    addToMassive(tempPoint, normal);

    tempPoint.clear();
    tempPoint.push_back(tempY[4]);
    tempPoint.push_back(tempY[3]);
    tempPoint.push_back(tempY[7]);
    tempPoint.push_back(tempY[8]);

    normal = QVector3D::normal(tempPoint[3] - tempPoint[0], tempPoint[1] - tempPoint[0]);
    addToMassive(tempPoint, normal);
    tempPoint.clear();
}

void XGLView::initializeGL() {

    glClearColor(ACRValue, ACGValue, ACBValue, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    qDebug() << "trueInitialize" << endl;
}

void XGLView::paintGL() {

    if (figure == "sphere") {
       // glEnable(GL_CULL_FACE);
        countSpherePoints();
        glDepthRange (0, 1);
    }
    else if (figure == "torus") {
       // glEnable(GL_CULL_FACE);
        countTorusPoints();
        glDepthRange (1, 0);
    }
    else if (figure == "y") {
        //glDisable(GL_CULL_FACE);
        glDepthRange (1, 0);
        countYPoints();
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

void XGLView::setRXValue(int value) {
	RXValue = (double)value;
	updateGL();
}

void XGLView::setRYValue(int value) {
	RYValue = (double)value;
	updateGL();
}

void XGLView::setRZValue(int value) {
	RZValue = (double)value;
	updateGL();
}

void XGLView::setLPXValue(int value) {
	LPXValue = (float)value;
	updateGL();
}

void XGLView::setLPYValue(int value) {
	LPYValue = (float)value;
	updateGL();
}

void XGLView::setLPZValue(int value) {
	LPZValue = (float)value;
	updateGL();
}

void XGLView::setFCRValue(int value) {
	FCRValue = (float)value / 255;
	updateGL();
}

void XGLView::setFCGValue(int value) {
	FCGValue = (float)value / 255;
	updateGL();
}

void XGLView::setFCBValue(int value) {
	FCBValue = (float)value / 255;
	updateGL();
}

void XGLView::setLCRValue(int value) {
	LCRValue = (float)value / 255;
	updateGL();
}

void XGLView::setLCGValue(int value) {
	LCGValue = (float)value / 255;
	updateGL();
}

void XGLView::setLCBValue(int value) {
	LCBValue = (float)value / 255;
	updateGL();
}

void XGLView::setACRValue(int value) {
	ACRValue = (float)value / 255;
	updateGL();
}

void XGLView::setACGValue(int value) {
	ACGValue = (float)value / 255;
	updateGL();
}

void XGLView::setACBValue(int value) {
	ACBValue = (float)value / 255;
	updateGL();
}

void XGLView::setApproximation(int value) {
	count = value;
	updateGL();
}

void XGLView::changeFigure(QString newFigure) {
	figure = newFigure;
	updateGL();
}