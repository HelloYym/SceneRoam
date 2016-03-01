//
//  Geometry.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/28.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "Geometry.hpp"

void Geometry::draw(){
    if (list == 10000)
        list = genList();
    glCallList(list);
}

void Geometry::render(){
    
    float color0[] = {134/255.0f, 120/255.0f, 171/255.0f, 1.0f};
    float high_shininess = 20.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
    
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    glPushMatrix();
    glTranslatef(1, 0.5, 1);
    glRotated(90, 1, 0, 0);
    //gluDisk(quadric, 2, 0, 200, 200);
    gluCylinder(quadric, 0, 2.0, 4, 200, 200);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(2, 0, 0);
    gluSphere(quadric, 1.0, 200, 200);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4, 1, 1);
    glRotated(70, 1, 0.4, 0);
    gluCylinder(quadric, 0.5, 0.5, 1, 200, 200);
    glPopMatrix();
    
    gluDeleteQuadric(quadric);
    
}

GLuint Geometry::genList(){
    GLuint list;
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    render();
    glEndList();
    return list;
}