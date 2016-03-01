//
//  Collision.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/28.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "Collision.hpp"

vector<Area*> Collision::Areas;

bool Collision::checkViewPort(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2){
    
    bool flag = true;
    
    
    /* In room */
    if (x1 > -10 && x1 < 10 && y1 > 0 && y1 < 10 && z1 > -10 && z1 < 10) {
        if (!(x1 > -2 && x1 < 2 && y1 > 0 && y1 < 8) && z2 <= -10)
            flag = false;
        
        if (z2 >= 10)
            flag = false;
        
        if (x2 <= -10 || x2 >= 10 || y2 <=0 || y2 >=10)
            flag = false;
    }
    else {
        
        if (x1 < 10 && x1 > -10 && y1 > 0 && y1 < 10 && z1 < -10 && z2 >= -10)
            if (!(x1 > -2 && x1 < 2 && y1 > 0 && y1 < 8))
                flag = false;
        
        if (x1 < -10 && y1 > 0 && y1 < 10 && z1 > -10 && z1 < 10 && x2 >= -10)
            flag = false;
        
        if (x1 > 10 && y1 > 0 && y1 < 10 && z1 > -10 && z1 < 10 && x2 <= 10)
            flag = false;
        
        if (x1 > -10 && x1 < 10 && y1 > 0 && y1 < 10 && z1 > 10 && z2 <= 10)
            flag = false;
        
    }
    
    for (int i = 0; i < Areas.size(); i++){
        Area area = *Areas[i];
        if (x2 >= area.x && x2 <= area.x + area.dimensions[0])
            if (y2 >= area.y && y2 <= area.y + area.dimensions[1])
                if (z2 >= area.z && z2 <= area.z + area.dimensions[2])
                    flag = false;
    }
    return flag;
}

void Collision::addObjArea(Area* area){
    Areas.push_back(area);
}




Area Collision::getNearest(GLfloat x, GLfloat y, GLfloat z){
    GLdouble minDis = 10000;
    Area res;
    for (int i = 0; i < Areas.size(); i++){
        Area area = *Areas[i];
        GLfloat x1, y1, z1;
        x1 = area.x + area.dimensions[0] * 0.5;
        y1 = area.y + area.dimensions[1] * 0.5;
        z1 = area.z + area.dimensions[2] * 0.5;
        GLdouble dis = sqrt(pow((x1 - x), 2) + pow((y1 - y), 2) + pow((z1 - z), 2));
        if (dis < minDis) {
            minDis = dis;
            res = area;
        }
    }
    return res;
}