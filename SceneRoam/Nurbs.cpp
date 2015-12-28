//
//  Nurbs.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/25.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "Nurbs.hpp"


void Nurbs::init(){
    for(int u = 0 ; u < 5 ; u++ )
        for(int v = 0 ; v < 5 ; v++ ){
            ctlpoints[u][v][0] = u - 2;
            ctlpoints[u][v][2] = v - 2;
            ctlpoints[u][v][1] = 0;
        }
    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb,GLU_SAMPLING_TOLERANCE,10.0);
    gluNurbsProperty(theNurb,GLU_DISPLAY_MODE,GLU_FILL);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    
    glPointSize(5.0);
    glLineWidth(2.0);
    
    glGenTextures(1, &texture);
    texload(texture, "Wall.bmp");
}




void Nurbs::drawFrame(void)
{
    glDisable(GL_LIGHTING);
    glColor3f(0.f, 1.f, 0.f);
    
    glBegin(GL_POINTS);
    for (int u=0; u<5; u++)
        for (int v=0; v<5; v++)
            glVertex3fv(ctlpoints[u][v]);
    glEnd();
    
    glColor3f(1.f, 1.f, 1.f);
    for (int u=0; u<5; u++) {
        glBegin(GL_LINE_STRIP);
        for (int v=0; v<5; v++)
            glVertex3fv(ctlpoints[u][v]);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (int v=0; v<5; v++)
            glVertex3fv(ctlpoints[v][u]);
        glEnd();
    }
    
    glEnable(GL_LIGHTING);
}


void Nurbs::drawSurface()
{
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);  //选择纹理texture[0]
    
    GLfloat color[4][4] ={
        {153/255.0f, 120/255.0f, 204/255.0f, 1.0f},
        {153/255.0f, 120/255.0f, 204/255.0f, 1.0f},
        {153/255.0f, 120/255.0f, 204/255.0f, 1.0f},
        {153/255.0f, 120/255.0f, 204/255.0f, 1.0f}
    };
    
    colorCtl++;
    if (colorCtl > 3)
        colorCtl = 0;
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[colorCtl]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color[colorCtl]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
    
    if (ctlpoints[2][2][1] > 4 || ctlpoints[2][2][1] < 0)
        ctl = -ctl;
    
    if (ctl == 1){
        ctlpoints[2][2][1] += 0.02f;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++){
                if (abs(j - 2) + abs(i - 2) == 1)
                    ctlpoints[i][j][1] += 0.01f;
            }
    }
    else{
        ctlpoints[2][2][1] -= 0.02f;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++){
                if (abs(j - 2) + abs(i - 2) == 1)
                    ctlpoints[i][j][1] -= 0.01f;
            }
    }
    
    
    GLfloat tknots[ 4 ] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat knots[10] = {0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0};
    gluBeginSurface(theNurb);
    
    gluNurbsSurface(theNurb, 4, tknots, 4, tknots, 2*2, 2, &tcoords[0][0][0], 2, 2, GL_MAP2_TEXTURE_COORD_2);
    //gluNurbsSurface(theNurb,8,knots,8,knots,4*3,3,&ctlpoints[0][0][0],4,4,GL_MAP2_VERTEX_3);
    
    gluNurbsSurface(theNurb,10,knots,10,knots,5*3,3,&ctlpoints[0][0][0],5,5,GL_MAP2_VERTEX_3);
        
    gluEndSurface(theNurb);
    
    
    glDisable(GL_COLOR_MATERIAL);
}









