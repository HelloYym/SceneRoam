//
//  Geometry.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/28.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>

class Geometry {
private:
    GLuint list = 10000;
    
private:
    void render();
    GLuint genList();
    
public:
    void draw();
};

#endif /* Geometry_hpp */
