//
//  MonitorModel.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/23.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef MonitorModel_hpp
#define MonitorModel_hpp

#include <stdio.h>
#include "ObjModel.hpp"


class MonitorModel:public ObjModel {
private:
    bool playing = false;
    
public:
    void    setVideo(string mtl, int nFrame, string pic);
    void    play(){ playing = true; }
    void    pause(){ playing = false; }
    void    draw();
};

#endif /* MonitorModel_hpp */
