#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PERLIN_H
#include "perlin.h"

float w = 300, h = 150;
float scale = 2.0f;

float z[300][150];

float fly = 0;

void renderScene(){
    float x, y;

    float xoff = fly;
    for(y = 0; y < h; y++){
        float yoff = 0;
        for(x = 0; x < w; x++){
            z[(int)x][(int)y] = map(perlin2d(xoff, yoff, 0.1, 5), 0, 1, -50, 40);
            yoff += 0.1;
        }
        xoff += 0.1;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-w, -30.0, -30.0f);
    glRotatef(-60.0, 1.0, 0.0, 0.0);

    for(y = 0; y < h; y++){
        glBegin(GL_TRIANGLE_STRIP);
            for(x = 0; x < w; x++){
                /*if(z[(int)x][(int)y] < 0){
                    glColor3f(0.0, 0.5, 0.5);
                }else if( z[(int)x][(int)y] >= 0 && z[(int)x][(int)y]<= 20){
                    glColor3f(0.5, 0.5, 0.15);
                }else{
                    glColor3f(1.0, 1.0, 1.0);
                }*/
                glColor3f(0.1, 1.0, 0.1);
                glVertex3f(x*scale, y*scale, z[(int)x][(int)y]);
                glVertex3f(x*scale, (y-1)*scale, z[(int)x][(int)(y-1)]);
            }
        glEnd();
    }

    fly+=0.1;

    glutSwapBuffers();
}

void specialKey(int key, int x, int y){
    switch(key){
        case 27:
            exit(1);
            break;
    }
    glutPostRedisplay();
}

void setup(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    srand(time(NULL));


    glLineWidth(2);
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
}

void framebuffer_size_callback(int w, int h){

    GLfloat aspectRatio;
    GLfloat canvasSize = 600.0f;

    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (float) w / (float) h;

    gluPerspective(65.0, aspectRatio, 0.1, canvasSize);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timerFunction(int val){
    glutPostRedisplay();

    glutTimerFunc(10,timerFunction,1);
}
int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutCreateWindow("SimpleTerrainGenerator");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(framebuffer_size_callback);
    glutSpecialFunc(specialKey);
    glutTimerFunc(10,timerFunction,1);

    setup();

    glutMainLoop();

    return 0;
}
