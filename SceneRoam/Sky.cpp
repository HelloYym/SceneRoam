//
//  Sky.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/29.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "Sky.hpp"

void Sky::draw(){
    if (list == 10000)
        list = genList();
    glPushMatrix();
    glRotatef(angle, 1, 1, 1);
    glRotatef(90, 1, 0, 1);
    glCallList(list);
    glPopMatrix();
    angle += 0.04;
}

void Sky::render(){
    GLuint texture;
    glGenTextures(1, &texture);
    texload(texture, "Sky.bmp");
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);  //选择纹理texture[0]
    
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, true);
    
    glPushMatrix();
    gluSphere(quadric, 500, 200, 200);
    glPopMatrix();
    
    gluDeleteQuadric(quadric);
    
    glDisable(GL_TEXTURE_2D);
    
}

GLuint Sky::genList(){
    GLuint list;
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    render();
    glEndList();
    return list;
}