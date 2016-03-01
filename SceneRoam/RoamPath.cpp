//
//  RoamPath.cpp
//  CGProj
//
//  Created by zyy on 16/1/7.
//  Copyright © 2016年 zyy. All rights reserved.
//

#include "RoamPath.hpp"
#include <math.h>

double roamPath[16][7]={{0.042036, 3.420001, -4.600173, 0.000000, 4.000000, -9.599996, 3.150000},
    {-3.728526, 2.680001, -6.268616, 0.000000, 4.000000, -9.599996, 2.300000},
    {-7.805228, 1.264003, -5.760357, -3.762746, 2.604002, -8.702863, 2.200000},
    {-8.358072, 0.348004, -2.975682, -5.569654, 1.388002, -7.125950, 2.550000},
    {-8.788076, 1.209010, 9.093878, -7.494979, 0.889008, 4.263981, 2.880000},
    {-1.589368, 2.725010, 4.911900, -6.418233, 3.865008, 3.614958, 4.450000},
    {7.641459, 1.631014, 7.854609, 3.040819, 2.551012, 5.896521, 4.310000},
    {5.052904, 4.375014, 2.746725, 1.974753, 4.915012, 6.686901, 5.620000},
    {6.179317, 4.427017, 0.047666, 6.013421, 4.427015, 5.044913, 6.250000},
    {3.539826, 5.183014, 5.229589, 8.536940, 5.683013, 5.399465, 7.820000},
    {-2.712518, 4.317016, 10.841413, -2.888592, 4.337016, 5.844514, 9.460000},
    {-0.390382, 4.337016, 1.513354, -2.888592, 4.337016, 5.844514, 5.760000},
    {7.927283, 4.002019, -9.288084, 5.049906, 4.002018, -5.198988, 5.670000},
    {1.900805, 3.078023, -10.068568, 5.679607, 7.178019, -6.794328, 7.140000},
    {3.468041, 6.878020, -4.587234, 6.820153, 9.938018, -8.297132, 8.690000},
    {0.042036, 3.420001, -4.600173, 0.000000, 4.000000, -9.599996, 363.150000}};

char passQuick[16]={'N','Y','N','Y','N','Y','N','Y','N','Y','N','Y','N','Y','N','N'};

double finalPath[500000][7];
int finalPathTot=0;

double euDist(int a, int b)
{
    return sqrt((roamPath[a][0]-roamPath[b][0])*(roamPath[a][0]-roamPath[b][0])
                +(roamPath[a][1]-roamPath[b][1])*(roamPath[a][1]-roamPath[b][1])
                +(roamPath[a][2]-roamPath[b][2])*(roamPath[a][2]-roamPath[b][2])
                +(roamPath[a][3]-roamPath[b][3])*(roamPath[a][3]-roamPath[b][3])
                +(roamPath[a][4]-roamPath[b][4])*(roamPath[a][4]-roamPath[b][4])
                +(roamPath[a][5]-roamPath[b][5])*(roamPath[a][5]-roamPath[b][5]));
}

void addToFinalPath(double a, double b, double c, double d, double e, double f, double g)
{
    finalPath[finalPathTot][0]=a;
    finalPath[finalPathTot][1]=b;
    finalPath[finalPathTot][2]=c;
    finalPath[finalPathTot][3]=d;
    finalPath[finalPathTot][4]=e;
    finalPath[finalPathTot][5]=f;
    finalPath[finalPathTot][6]=g;
    finalPathTot++;
}

void genRoamInRoom()
{
    double a,b,c,d,e,f,g;
    a=roamPath[0][0];
    b=roamPath[0][1];
    c=roamPath[0][2];
    d=roamPath[0][3];
    e=roamPath[0][4];
    f=roamPath[0][5];
    g=roamPath[0][6];
    for (int j=0; j<20; j++) {
        addToFinalPath(roamPath[0][0],roamPath[0][1],roamPath[0][2],roamPath[0][3],roamPath[0][4],roamPath[0][5],roamPath[0][6]);
    }
//    updateView(wHeight, wWidth);
    for (int i=1; i<16; i++)
    {
        double dist = euDist(i-1, i);
        int total=(int)(dist * 2);
        
        for (int j=0; j<total; j++)
        {
            a+=(roamPath[i][0]-roamPath[i-1][0])/total;
            b+=(roamPath[i][1]-roamPath[i-1][1])/total;
            c+=(roamPath[i][2]-roamPath[i-1][2])/total;
            d+=(roamPath[i][3]-roamPath[i-1][3])/total;
            e+=(roamPath[i][4]-roamPath[i-1][4])/total;
            f+=(roamPath[i][5]-roamPath[i-1][5])/total;
            g+=(roamPath[i][6]-roamPath[i-1][6])/total;
            addToFinalPath(a, b, c, d, e, f, g);
//            updateView(wHeight, wWidth);
        }
        
        a=roamPath[i][0];
        b=roamPath[i][1];
        c=roamPath[i][2];
        d=roamPath[i][3];
        e=roamPath[i][4];
        f=roamPath[i][5];
        g=roamPath[i][6];
        addToFinalPath(a, b, c, d, e, f, g);
        if (passQuick[i]=='Y')
            continue;
        
        for (int j=0; j< 20; j++) {
            addToFinalPath(a, b, c, d, e, f, g);
        }
//        updateView(wHeight, wWidth);
//        printf("OK\n");
    }
    
    printf("TOTAL: %d\n",finalPathTot);
}