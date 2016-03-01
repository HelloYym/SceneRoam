//
//  ViewPortCtrl.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/5.
//  Copyright © 2016年 Yym. All rights reserved.
//

#include "ViewPortCtrl.hpp"

extern DoorModel Door;

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

bool bNurbs = false;

int wHeight = 0;
int wWidth = 0;

double angle=0;
float eye[] = {0, 4, 0};
float center[] = {0, 4, -1};

bool roaming = false;
int currentRoam;


void getFPS() {
    static int frame = 0, time, timebase = 0;
    static char buffer[256];
    
    char mode[64];
    
    strcpy(mode, "");
    
    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        sprintf(buffer,"FPS:%4.2f %s",
                frame*1000.0/(time-timebase), mode);
        timebase = time;
        frame = 0;
    }
    
    char *c;
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);  // —°‘ÒÕ∂”∞æÿ’Û
    glPushMatrix();               // ±£¥Ê‘≠æÿ’Û
    glLoadIdentity();             // ◊∞»Îµ•Œªæÿ’Û
    glOrtho(0,480,0,480,-1,1);    // Œª÷√’˝Õ∂”∞
    glMatrixMode(GL_MODELVIEW);   // —°‘ÒModelviewæÿ’Û
    glPushMatrix();               // ±£¥Ê‘≠æÿ’Û
    glLoadIdentity();             // ◊∞»Îµ•Œªæÿ’Û
    glRasterPos2f(10,10);
    for (c=buffer; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    glMatrixMode(GL_PROJECTION);  // —°‘ÒÕ∂”∞æÿ’Û
    glPopMatrix();                // ÷ÿ÷√Œ™‘≠±£¥Êæÿ’Û
    glMatrixMode(GL_MODELVIEW);   // —°‘ÒModelviewæÿ’Û
    glPopMatrix();                // ÷ÿ÷√Œ™‘≠±£¥Êæÿ’Û
    glEnable(GL_DEPTH_TEST);
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


void updateView(int width, int height)
{
    glViewport(0,0,width,height);						// Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width/(GLfloat)height;
    
    //    if (bPersp) {
    gluPerspective(90.0f, whRatio,0.1f,600.0f);
    //    } else {
    //        glOrtho(-3 ,3, -3, 3,-100,100);
    //    }
    
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}



void key(unsigned char k, int x, int y)
{
    GLfloat new_eye[3];
    
    switch(k)
    {
        case 27:
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; break; }
            
        case 'n': {bNurbs = !bNurbs; break;}
        case 'o': {bWire = !bWire; break;}
            
        case 'm': {screenshot(); break;}
            
        case 'l': {lights.changeMode(); break;}
            
        case ' ': {
            bAnim = !bAnim;
            break;
        }
           
        //Zoom Fit
        case 'f': {
            Area area = Collision::getNearest(eye[0], eye[1], eye[2]);
            center[0] = area.x + area.dimensions[0] * 0.5;
            center[1] = area.y + area.dimensions[1] * 0.5;
            center[2] = area.z + area.dimensions[2] * 0.5;
            
            GLdouble dis0 = sqrt(pow((eye[0] - center[0]), 2) + pow((eye[1] - center[1]), 2) + pow((eye[2] - center[2]),2));
            
            GLdouble len = max(max(area.dimensions[0], area.dimensions[1]), area.dimensions[2]);
            
            cout << len << " " << dis0 << endl;
            GLdouble dis = len * 0.8;
            
            GLdouble r = dis / dis0;
            
            eye[0] += (center[0] - eye[0]) * (1 - r);
            eye[1] += (center[1] - eye[1]) * (1 - r);
            eye[2] += (center[2] - eye[2]) * (1 - r);
            
            cout << "Zoom Fit: " << area.x << " " << area.y << " " << area.z << endl;
            break;
        }
            
        
        case 'a': {
            new_eye[2] = eye[2] + 0.2f*sin(angle);
            new_eye[0] = eye[0] - 0.2f*cos(angle);
            new_eye[1] = eye[1];
            if (Collision::checkViewPort(eye[0], eye[1], eye[2], new_eye[0], new_eye[1], new_eye[2])){
                eye[2] += 0.2f*sin(angle);
                eye[0] -= 0.2f*cos(angle);
                center[2] += 0.2f*sin(angle);
                center[0] -= 0.2f*cos(angle);
            }
            
            break;
        }
        case 'd': {
            new_eye[2] = eye[2] - 0.2f*sin(angle);
            new_eye[0] = eye[0] + 0.2f*cos(angle);
            new_eye[1] = eye[1];
            if (Collision::checkViewPort(eye[0], eye[1], eye[2], new_eye[0], new_eye[1], new_eye[2])){
                eye[2] -= 0.2f*sin(angle);
                eye[0] += 0.2f*cos(angle);
                center[2] -= 0.2f*sin(angle);
                center[0] += 0.2f*cos(angle);
            }
            
            break;
        }
        case 'w': {
            new_eye[2] = eye[2] - 0.2f*cos(angle);
            new_eye[0] = eye[0] - 0.2f*sin(angle);
            new_eye[1] = eye[1] + (center[1]-eye[1])*0.05;
            if (Collision::checkViewPort(eye[0], eye[1], eye[2], new_eye[0], new_eye[1], new_eye[2])){
                eye[2] -= 0.2f*cos(angle);
                eye[0] -= 0.2f*sin(angle);
                center[2] -= 0.2f*cos(angle);
                center[0] -= 0.2f*sin(angle);
                double tmp=(center[1]-eye[1])*0.05;
                eye[1] += tmp;
                center[1] += tmp;
            }
            
            
            break;
        }
        case 's': {
            new_eye[2] = eye[2] + 0.2f*cos(angle);
            new_eye[0] = eye[0] + 0.2f*sin(angle);
            new_eye[1] = eye[1] - (center[1]-eye[1])*0.05;
            if (Collision::checkViewPort(eye[0], eye[1], eye[2], new_eye[0], new_eye[1], new_eye[2])){
                eye[2] += 0.2f*cos(angle);
                eye[0] += 0.2f*sin(angle);
                center[2] += 0.2f*cos(angle);
                center[0] += 0.2f*sin(angle);
                double tmp=(center[1]-eye[1])*0.05;
                eye[1] -= tmp;
                center[1] -= tmp;
            }
            break;
        }
        case 'z': {
            //zzzzzzzzzzzzzzzzzzzzzzzz
            
            //yyyyyyyyyyyyyyyyyyyyyyyy
            break;
        }
        case 'c': {
            roaming=!roaming;
            if (roaming) {
                currentRoam=0;
            }
            else {
                currentRoam=-1;
            }
            
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



struct str
{
    int x,y;
}oldpt;

void Mouse(int button, int state, int x, int y)        /*当鼠标按下或拿起时会回调该函数*/
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //        l_button_down = TRUE;                /*当l_button_down为true时才可改变相机位置*/
        oldpt.x=x;                      /*记录旧坐标，以便移动发生时计算鼠标移动方向*/
        oldpt.y=y;
        printf("鼠标左键按下\n");
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        //        l_button_down = FALSE;        /*拿起时不能改变摄像机位置*/
        printf("鼠标左键松开\n");
    }
}

void OnMouseMove(int x, int y)          /*当鼠标移动时会回调该函数*/
{
    angle-=(x-oldpt.x)/100.0;
    center[1]-=(y-oldpt.y)/50.0;
    oldpt.x=x;
    oldpt.y=y;
    center[0]=-5.0f*sin(angle)+eye[0];
    center[2]=-5.0f*cos(angle)+eye[2];
    printf("%lf %lf\n",center[0],center[2]);
    printf("鼠标移动\n");
}
