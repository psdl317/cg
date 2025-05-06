#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void displayPoint(int x, int y)
{
    glColor3f(0, 1, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void SimpleLine(float x1, float y1, float x2, float y2)
{
    float dx, dy, p;
    int i;
    float incx, incy, inc1, inc2;
    float x, y;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    incx = (x2 < x1) ? -1 : 1;
    incy = (y2 < y1) ? -1 : 1;

    x = x1;
    y = y1;

    if (dx > dy)
    {
        p = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i <= dx; i++)
        {
            displayPoint(x, y);
            if (p >= 0)
            {
                x += incx;
                y += incy;
                p += inc1;
            }
            else
            {
                x += incx;
                p += inc2;
            }
        }
    }
    else
    {
        p = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i <= dy; i++)
        {
            displayPoint(x, y);
            if (p >= 0)
            {
                x += incx;
                y += incy;
                p += inc1;
            }
            else
            {
                y += incy;
                p += inc2;
            }
        }
    }
    glFlush();
}

void myMouse(int button, int state, int x, int y)
{
    static int xst, yst, pt = 0;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (pt == 0)
        {
            xst = x;
            yst = 600 - y;
            pt = 1;
        }
        else
        {
            SimpleLine(xst, yst, x, 600 - y);
            xst = x;
            yst = 600 - y;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        pt = 0; // reset drawing
    }
}

void initialize(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 600, 0, 600);
}

void primitives(void)
{
    glColor3f(1, 0, 0);
    glutMouseFunc(myMouse); // bind mouse function here
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bresenham's Line Drawing");
    initialize();
    glutDisplayFunc(primitives);
    glutMainLoop();
    return 0;
}
