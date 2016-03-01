//
//  ObjModel.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/21.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef ObjModel_hpp
#define ObjModel_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <GLUT/GLUT.h>
#include <cmath>
#include <cstring>
#include <sstream>
#include "LoadTexture.hpp"
using namespace std;



class vec3 {
public:
    GLfloat x;
    GLfloat y;
    GLfloat z;
};


class vec2 {
public:
    GLfloat x;
    GLfloat y;
};


class ObjMaterial {
public:
    string  name;
    GLfloat diffuse[4];
    GLfloat ambient[4];
    GLfloat specular[4];
    GLfloat emmissive[4];
    GLfloat shininess;
    GLuint  texture;
    bool    isVideo = false;
    GLuint  curFrame = 0;
    vector<GLuint>  videoFrames;
public:
    void clear(){
        name = "";
        isVideo = false;
        texture = -1;
        videoFrames.clear();
    }
};


class ObjPoint {
public:
    vec3 vertex;
    vec2 texCoord;
    vec3 normal;
};

class ObjTriangle {
public:
    ObjPoint points[3];
};

class ObjQuad {
public:
    ObjPoint points[4];
};


class ObjGroup {
public:
    string  name;
    vector<ObjTriangle> triangles;
    vector<ObjQuad> quads;
    string  material;
public:
    void clear(){
        name = "";
        triangles.clear();
        quads.clear();
        material = "";
    }
};

class Area {
public:
    GLfloat x, y, z;
    GLfloat dimensions[3];
};


class ObjModel {
protected:
    vector<ObjGroup>    groups;
    map<string, ObjMaterial>    materials;
    string  filePath;
    string  objFile;
    string  mtlFile;
    GLuint  objList = 10000;
    vec3    position;
    Area    area;
    GLuint  ori = 0;
    
public:
    ObjModel(){
        materials.clear();
        groups.clear();
        position.x = 0;
        position.y = 0;
        position.z = 0;
    }
    bool    loadOBJ(string filePath, string objFile);
    void    draw();
    void    render();
    void    unitize(GLfloat ratio);
    void    setPosition(GLfloat x, GLfloat y, GLfloat z);
    void    rotate(GLuint ori);
    Area&   getArea();
    
private:
    bool    loadMTL();
    GLuint  list();
    
protected:
    void    getDimensions(GLfloat* dimensions);
    void    setArea();
    GLfloat getMinX();
    GLfloat getMinY();
    GLfloat getMinZ();
};




#endif /* ObjModel_hpp */
