//
//  Screen.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/30.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "Screen.hpp"

void Screen::setVideo(string path, int n){
    for (int i = 0; i < n; i++){
        stringstream ss;
        string str;
        ss << i;
        ss >> str;
        
        GLuint texture;
        glGenTextures(1, &texture);
        
        string texPath = path + "/" + str + ".bmp";
        
        char ch[30];
        strcpy(ch, texPath.c_str());
        texload(texture, ch);
        
        videoFrames.push_back(texture);
    }
    curFrame = 0;
}

void Screen::draw(){
    
    float color[4] = {199/255.0f, 255/255.0f, 236/255.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    GLuint texture = videoFrames[curFrame];
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2i(0, 1);
    glVertex3f(0, 0, 0);
    glTexCoord2i(1, 1);
    glVertex3f(1.85f, 0, 0);
    glTexCoord2i(1, 0);
    glVertex3f(1.85f, 1, 0);
    glTexCoord2i(0, 0);
    glVertex3f(0, 1, 0);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
    
    count++;
    if (count == 5)
        count = 0;
    
    if (count == 1 || count == 3){
        curFrame++;
        if (curFrame == videoFrames.size()) {
            curFrame = 0;
        }
    }
    
}