//
//  Sun.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/29.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef Sun_hpp
#define Sun_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "DoorModel.hpp"
#include <cmath>

class Sun {
private:
    GLfloat angle = 0;
    GLfloat position[4];
    GLfloat color[4] = {232.0/255.0f, 220.0/255.0f, 200.0/255.0f, 1.0f};
    
public:
    Sun();
    void shine();
    void reset(){
        angle = 0;
    }
};

#endif /* Sun_hpp */
