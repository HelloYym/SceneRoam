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
#include "ObjModel.hpp"
#include "DoorModel.hpp"
#include "MonitorModel.hpp"
#include "Nurbs.hpp"
using namespace std;


ObjModel Woman;
ObjModel Apple;
ObjModel Dumbbell;
ObjModel Ball;
ObjModel iPad;
ObjModel City;

DoorModel Door;
MonitorModel Monitor;


float fTranslate;
float fRotate;
float fScale  = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;


int wHeight = 0;
int wWidth = 0;


GLuint WallList;



void texSolidCube(){
    
    
    GLuint FloorTexture, WallTexture;
    
    glGenTextures(1, &FloorTexture);
    glGenTextures(1, &WallTexture);
    texload(FloorTexture, "Floor.bmp");
    texload(WallTexture, "Wall.bmp");
    
    //glColor3f(199/255.0f, 255/255.0f, 236/255.0f);
    
    
    
    float color[4] = {199/255.0f, 255/255.0f, 236/255.0f, 1.0f};
    float high_shininess = 20.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.1f);
    
    float low_shininess = 1.0f;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, WallTexture);  //选择纹理texture[0]
    
    glPushMatrix();
    glBegin(GL_QUADS);
    
    glTexCoord2i(0, 0);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2i(1, 0);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2i(1, 1);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex3f(-1.0, -1.0, 1.0);
    
    //    glTexCoord2i(0, 0);
    //    glVertex3f(-1.0, -1.0, -1.0);
    //    glTexCoord2i(1, 0);
    //    glVertex3f(1.0, -1.0, -1.0);
    //    glTexCoord2i(1, 1);
    //    glVertex3f(1.0, 1.0, -1.0);
    //    glTexCoord2i(0, 1);
    //    glVertex3f(-1.0, 1.0, -1.0);
    
    
    glTexCoord2i(0, 0);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2i(1, 0);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2i(1, 1);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex3f(1.0, -1.0, 1.0);
    
    glTexCoord2i(0, 0);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2i(1, 0);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2i(1, 1);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex3f(-1.0, 1.0, 1.0);
    
    glTexCoord2i(0, 0);
    glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2i(1, 0);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2i(1, 1);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex3f(-1.0, 1.0, 1.0);
    
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);	//关闭纹理texture[0]
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, FloorTexture);  //选择纹理texture[0]
    
    glPushMatrix();
    glBegin(GL_QUADS);
    
    
    GLfloat divide = 20;
    GLfloat unit = 2 / divide;
    for (int i = 0; i < divide; i++)
        for (int j = 0; j < divide; j++){
            GLfloat x0 = unit * i - 1.0;
            GLfloat z0 = unit * j - 1.0;
            glTexCoord2i(0, 0);
            glVertex3f(x0, -1.0, z0);
            glTexCoord2i(1, 0);
            glVertex3f(x0 + unit, -1.0, z0);
            glTexCoord2i(1, 1);
            glVertex3f(x0 + unit, -1.0, z0 + unit);
            glTexCoord2i(0, 1);
            glVertex3f(x0, -1.0, z0 + unit);
        }
    
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);	//关闭纹理texture[0]
}

Nurbs NurbsSurface;

void Draw_Scene()
{
    
    float color[4] = {134/255.0f, 120/255.0f, 171/255.0f, 1.0f};
    float high_shininess = 20.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
    
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    //    glPushMatrix();
    //    glTranslatef(1, 1, 1);
    //    glRotated(90, 1, 0, 0);
    //    gluDisk(quadric, 2, 0, 200, 200);
    //    gluCylinder(quadric, 0, 2, 3, 200, 200);
    //    glPopMatrix();
    
    gluDeleteQuadric(quadric);
    
    
    
    NurbsSurface.drawSurface();
    
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    glCallList(WallList);
    
    Woman.draw();
    Dumbbell.draw();
    Apple.draw();
    Ball.draw();
    iPad.draw();
    City.draw();
    Door.draw();
    Monitor.draw();
}



void updateView(int width, int height)
{
    glViewport(0,0,width,height);						// Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width/(GLfloat)height;
    
    //    if (bPersp) {
    gluPerspective(80.0f, whRatio,0.1f,300.0f);
    //    } else {
    //        glOrtho(-3 ,3, -3, 3,-100,100);
    //    }
    
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }
    
    wHeight = height;
    wWidth = width;
    updateView(wHeight, wWidth);
}


void idle()
{
    glutPostRedisplay();
}


float eye[] = {0, 0, 5};
float center[] = {0, 0, 0};


void key(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; break; }
            
        case ' ': {bAnim = !bAnim; break;}
        case 'o': {bWire = !bWire; break;}
            
        case 'a': {
            eye[0] -= 1.5f;
            center[0] -= 1.5f;
            break;
        }
        case 'd': {
            eye[0] += 1.5f;
            center[0] += 1.5f;
            break;
        }
        case 'w': {
            eye[1] += 1.5f;
            center[1] += 1.5f;
            break;
        }
        case 's': {
            eye[1] -= 1.5f;
            center[1] -= 1.5f;
            break;
        }
        case 'z': {
            eye[2] -= 1.5f;
            center[2] -= 1.5f;
            break;
        }
        case 'c': {
            eye[2] += 1.5f;
            center[2] += 1.5f;
            break;
        }
            
        case 'u': {
            if (Door.isOpen())
                Door.close();
            else
                Door.open();
            break;
        }
            
    }
    
    updateView(wHeight, wWidth);
}



void Light0(){
    float position[] = {0.0, 3.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    float color_write[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, color_write);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color_write);
    glLightfv(GL_LIGHT0, GL_SPECULAR, color_write );
    glLightfv(GL_LIGHT0, GL_EMISSION, color_write );
    
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.03f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
    
    glEnable(GL_LIGHT0);
}


void Light1(){
    float position[] = {0.0, 100.0, 0.0, 0.0};
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    
    float color_write[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_AMBIENT, color_write);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color_write);
    glLightfv(GL_LIGHT1, GL_SPECULAR, color_write );
    glLightfv(GL_LIGHT1, GL_EMISSION, color_write );
    
    glEnable(GL_LIGHT1);
}




void redraw()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();									// Reset The Current Modelview Matrix
    
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
    
    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    Light0();
    //Light1();
    
    glRotatef(fRotate, 0, 1.0f, 0);
    
    glShadeModel(GL_SMOOTH);
    
    Draw_Scene();
    
    if (bAnim) fRotate += 0.4f;
    glutSwapBuffers();
}





void init(){
    NurbsSurface.init();
    
    Dumbbell.loadOBJ("Models/Dumbbell", "Dumbbell.obj");
    Dumbbell.unitize();
    Dumbbell.setPosition(5, -3 - Dumbbell.getArea().y, 0);
    
    Ball.loadOBJ("Models/Ball", "Ball.obj");
    Ball.unitize();
    Ball.setPosition(-5, -3 - Ball.getArea().y, 5);
    
    iPad.loadOBJ("Models/iPad", "iPad.obj");
    iPad.unitize();
    iPad.setPosition(-3, -3 - iPad.getArea().y, 0);
    
    Woman.loadOBJ("Models/test", "test.obj");
    Woman.unitize();
    Woman.setPosition(-5, -3 - Woman.getArea().y, -5);
    
    Apple.loadOBJ("Models/Apple", "Apple.obj");
    Apple.unitize();
    Apple.setPosition(5, -3 - Apple.getArea().y, -5);
    
    City.loadOBJ("Models/City", "City.obj");
    City.setPosition(0, -15 - City.getArea().y, -126);
    
    
    Monitor.loadOBJ("Models/Monitor", "Monitor.obj");
    Monitor.unitize();
    Monitor.setVideo("screen", 7, "video");
    Monitor.play();
    Monitor.setPosition(2, -3 - Monitor.getArea().y, 0);
    
    Door.loadOBJ("Models/Door", "Door.obj");
    Door.unitize();
    Door.setPosition(0, -3 - Door.getArea().y, 0);
    
    WallList = glGenLists(1);
    glNewList(WallList, GL_COMPILE);
    glPushMatrix();
    glScalef(10, 3, 10);
    texSolidCube();
    glPopMatrix();
    glEndList();
    
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
    
    
    glutMainLoop();
    return 0;
}


