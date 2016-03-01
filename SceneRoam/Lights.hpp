//
//  Lights.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/6.
//  Copyright © 2016年 Yym. All rights reserved.
//

#ifndef Lights_hpp
#define Lights_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "Sun.hpp"





class Lights {
private:
    int mode = 0;
    Sun sun;
    
public:
    void setMode(int mode);
    void changeMode();
    void Light0();
    void Light1();
    void Light3();
    void torch();
    void sunny();
    void on();
};


#endif /* Lights_hpp */
