//
//  SaveBmp.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/7.
//  Copyright © 2016年 Yym. All rights reserved.
//

#ifndef SaveBmp_hpp
#define SaveBmp_hpp


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GLUT/GLUT.h>
#include <time.h>
#include <string.h>
#include "LoadTexture.hpp"

using namespace std;


bool WriteBitmapFile(char * filename, int width, int height, unsigned char * bitmapData);
bool screenshot();



#endif /* SaveBmp_hpp */
