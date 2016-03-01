//
//  PlaneModel.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/29.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef PlaneModel_hpp
#define PlaneModel_hpp

#include <stdio.h>
#include "ObjModel.hpp"

class PlaneModel: public ObjModel {
private:
    vector<vec3> airline;
    int currentPos = 0;
public:
    PlaneModel();
    void fly();
};

#endif /* PlaneModel_hpp */
