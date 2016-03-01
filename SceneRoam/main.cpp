//
//  main.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/21.
//  Copyright © 2015年 Yym. All rights reserved.
//



#include <iostream>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include "LoadTexture.hpp"
#include "ViewPortCtrl.hpp"
#include "Models.hpp"
#include "Collision.hpp"
#include "Lights.hpp"
#include "RoamPath.hpp"


using namespace std;


extern float eye[3];
extern float center[3];
extern bool roaming;
extern double finalPath[500000][7];
extern int currentRoam;
extern int finalPathTot;
extern bool bAnim;

extern Sun sun;

void idle()
{
    glutPostRedisplay();
}

Lights lights;


void redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    lights.on();

    glShadeModel(GL_SMOOTH);
    
    drawScene();
    
    if (roaming) {
        center[0]=finalPath[currentRoam][0];
        center[1]=finalPath[currentRoam][1];
        center[2]=finalPath[currentRoam][2];
        eye[0]=finalPath[currentRoam][3];
        eye[1]=finalPath[currentRoam][4];
        eye[2]=finalPath[currentRoam][5];
        angle=finalPath[currentRoam][6];
        currentRoam++;
        if (currentRoam>=finalPathTot) {
            currentRoam=0;
        }
    }
    
    if (bAnim) {
        GLdouble dis = sqrt(pow((eye[0] - center[0]), 2) + pow((eye[2] - center[2]),2));
        GLdouble x0 = (center[0] - eye[0]);
        GLdouble z0 = (center[2] - eye[2]);
        GLdouble tan0 = z0 / x0;
    
        
        GLdouble angle = atan(tan0);
        
        if (x0 < 0)
            angle += 3.14;
        
        angle += 0.7 * 3.14 / 180;
        GLdouble x1 = dis * cos(angle);
        GLdouble z1 = dis * sin(angle);
        center[0] = eye[0] + x1;
        center[2] = eye[2] + z1;
    }
    
    getFPS();
    
    glutSwapBuffers();
}


void init(){
    initModels();
    genRoamInRoom();
}


int main (int argc,  char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640,640);
    int windowHandle = glutCreateWindow("Simple GLUT App");
    
    init();
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    
    
    glutMouseFunc(Mouse);
    glutMotionFunc(OnMouseMove);
    
    glutMainLoop();
    return 0;
}


