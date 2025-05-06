#include <GL/glut.h>
#include <cmath>

const GLfloat INITIAL_X = -0.7f, INITIAL_Y = 0.5f;
GLfloat oldx = INITIAL_X, oldy = INITIAL_Y;

void drawKoch(GLfloat dir, GLfloat len, GLint iter) {
    GLdouble dirRad = 0.0174533 * dir;
    GLfloat newX = oldx + len * cos(dirRad);
    GLfloat newY = oldy + len * sin(dirRad);
    
    if (iter == 0) {
        glVertex2f(oldx, oldy);
        glVertex2f(newX, newY);
        oldx = newX;
        oldy = newY;
    } else {
        iter--;
        drawKoch(dir, len, iter);
        dir += 60.0;
        drawKoch(dir, len, iter);
        dir -= 120.0;
        drawKoch(dir, len, iter);
        dir += 60.0;
        drawKoch(dir, len, iter);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // Red color
    
    oldx = INITIAL_X;
    oldy = INITIAL_Y;
    
    drawKoch(0.0, 0.015, 4);
    drawKoch(-120.0, 0.015, 4);
    drawKoch(120.0, 0.015, 4);
    
    glEnd();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SIB50-Koch Snowflake");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
