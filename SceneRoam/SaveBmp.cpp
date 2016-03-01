//
//  SaveBmp.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 16/1/7.
//  Copyright © 2016年 Yym. All rights reserved.
//

#include "SaveBmp.hpp"


#define BITMAP_ID 0x4D42

unsigned char*  bitmapData;		// the bitmap data

bool WriteBitmapFile(char * filename, int width, int height, unsigned char * bitmapData)
{
    //填充BITMAPFILEHEADER
    BITMAPFILEHEADER bitmapFileHeader;
    memset(&bitmapFileHeader, 0, sizeof(BITMAPFILEHEADER));
    bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER);
    bitmapFileHeader.bfType = 0x4d42;	//BM
    bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
    
    //填充BITMAPINFOHEADER
    BITMAPINFOHEADER bitmapInfoHeader;
    memset(&bitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));
    bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfoHeader.biWidth = width;
    bitmapInfoHeader.biHeight = height;
    bitmapInfoHeader.biPlanes = 1;
    bitmapInfoHeader.biBitCount = 24;
    bitmapInfoHeader.biCompression = 0L;
    bitmapInfoHeader.biSizeImage = width * abs(height) * 3;
    
    //////////////////////////////////////////////////////////////////////////
    FILE * filePtr;			//连接要保存的bitmap文件用
    unsigned char tempRGB;	//临时色素
    int imageIdx;
    
//    //交换R、B的像素位置,bitmap的文件放置的是BGR,内存的是RGB
//    for (imageIdx = 0; imageIdx < bitmapInfoHeader.biSizeImage; imageIdx += 3)
//    {
//        tempRGB = bitmapData[imageIdx];
//        bitmapData[imageIdx] = bitmapData[imageIdx + 2];
//        bitmapData[imageIdx + 2] = tempRGB;
//    }
    
    filePtr = fopen(filename, "wb");
    if (NULL == filePtr)
    {
        return false;
    }
    
    fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    
    fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    
    fwrite(bitmapData, bitmapInfoHeader.biSizeImage, 1, filePtr);
    
    fclose(filePtr);
    return true;
}




bool screenshot()
{
    GLenum lastBuffer;
    GLbyte* pBits = 0; // 图像数据
    unsigned long lImageSize;
    GLint iViewport[4]; // 视图大小
    
    glGetIntegerv(GL_VIEWPORT, iViewport);
    lImageSize = iViewport[2] * iViewport[3] * 3;
    
    pBits = (GLbyte*)new unsigned char[lImageSize];
    if (!pBits)
        return false;
    
    // 从color buffer中读取数据
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    
    //
    glGetIntegerv(GL_READ_BUFFER, (GLint*)&lastBuffer);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, iViewport[2], iViewport[3], GL_BGR_EXT, GL_UNSIGNED_BYTE, pBits);
    glReadBuffer(lastBuffer);
    
    time_t tm = 0;
    tm = time(NULL);
    char lpstrFilename[256] = { 0 };
    sprintf(lpstrFilename, "./ScreenShot/%d.bmp", tm);
    
    if (WriteBitmapFile(lpstrFilename, iViewport[2], iViewport[3], (unsigned char*)pBits))
    {
        free(pBits);
        return true;
    }
    else
    {
        free(pBits);
        return false;
    }
    
}