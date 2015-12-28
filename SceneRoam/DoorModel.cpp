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
    }
    else{
        if (angle < 90)
            angle +=speed;
        if (angle > 90)
            angle = 90;
    }
    glPushMatrix();
    glTranslatef(-0.5, 0, 0);
    glRotated(angle, 0, 1, 0);
    glTranslatef(0.5, 0, 0);
    ObjModel::draw();
    glPopMatrix();
}
