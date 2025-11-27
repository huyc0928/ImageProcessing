#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "D:\USTC\Program\ImageProcessing\stb_image.h"
#include "D:\USTC\Program\ImageProcessing\stb_image_write.h"
void task1(unsigned char* image, unsigned char* output, int width, int height, int channels);
void task1func1(unsigned char* image, unsigned char* output, int x, int y, double originx, double originy, int width, int height);
double distance(double x1, double y1, double x2, double y2);
int main()
{
	int width, height, channels;
	unsigned char* image = stbi_load("D:\\USTC\\Program\\ImageProcessing\\ImageProcessing\\TestData\\Girl.jpg", &width, &height, &channels, 1);//读入图像用的函数
	unsigned char* output;
	int ctrl;
	printf("要进行何种操作？\n1-图像的平移旋转和放缩\n2-图像的直方图均衡化\n3-图像的空间域滤波去噪\n4-彩色图像的K-means算法有损压缩\n5-图像的频率域滤波\n6-图像的四叉树分裂合并算法\n");
	scanf("%d", &ctrl);
	switch (ctrl) {
	case 1:
		task1(image, output, width, height, channels);
		break;
	}
	stbi_write_jpg("D:\\USTC\\Program\\ImageProcessing\\ImageProcessing\\TestData\\Girl1.jpg", width, height, 1, image, 100);//写出函数的图像
	stbi_image_free(image);
	stbi_image_free(output);//释放内存的函数
	return 0;
}

void task1(unsigned char* image, unsigned char* output, int width, int height, int channels) {
	double originx, originy;//原图像位置
	double angle;//旋转的角度
	printf("输入旋转的角度：\n");
	scanf("%lf", &angle);
	printf("选择插值法：\n1-最近邻插值法\n2-双线性插值法\n");
	int ctrl;
	scanf("%d", &ctrl);
	for (int x = 0; x < width; x++) {//x对应横坐标
		for (int y = 0; y < height; y++) {//y对应纵坐标
			originx = cos(angle) * x + sin(angle) * y;
			originy = -sin(angle) * x + cos(angle) * y;
			
			switch (ctrl) {
			case 1://最近邻插值法
				task1func1(image, output, x, y, originx, originy, width, height);
				break;
			}
		}
	}
}//图像的平移旋转和放缩

void task1func1(unsigned char* image, unsigned char* output, int x, int y, double originx, double originy, int width, int height) {
	int nearest[2] = { originx,originy };//0-3分别对应A（i，j）B（i，j+1）C（i+1，j）D（i + 1，j + 1)
	if (distance(nearest[0], nearest[1], originx, originy) > distance((int)originx, (int)originy + 1, originx, originy)) {
		nearest[0] = (int)originx;
		nearest[1] = (int)originy + 1;
	}
	if (distance(nearest[0], nearest[1], originx, originy) > distance((int)originx + 1, (int)originy, originx, originy)) {
		nearest[0] = (int)originx + 1;
		nearest[1] = (int)originy;
	}
	if (distance(nearest[0], nearest[1], originx, originy) > distance((int)originx + 1, (int)originy + 1, originx, originy)) {
		nearest[0] = (int)originx + 1;
		nearest[1] = (int)originy + 1;
	}//得到距离最近的点的坐标
	if (nearest[0] < 0 || nearest[0] >= height || nearest[1] < 0 || nearest[1] >= width) {
		output[x * width + y] = 0;//边界处理
	}
	else {
		output[x * width + y] = image[nearest[0] * width + nearest[1]];//赋值
	}
}//1-图像的平移旋转和放缩-1-最近邻插值法

double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}