//
//  Screen.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/30.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>
#include <sstream>
#include "LoadTexture.hpp"
using namespace std;

class Screen {
private:
    GLuint  curFrame = 0;
    vector<GLuint>  videoFrames;
    bool playing = false;
    short count = 0;
public:
    void setVideo(string path, int n);
    void draw();
    void play(){
        playing = true;
    }
    
    void pause(){
        playing = false;
    }
};


#endif /* Screen_hpp */
