#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

const int WINDOW_SIZE = 800;

struct Point {
    double x, y;
};

Point controlPoints[3] = {{200, 200}, {300, 450}, {500, 150}};
int numControlPoints = 3;
int pointToBeChanged = 2;

void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawControlPoints() {
    glColor3f(1.0, 1.0, 0.0);
    glPointSize(3);
    for (int i = 0; i < numControlPoints; i++) {
        drawPoint(controlPoints[i].x, controlPoints[i].y);
    }
}

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int combination(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

double bezierBlendingFunc(double t, int n, int k) {
    return combination(n, k) * pow(t, k) * pow(1 - t, n - k);
}

void drawBezierCurve() {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1);
    
    for (double t = 0.0; t <= 1.0; t += 0.001) {
        double x = 0, y = 0;
        for (int i = 0; i < numControlPoints; i++) {
            double blend = bezierBlendingFunc(t, numControlPoints - 1, i);
            x += blend * controlPoints[i].x;
            y += blend * controlPoints[i].y;
        }
        drawPoint(static_cast<int>(x), static_cast<int>(y));
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, WINDOW_SIZE, 0, WINDOW_SIZE);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawControlPoints();
    drawBezierCurve();
    glFlush();
}

void mouseHandler(int button, int action, int xMouse, int yMouse) {
    if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
        controlPoints[pointToBeChanged].x = xMouse;
        controlPoints[pointToBeChanged].y = WINDOW_SIZE - yMouse;
        glutPostRedisplay();
    }
}

void keyboardHandler(unsigned char key, int xMouse, int yMouse) {
    if (isdigit(key)) {
        int index = key - '1';
        if (index >= 0 && index < numControlPoints) {
            pointToBeChanged = index;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SIB50-Bezier Curve");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardHandler);
    glutMouseFunc(mouseHandler);
    glutMainLoop();
    return 0;
}
