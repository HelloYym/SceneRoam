//
//  Sky.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/29.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef Sky_hpp
#define Sky_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "LoadTexture.hpp"


class Sky {
private:
    GLuint list = 10000;
    GLdouble angle = 0;
    
private:
    void render();
    GLuint genList();
    
public:
    void draw();
};


#endif /* Sky_hpp */
