//
//  ViewPortCtrl.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/5.
//  Copyright © 2016年 Yym. All rights reserved.
//

#ifndef ViewPortCtrl_hpp
#define ViewPortCtrl_hpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DoorModel.hpp"
#include "Collision.hpp"
#include "SaveBmp.hpp"
#include "Lights.hpp"

extern Lights lights;

void reshape(int width, int height);
void updateView(int width, int height);


void key(unsigned char k, int x, int y);

void Mouse(int button, int state, int x, int y);
void OnMouseMove(int x, int y);
void getFPS();

#endif /* ViewPortCtrl_hpp */
