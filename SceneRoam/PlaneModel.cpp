//
//  PlaneModel.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/29.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "PlaneModel.hpp"

PlaneModel::PlaneModel(){
    for (int i = 0; i < 1000; i++){
        vec3 pos;
        pos.x = 200;
        pos.y = 150;
        pos.z = i - 500;
        airline.push_back(pos);
    }
}


void PlaneModel::fly(){
    position.x = airline[currentPos].x;
    position.y = airline[currentPos].y;
    position.z = airline[currentPos].z;
    
    currentPos++;
    if (currentPos == airline.size())
        currentPos = 0;
    glPushMatrix();
    glTranslatef(0, 20, -30);
    glRotatef(90, 0, 1, 0);
    draw();
    glPopMatrix();
}