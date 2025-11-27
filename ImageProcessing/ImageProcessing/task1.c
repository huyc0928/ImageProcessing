#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
void task1(unsigned char* image, unsigned char* output, int width, int height, int channels) {
	double originrow, origincolumn;//原图像位置
	double angle;//旋转的角度
	int centrerow, centrecolumn;
	int ctrl;
	printf("输入旋转的角度（角度制）：\n");
	scanf("%lf", &angle);
	printf("输入旋转中心的坐标（行和列）：\n");
	scanf("%d %d", &centrerow, &centrecolumn);
	printf("选择插值法：\n1-最近邻插值法\n2-双线性插值法\n");
	scanf("%d", &ctrl);
	angle = angle * PI / 180.0;//角度制转弧度制
	for (int i = 0; i < width * height; i++) {
		int row = i / width;
		int column = i % width;
		originrow = cos(angle) * (row - centrerow) - sin(angle) * (column - centrecolumn) + centrerow;
		origincolumn = sin(angle) * (row - centrerow) + cos(angle) * (column - centrecolumn) + centrecolumn;
		switch (ctrl) {
		case 1://最近邻插值法
			nearestNeighbor(image, output, i, round(originrow) * width + round(origincolumn), width, height);
			break;
		}
	}//按照要求，旋转只针对黑白图像进行处理
}//图像的平移旋转和放缩

void nearestNeighbor(unsigned char* image, unsigned char* output, int i, int origini, int width, int height) {
	if (origini >= width * height || origini < 0) {
		output[i] = 0;//边界处理
	}
	else {
		output[i] = image[origini];
	}
}//最近邻插值法

double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}