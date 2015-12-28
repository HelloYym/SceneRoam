//
//  LoadTexture.cpp
//  SceneRoam
//
//  Created by 杨煜溟 on 15/12/21.
//  Copyright © 2015年 Yym. All rights reserved.
//

#include "LoadTexture.hpp"
#include <iostream>
using namespace std;



// 纹理标示符数组，保存两个纹理的标示符
// 描述: 通过指针，返回filename 指定的bitmap文件中数据。
// 同时也返回bitmap信息头.（不支持-bit位图）
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;	// 文件指针
    BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
    unsigned char	*bitmapImage;		// bitmap图像数据
    int	imageIdx = 0;		// 图像位置索引
    unsigned char tempRGB;	// 交换变量
    
    // 以“二进制+读”模式打开文件filename
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("BMP File not exit!!!\n");
        return NULL;
    }
    // 读入bitmap文件图
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    // 验证是否为bitmap文件
    if (bitmapFileHeader.bfType != BITMAP_ID) {
        fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
        return NULL;
    }
    
    // 读入bitmap信息头
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    // 将文件指针移至bitmap数据
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
    // 为装载图像数据创建足够的内存
    
    
    if (bitmapInfoHeader->biHeight < 0)
        bitmapInfoHeader->biHeight *= -1;
    
    if (bitmapInfoHeader->biBitCount == 24){
        bitmapInfoHeader->biSizeImage = 3 * bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth;
        
        bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
        // 验证内存是否创建成功
        if (!bitmapImage) {
            fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
            return NULL;
        }
        
        // 读入bitmap图像数据
        fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
        // 确认读入成功
        if (bitmapImage == NULL) {
            fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
            return NULL;
        }
        
        //由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
        for (imageIdx = 0;
             imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3) {
            tempRGB = bitmapImage[imageIdx];
            bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
            bitmapImage[imageIdx + 2] = tempRGB;
        }
    }
    else{
        bitmapInfoHeader->biSizeImage = 3 * bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth;
        
        bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
        
        unsigned char* u = new unsigned char[4 * bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth];
        
        // 验证内存是否创建成功
        if (!bitmapImage) {
            fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
            return NULL;
        }
        
        // 读入bitmap图像数据
        fread(u, 1, 4 * bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth, filePtr);
        
        for (int i = 0; i < bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth; i++){
            bitmapImage[i * 3] = u[i * 4];
            bitmapImage[i * 3 + 1] = u[i * 4 + 1];
            bitmapImage[i * 3 + 2] = u[i * 4 + 2];
        }
        
        
        // 确认读入成功
        if (bitmapImage == NULL) {
            fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
            return NULL;
        }
        
        //由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
        for (imageIdx = 0;
             imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3) {
            tempRGB = bitmapImage[imageIdx];
            bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
            bitmapImage[imageIdx + 2] = tempRGB;
        }
    }
    // 关闭bitmap图像文件
    fclose(filePtr);
    
    
    
    
    printf("load BMP succeed!!!\n");
    
    return bitmapImage;
}



unsigned char *CreateMyBmp(BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;	// 文件指针
    BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
    unsigned char	*bitmapImage;		// bitmap图像数据
    int	imageIdx = 0;		// 图像位置索引
    unsigned char	tempRGB;	// 交换变量
    
    
    bitmapInfoHeader->biWidth = 640;
    bitmapInfoHeader->biHeight = 480;
    bitmapInfoHeader->biSizeImage = 640 * 480 * 3;
    bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
    
    
    //unsigned char a[480][640];
    
    int x = 0;
    int y = 0;
    
    for (int i = 0; i < 480; i++){
        if (i % 50 == 0)
            x = 1 - x;
        
        if (x)
            y = 0;
        else
            y = 1;
        
        for (int j = 0; j < 640; j++){
            if (j % 50 == 0)
                y = 1 - y;
            
            if (y){
                bitmapImage[i * 640 * 3 + 3 * j] = 255;
                bitmapImage[i * 640 * 3 + 3 * j + 1] = 0;
                bitmapImage[i * 640 * 3 + 3 * j + 2] = 0;
            }
            else{
                bitmapImage[i * 640 * 3 + 3 * j] = 0;
                bitmapImage[i * 640 * 3 + 3 * j + 1] = 0;
                bitmapImage[i * 640 * 3 + 3 * j + 2] = 0;
            }
        }
    }
    
    
    return bitmapImage;
}


void texload(GLuint& texture, char *filename)
{
    
    BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
    unsigned char*   bitmapData;                                       // 纹理数据
    glBindTexture(GL_TEXTURE_2D, texture);
    
    
    cout << "In texLoad :: " << filename << endl;
    bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
    
    // 指定当前纹理的放大/缩小过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0, 	    //mipmap层次(通常为，表示最上层)
                 GL_RGB,	//我们希望该纹理有红、绿、蓝数据
                 bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2
                 bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2
                 0, //边框(0=无边框, 1=有边框)
                 GL_RGB,	//bitmap数据的格式
                 GL_UNSIGNED_BYTE, //每个颜色数据的类型
                 bitmapData);	//bitmap数据指针
}
