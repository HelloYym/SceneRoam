//
//  LoadTexture.hpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/21.
//  Copyright © 2015年 Yym. All rights reserved.
//

#ifndef LoadTexture_hpp
#define LoadTexture_hpp


#include <stdio.h>
#include <string.h>
#include <GLUT/GLUT.h>


typedef unsigned int DWORD;
typedef int LONG;
typedef unsigned short WORD;
typedef unsigned char BYTE;

#pragma pack(1)

typedef struct tagBITMAPFILEHEADER {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER {
    DWORD      biSize;
    LONG        biWidth;
    LONG        biHeight;
    WORD       biPlanes;
    WORD       biBitCount;
    DWORD      biCompression;
    DWORD      biSizeImage;
    LONG        biXPelsPerMeter;
    LONG        biYPelsPerMeter;
    DWORD      biClrUsed;
    DWORD      biClrImportant;
} BITMAPINFOHEADER;

#pragma pack()


#define BITMAP_ID 0x4D42


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
unsigned char *CreateMyBmp(BITMAPINFOHEADER *bitmapInfoHeader);
void texload(GLuint& texture, char *filename);

#endif /* LoadTexture_hpp */
