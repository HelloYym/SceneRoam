//
//  Wall.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/4.
//  Copyright © 2016年 Yym. All rights reserved.
//

#include "Wall.hpp"


void Wall::render(){
    
    GLuint FloorTexture, WallTexture;
    glGenTextures(1, &FloorTexture);
    glGenTextures(1, &WallTexture);
    texload(FloorTexture, "Floor1.bmp");
    texload(WallTexture, "Room.bmp");
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glEnable(GL_TEXTURE_2D);
    
    glPushMatrix();
    glTranslated(0, 5, 0);
    glScalef(10.01, 5, 10.01);
    
    glBindTexture(GL_TEXTURE_2D, WallTexture);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 1);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2i(0, 0);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2i(1, 0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2i(1, 1);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, FloorTexture);
    glBegin(GL_QUADS);
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
    
    glBindTexture(GL_TEXTURE_2D, FloorTexture);
    glBegin(GL_QUADS);
    GLfloat divide = 10;
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
    
    
    
    //wall with door
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.2, 0.2);
    glVertex3f(-2.0, 0, -10.001);
    glTexCoord2f(0.7, 0.2);
    glVertex3f(-2.0, 10, -10.001);
    glTexCoord2f(0.7, 0.7);
    glVertex3f(-10, 10, -10.001);
    glTexCoord2f(0.2, 0.7);
    glVertex3f(-10, 0, -10.001);
    
    glTexCoord2f(0.2, 0.2);
    glVertex3f(10, 0, -10.001);
    glTexCoord2f(0.7, 0.2);
    glVertex3f(10, 10, -10.001);
    glTexCoord2f(0.7, 0.7);
    glVertex3f(2, 10, -10.001);
    glTexCoord2f(0.2, 0.7);
    glVertex3f(2, 0, -10.001);
    
    glTexCoord2f(0.2, 0.2);
    glVertex3f(2, 8, -10.001);
    glTexCoord2f(0.2, 0.4);
    glVertex3f(2, 10, -10.001);
    glTexCoord2f(0.4, 0.4);
    glVertex3f(-2, 10, -10.001);
    glTexCoord2f(0.4, 0.2);
    glVertex3f(-2, 8, -10.001);
    glEnd();
    glPopMatrix();
    
    
    
    
    float color[4] = {0/255.0f, 150/255.0f, 50/255.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(-50, -0.1, -50);
    glVertex3f(-50, -0.1, 50);
    glVertex3f(50, -0.1, 50);
    glVertex3f(50, -0.1, -50);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);


    float color1[4] = {255/255.0f, 255/255.0f, 255/255.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
}


GLuint Wall::list(){
    GLuint list;
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    render();
    glEndList();
    return list;
}

void Wall::draw(){
    if (objList == 10000)
        objList = list();
    glPushMatrix();
    glCallList(objList);
    glPopMatrix();
}

