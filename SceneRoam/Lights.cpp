//
//  Lights.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/6.
//  Copyright © 2016年 Yym. All rights reserved.
//

#include "Lights.hpp"

extern float eye[3];
extern float center[3];


void Lights::setMode(int mode){
    this->mode = mode;
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);
}

void Lights::changeMode(){
    if (mode == 2) {
        setMode(0);
    }
    else{
        setMode(mode + 1);
    }
}


//聚光灯，在屋子正中央向下照射
void Lights::Light0(){
    glEnable(GL_LIGHT0);
    
    float position[] = {0.0, 10.5, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    float color_write[4] = {232.0/255.0f, 220.0/255.0f, 210.0/255.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, color_write);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color_write);
    glLightfv(GL_LIGHT0, GL_SPECULAR, color_write );
    glLightfv(GL_LIGHT0, GL_EMISSION, color_write );
    
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.03f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
    
    float lightDir[3] = {0, -1, 0};
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 0.4f);
    glLightf(GL_LIGHT0,  GL_SPOT_CUTOFF, 90.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);
}


int spin = 0;

void Lights::Light1(){
    glEnable(GL_LIGHT1);

    GLfloat lightDir[] = { 0, -1, 0 };
    GLfloat spotangle = 3;
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat position[] = { 0, 10, 0, 1};
    float diffuse[] = { 0.6, 0.6, 0.6 };
    float specular[] = { 0.8, 0.8, 0.8, 1 };
    
    glPushMatrix();
    spin = (spin + 5) % 360;
    glutPostRedisplay();
    glRotated((GLdouble)spin, 1, 0, 0.0);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);             //设置环境光成分
    glLightfv(GL_LIGHT1, GL_SPECULAR, diffuse);                    //设置镜面光成分
    glLightfv(GL_LIGHT1, GL_DIFFUSE, specular);                     //设置漫射光成分
    glLightfv(GL_LIGHT1, GL_POSITION, position);			//设置聚光灯位置
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotangle);             //裁减角度
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);          //光源方向
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);                    //聚集度
    glPopMatrix();
    
}



//手电，跟随视点
void Lights::torch(){
    glEnable(GL_LIGHT2);
    
    float position[4];
    position[0] = eye[0];
    position[1] = eye[1];
    position[2] = eye[2];
    position[3] = 1.0f;
    
    glLightfv(GL_LIGHT2, GL_POSITION, position);
    
    float color_write[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, color_write);
    glLightfv(GL_LIGHT2, GL_SPECULAR, color_write );
    glLightfv(GL_LIGHT2, GL_EMISSION, color_write );
    
    float lightDir[3];
    lightDir[0] = center[0] - eye[0];
    lightDir[1] = center[1] - eye[1];
    lightDir[2] = center[2] - eye[2];
    
    glLightf(GL_LIGHT2,GL_SPOT_EXPONENT, 10.0f);
    glLightf(GL_LIGHT2,  GL_SPOT_CUTOFF, 20.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDir);
    
}


GLfloat hh = 0;

void Lights::Light3(){
    glEnable(GL_LIGHT3);
    
    hh += 0.1;
    if (hh > 6.28)
        hh = 0;
    
    float position[] = {0.0, 10, 0.0, 1.0};
    glLightfv(GL_LIGHT3, GL_POSITION, position);
    
    float color_write[4] = {134/255.0f, 120/255.0f, 171/255.0f, 1.0f};
    glLightfv(GL_LIGHT3, GL_DIFFUSE, color_write);
    glLightfv(GL_LIGHT3, GL_SPECULAR, color_write );
    glLightfv(GL_LIGHT3, GL_EMISSION, color_write );
    
    float lightDir[3];
    lightDir[0] = 0.6 * sin(hh);
    lightDir[1] = -1;
    lightDir[2] = 0.6 * cos(hh);
    
    glLightf(GL_LIGHT3,GL_SPOT_EXPONENT, 10.0f);
    glLightf(GL_LIGHT3,  GL_SPOT_CUTOFF, 10.0);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightDir);
}



void Lights::on(){
    switch (mode) {
        case 0:
            Light0();
            break;
        case 1:
            Light1();
            Light3();
            break;
        case 2:
            torch();
            break;
        case 3:
            Light3();
            break;
        default:
            break;
    }
    
    sunny();
}


void Lights::sunny(){
    sun.shine();
}




