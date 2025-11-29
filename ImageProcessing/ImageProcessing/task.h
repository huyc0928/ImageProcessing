#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265358979323846
#define L 256
//最近邻插值法的函数
void nearestNeighbor(unsigned char* image, unsigned char* output, int i, int origini, int width, int height);
//计算两点间距离的函数（貌似没用）
double distance(double x1, double y1, double x2, double y2);
//将二维坐标转换为一维坐标
int trans(int row, int column, int width);
//双线性插值法函数
void bilinearNeighbor(unsigned char* image, unsigned char* output, int row, int column, double originrow, double origincolumn, int width, int height, int newWidth, int newHeight);

//绘制直方图函数
void histogram(int hist[]);
//计算灰度值函数
void generateHist(unsigned char* image, int* hist, int width, int height);
//图像均衡化函数
void equalization(unsigned char* image, unsigned char* output, int* originHist, int width, int height);