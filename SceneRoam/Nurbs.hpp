//
//  Nurbs.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/25.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef Nurbs_hpp
#define Nurbs_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include "LoadTexture.hpp"



class Nurbs {
public:
    GLUnurbsObj *theNurb;
    GLfloat ctlpoints[5][5][3];
    GLfloat tcoords [2][2][2] = {0, 0, 0, 1, 1, 0, 1, 2};
    int ctl = 1;
    int colorCtl = 0;
    
    GLuint texture;
public:
    
    void init();
    
    void drawFrame();
    void drawSurface();
};

#endif /* Nurbs_hpp */
