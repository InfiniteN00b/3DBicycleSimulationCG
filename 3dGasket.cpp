#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>

int c = 2;
float v[4][3] = {{0,0,1}, {-1, -0.5, 0}, {0, 1, 0}, {1, -0.5, 0}};

void myinit(){
    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

void displayTriangle(float *a, float *b, float *c){
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void divTriangle(float *a, float *b, float *c, int m){
    float v1[3], v2[3], v3[3];
    int i;

    if(m > 0){
        for(i = 0; i < 3; i++){
            v1[i] = (a[i] + b[i]) / 2;
            v2[i] = (a[i] + c[i]) / 2;
            v3[i] = (b[i] + c[i]) / 2;
        }
        divTriangle(a, v1, v2, m - 1);
        divTriangle(v1, b, v3, m - 1);
        divTriangle(v2, v3, c, m - 1);
    }
    else{
        displayTriangle(a, b, c);
    }
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT

    glColor3f(1,1,1);
    divTriangle(v[1], v[2], v[3], c);

    glColor3f(1,0,0);
    divTriangle(v[0], v[1], v[2], c);

    glColor3f(0,1,0);
    divTriangle(v[0], v[2], v[3], c);

    glColor3f(0,0,1);
    divTriangle(v[0], v[1], v[3], c);

    glFlush();
}

int main(int argc, char **argv){
    glutInit( & argc, argv );
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 150);
	// printf("Enter the number of subdivisions:\n");
	// scanf_s("%d", &c);
	myinit();
	glutCreateWindow("3D Recursive Sierpinski Gasket");
	glutDisplayFunc(display);
	glutMainLoop();
    return 0;
}