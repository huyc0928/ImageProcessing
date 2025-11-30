#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.14159265358979323846
#define L 256
//最近邻插值法的函数
void nearestNeighbor(unsigned char* image, unsigned char* output, int i, int origini, int width, int height);
//计算距离的函数
double distance(double coordinate[][2], int dim);
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

//均值滤波函数
int averageFilter(unsigned char* image, int row, int column, int width, int height, int filterSize);
//中位数计算函数
int median(int arr[], int n);
//中值滤波函数
int medianFilter(unsigned char* image, int row, int column, int width, int height, int filterSize);


//将二维坐标转换为一维坐标（RGB图像）
int transRGB(int row, int column, int width, int channel);
//随机选择K个中心
void randChoose(unsigned char* image, unsigned char* temp, int width, int height, int K);
//判断是否收敛
int convergence(unsigned char* temp0, unsigned char* temp1, int K, int width, int height);