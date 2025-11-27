#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265358979323846
void task1(unsigned char* image, unsigned char* output, int width, int height, int channels);
//task1的主函数
void nearestNeighbor(unsigned char* image, unsigned char* output, int i, int origini, int width, int height);
//最近邻插值法的函数
double distance(double x1, double y1, double x2, double y2);
//计算两点间距离的函数（貌似没用）
