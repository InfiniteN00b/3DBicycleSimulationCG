#include <GL/glut.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int xx = 10, yy = 10, xend = 100, yend = 100;

void myinit(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 500, -100, 500);
    glMatrixMode(GL_MODELVIEW);
}

void setPixel(int x, int y){
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void BresenhamLine(){
    int dx = abs(xend - xx), dy = abs(yend - yy);
    int p, x, y;
    x = xx; y = yy;
    glColor3f(1, 1, 1);
    glPointSize(5);
    if(dx > dy){
        p = 2 * dy - dx;
        setPixel(x, y);
        while(x < xend){
            x += 1;
            if(p < 0) p += 2 * dy;
            else
                y += 1, p += 2 * (dy - dx);
        }

        setPixel(x, y);
    }
    else{
        p = 2 * dx - dy;
        setPixel(x, y);
        while(y < yend){
            y += 1;
            if(p < 0) p += 2 * dx;
            else
                x += 1, p += 2 * (dx - dy);
        }
        setPixel(x, y);
    }
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT );
    BresenhamLine();
    glFlush();
}

int main(int argc, char **argv){
    glutInit( & argc, argv );
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}