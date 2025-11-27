#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265358979323846
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "D:\USTC\Program\ImageProcessing\stb_image.h"
#include "D:\USTC\Program\ImageProcessing\stb_image_write.h"
#include "task.h"
//void task1(unsigned char* image, unsigned char* output, int width, int height, int channels);
//void nearestNeighbor(unsigned char* image, unsigned char* output, int i, int origini, int width, int height);
//double distance(double x1, double y1, double x2, double y2);
int main()
{
	int width, height, channels;
	unsigned char* image = stbi_load("D:\\USTC\\Program\\ImageProcessing\\ImageProcessing\\TestData\\alphabet1.jpg", &width, &height, &channels, 1);//读入图像用的函数
	unsigned char* output = (unsigned char*)malloc(width * height * channels);
	int ctrl;
	printf("要进行何种操作？\n1-图像的平移旋转和放缩\n2-图像的直方图均衡化\n3-图像的空间域滤波去噪\n4-彩色图像的K-means算法有损压缩\n5-图像的频率域滤波\n6-图像的四叉树分裂合并算法\n");
	scanf("%d", &ctrl);
	switch (ctrl) {
	case 1:
		task1(image, output, width, height, channels);
		break;
	}
	stbi_write_jpg("D:\\USTC\\Program\\ImageProcessing\\ImageProcessing\\TestData\\task1.jpg", width, height, 1, output, 100);//写出函数的图像
	stbi_image_free(image);
	free(output);//释放内存的函数
	return 0;
}

