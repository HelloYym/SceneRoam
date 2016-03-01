//
//  Wall.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/4.
//  Copyright © 2016年 Yym. All rights reserved.
//

#ifndef Wall_hpp
#define Wall_hpp

#include <stdio.h>
#include "LoadTexture.hpp"
#include <GLUT/GLUT.h>

class Wall {
private:
    GLuint  objList = 10000;
public:
    void draw();

private:
    GLuint  list();
    void    render();
};

#endif /* Wall_hpp */
