//
//  Collision.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/28.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef Collision_hpp
#define Collision_hpp

#include <stdio.h>
#include <vector>
#include "ObjModel.hpp"
class Collision {
public:
    static vector<Area*> Areas;
    
public:
    static void addObjArea(Area* area);
    static void clear(){
        Areas.clear();
    }
    static bool checkViewPort(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);
    //static bool checkObject();
    
    static Area getNearest(GLfloat x, GLfloat y, GLfloat z);
};

#endif /* Collision_hpp */
