//
//  DoorModel.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/23.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "DoorModel.hpp"

void DoorModel::draw(){
    if (state == 0){
        if (angle > 0)
            angle -= speed;
        if (angle < 0)
            angle = 0;
        setArea();
    }
    else{
        if (angle < 90)
            angle +=speed;
        if (angle > 90)
            angle = 90;
        setArea();
    }
    if (angle < 90){
        glPushMatrix();
        glTranslatef(area.x, 0, area.z);
        glRotated(angle, 0, 1, 0);
        glTranslatef(-area.x, 0, -(area.z));
        ObjModel::draw();
        glPopMatrix();
    }
    else{
        glPushMatrix();
        glTranslatef(area.x + area.dimensions[0], 0, (area.z + area.dimensions[2]));
        glRotated(angle, 0, 1, 0);
        glTranslatef(-(area.x + area.dimensions[0]), 0, -(area.z + area.dimensions[2]));
        ObjModel::draw();
        glPopMatrix();
    }
}


void DoorModel::setArea(){
    if (angle < 90){
        area.x = getMinX() + position.x;
        area.y = getMinY() + position.y;
        area.z = getMinZ() + position.z;
        getDimensions(area.dimensions);
        area.dimensions[0] = area.dimensions[0] * cos(angle / 180 * 3.14);
    }
    else{
        getDimensions(area.dimensions);
        area.x = getMinX() + position.x - area.dimensions[2];
        area.y = getMinY() + position.y;
        area.z = getMinZ() + position.z - area.dimensions[0];
        GLfloat p = area.dimensions[0];
        area.dimensions[0] = area.dimensions[2];
        area.dimensions[2] = p;
    }
    
}