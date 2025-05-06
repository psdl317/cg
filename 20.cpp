#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;
bool flag=true;
int xc,yc,r;
void drawCircle(int xc,int yc,int radius)
{
    int x=0;
    int y=radius;

    int p=3-2*radius;
    while(x<=y)
    {
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex2i(xc+x,yc+y);
        glVertex2i(xc+y,yc+x);
        glVertex2i(xc-x,yc+y);
        glVertex2i(xc-y,yc+x);
        glVertex2i(xc-x,yc-y);
        glVertex2i(xc-y,yc-x);
        glVertex2i(xc+x,yc-y);
        glVertex2i(xc+y,yc-x);
        glEnd();
        if(p<0)
        {
            x++;
            p=p+4*x+6;
        }
        if(p>=0)
        {
            x++;
            y--;
            p=p+4*(x-y)+10;
        }

    }
    glFlush();
}



void myDisplay() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

}
void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (flag == true) {
           xc=x;
           yc=600-y;
           flag=false;

        }
        else
        {
            r=abs(xc-x);
              glColor3f(0,0,0);
        drawCircle(xc, yc, r);// black circle
     glColor3f(0,0,1);
       drawCircle(xc-2*r-20,yc,r);//blue circle
       glColor3f(1,0,0);
       drawCircle(xc+2*r+20,yc,r);//red circle
       glColor3f(0,1,0);
       drawCircle(xc+r+10,yc-r,r);//green circle
       glColor3f(1,1,0);
       drawCircle(xc-r-10,yc-r,r);//yellow circle

cout<<xc<<" "<<yc<<" "<<r;

       // flag = false;
        glFlush();

        }
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Olympic Circles");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return (0);
}

