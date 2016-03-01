//
//  Models.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/5.
//  Copyright © 2016年 Yym. All rights reserved.
//

#ifndef Models_h
#define Models_h

#include <GLUT/GLUT.h>
#include "ObjModel.hpp"
#include "DoorModel.hpp"
#include "MonitorModel.hpp"
#include "PlaneModel.hpp"
#include "Nurbs.hpp"
#include "Sky.hpp"
#include "Geometry.hpp"
#include "Screen.hpp"
#include "Wall.hpp"

ObjModel Woman;
ObjModel Apple;
ObjModel Dumbbell;
ObjModel Ball;
ObjModel iPad;
ObjModel City;
ObjModel Lamp;
ObjModel Table;
ObjModel Table2;
ObjModel Plant2;
ObjModel Plant0;
ObjModel Chair;
ObjModel Sofa;
ObjModel Grass;
ObjModel Jeep;
ObjModel Tree;
PlaneModel Plane;
Geometry geometry;
DoorModel Door;
MonitorModel Monitor;
Screen screen;
Wall wall;
Sky sky;
Nurbs NurbsSurface;

GLuint GrassList;   //草地显示列表

extern bool bNurbs; //是否绘制Nurbs曲面

void initModels(){
    
    
    //    Sofa.loadOBJ("Models/Sofa", "Sofa.obj");
    
    Tree.loadOBJ("Models/needle", "needle.obj");
    Tree.unitize(20);
    Tree.setPosition(8, -Tree.getArea().y, -20);
    Collision::addObjArea(&Tree.getArea());
    
    
    Grass.loadOBJ("Models/Grass", "Grass_02.obj");
    Grass.unitize(5);
    
    Plane.loadOBJ("Models/Boeing747", "Boeing747.obj");
    
    Table.loadOBJ("Models/Table", "Table.obj");
    Table.unitize(4.0);
    Table.setPosition(10 - Table.getArea().x - Table.getArea().dimensions[0], -Table.getArea().y, -10 - Table.getArea().z);
    Collision::addObjArea(&Table.getArea());
    
    Plant2.loadOBJ("Models/plant2", "plant.obj");
    Plant2.unitize(2.0);
    Plant2.setPosition(9, Table.getArea().dimensions[1] - Plant2.getArea().y, -8.5);
    Collision::addObjArea(&Plant2.getArea());
    
    Plant0.loadOBJ("Models/plant0", "plant.obj");
    Plant0.unitize(2.0);
    Plant0.setPosition(8, Table.getArea().dimensions[1] - Plant0.getArea().y, -9);
    Collision::addObjArea(&Plant0.getArea());
    
    
    Table2.loadOBJ("Models/Table2", "Table2.obj");
    Table2.unitize(7);
    Table2.setPosition(10 - Table2.getArea().x - Table2.getArea().dimensions[0], -Table2.getArea().y, 0 - Table2.getArea().z);
    Collision::addObjArea(&Table2.getArea());
    
    Apple.loadOBJ("Models/Apple", "Apple.obj");
    Apple.unitize(1.3);
    Apple.setPosition(Table2.getArea().x + 5.7, Table2.getArea().dimensions[1] - Apple.getArea().y, Table2.getArea().z + 2.8);
    Collision::addObjArea(&Apple.getArea());
    
    iPad.loadOBJ("Models/iPad", "iPad.obj");
    iPad.unitize(1.3);
    iPad.setPosition(Table2.getArea().x + 1.2, Table2.getArea().dimensions[1] - iPad.getArea().y, Table2.getArea().z + 1);
    Collision::addObjArea(&iPad.getArea());
    
    Lamp.loadOBJ("Models/Lamp", "Lamp.obj");
    Lamp.unitize(2);
    Lamp.setPosition(Table2.getArea().x + 0.5, Table2.getArea().dimensions[1] - Lamp.getArea().y, Table2.getArea().z + 2.8);
    Collision::addObjArea(&Lamp.getArea());
    
    Monitor.loadOBJ("Models/Monitor", "Monitor.obj");
    Monitor.unitize(4.0);
    Monitor.setVideo("screen", 138, "Video1");
    Monitor.play();
    Monitor.setPosition(Table2.getArea().x + 3.2, Table2.getArea().dimensions[1] - Monitor.getArea().y, Table2.getArea().z + 2.1);
    Collision::addObjArea(&Monitor.getArea());
    
    Chair.loadOBJ("Models/Chair", "Chair.obj");
    Chair.unitize(4.0);
    Chair.setPosition(Table2.getArea().x + 3, -Chair.getArea().y, Table2.getArea().z + 7);
    Chair.rotate(195);
    Collision::addObjArea(&Chair.getArea());
    
    Ball.loadOBJ("Models/Ball", "Ball.obj");
    Ball.unitize(1.2);
    Ball.setPosition(5, -Ball.getArea().y, 1.5);
    Collision::addObjArea(&Ball.getArea());
    
    Dumbbell.loadOBJ("Models/Dumbbell", "Dumbbell.obj");
    Dumbbell.unitize(2.5);
    Dumbbell.setPosition(-6.5, -Dumbbell.getArea().y, 8.5);
    Collision::addObjArea(&Dumbbell.getArea());
    
    Jeep.loadOBJ("Models/Jeep", "Jeep.obj");
    Jeep.unitize(3.0);
    Jeep.setPosition(-8, -Jeep.getArea().y, 6.5);
    Jeep.rotate(-30);
    Collision::addObjArea(&Jeep.getArea());
    
    
    //
    //    Woman.loadOBJ("Models/test", "test.obj");
    //    Woman.unitize(2.0);
    //    Woman.setPosition(-5, - Woman.getArea().y, -5);
    //
    
    
    City.loadOBJ("Models/City", "City.obj");
    City.setPosition(0, -10 - City.getArea().y, -135);
    
    
    Door.loadOBJ("Models/Door", "Door.obj");
    Door.unitize(8);
    Door.setPosition(0, -Door.getArea().y, -10.1);
    Collision::addObjArea(&Door.getArea());
    
    
    screen.setVideo("Video2", 401);
    screen.play();
    
    GrassList = glGenLists(1);
    glNewList(GrassList, GL_COMPILE);
    {
        for (int i = -10; i < 10; i++)
            for (int j = 0; j < 6; j++){
                glPushMatrix();
                glTranslated(i * 3.2, 0.2, -j * 3.7 - 12.5);
                Grass.render();
                glPopMatrix();
            }
    }
    glEndList();
    
    NurbsSurface.init();
}


void drawScene()
{
    
    if (bNurbs) {
        glPushMatrix();
        glTranslated(-5, 3, -5);
        NurbsSurface.drawSurface();
        glPopMatrix();
    }
    
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    wall.draw();
    
    //    Woman.draw();
    Dumbbell.draw();
    
    Apple.draw();
    iPad.draw();
    City.draw();
    Door.draw();
    Monitor.draw();
    Lamp.draw();
    Table.draw();
    
    Plant2.draw();
    Plant0.draw();
    
    Tree.draw();
    
    Chair.draw();
    Table2.draw();
    
    Jeep.draw();
    
    glCallList(GrassList);
    
    sky.draw();
    
    glPushMatrix();
    Plane.fly();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-9, 1, -8);
    geometry.draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 3.3, 9.99);
    glScalef(3, 3, 3);
    glRotated(180, 0, 1, 0);
    screen.draw();
    glPopMatrix();
}





#endif /* Models_h */







