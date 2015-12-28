//
//  DoorModel.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/23.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef DoorModel_hpp
#define DoorModel_hpp

#include <stdio.h>
#include "ObjModel.hpp"

class DoorModel: public ObjModel {
private:
    bool state = 0; //0->close 1->open
    GLfloat  angle = 0.0f;  //current angle, 0->close, 90->open
    GLfloat speed = 0.7f;
public:
    bool isOpen(){
        return state;
    }
    void open(){
        state = 1;
    }
    void close(){
        state = 0;
    }
    void draw();
};

#endif /* DoorModel_hpp */
