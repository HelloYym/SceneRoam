//
//  Sun.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/29.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "Sun.hpp"

extern DoorModel Door;

Sun::Sun(){
    position[0] = 400.0f;
    position[1] = 0.0f;
    position[2] = 200.0f;
    position[3] = 1.0f;
    angle = 0.0f;
}

void Sun::shine(){
    if (!Door.isOpen()){
        reset();
        glDisable(GL_LIGHT7);
        return;
    }
        
    if (position[1] < 0) {
        glDisable(GL_LIGHT7);
    }
    else{
        glEnable(GL_LIGHT7);
    }
    glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, (1.0 / sin(angle)) * 0.001);
    
    glLightfv(GL_LIGHT7, GL_POSITION, position);
    
    glLightfv(GL_LIGHT7, GL_AMBIENT, color);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT7, GL_SPECULAR, color);
    glLightfv(GL_LIGHT7, GL_EMISSION, color);

    angle += 0.003f;
    position[0] = 400.0 * cos(angle);
    position[1] = 400.0 * sin(angle);
    
    //glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 1.0f);
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
}