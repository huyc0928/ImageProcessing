#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "D:\USTC\Program\ImageProcessing\stb_image.h"
#include "D:\USTC\Program\ImageProcessing\stb_image_write.h"
#include "task.h"
int main()
{
	int width, height, channels;
	int newWidth, newHeight;
	unsigned char* image = stbi_load("D:\\USTC\\Program\\ImageProcessing\\ImageProcessing\\TestData\\lena_random.jpg", &width, &height, &channels, 1);//读入图像用的函数
	unsigned char* output = NULL;
	int ctrl;
	printf("要进行何种操作？\n1-图像的平移旋转和放缩\n2-图像的直方图均衡化\n3-图像的空间域滤波去噪\n4-彩色图像的K-means算法有损压缩\n5-图像的频率域滤波\n6-图像的四叉树分裂合并算法\n");
	scanf("%d", &ctrl);
	if (ctrl == 1) {
		printf("1-旋转\n2-放缩\n");
		scanf("%d", &ctrl);
		double originrow, origincolumn;//原图像位置
		if (ctrl == 1) {
			output = (unsigned char*)malloc(width * height * channels);
			newWidth = width;
			newHeight = height;
			double angle;//旋转的角度
			int centrerow, centrecolumn;
			printf("输入旋转的角度（角度制）：\n");
			scanf("%lf", &angle);
			printf("输入旋转中心的坐标（行和列）：\n");
			scanf("%d %d", &centrerow, &centrecolumn);
			printf("选择插值法：\n1-最近邻插值法\n2-双线性插值法\n");
			scanf("%d", &ctrl);
			angle = angle * PI / 180.0;//角度制转弧度制
			for (int i = 0; i < width * height; i++) {
				int row = i / newWidth;
				int column = i % newWidth;
				originrow = cos(angle) * (row - centrerow) + sin(angle) * (column - centrecolumn) + centrerow;
				origincolumn = -sin(angle) * (row - centrerow) + cos(angle) * (column - centrecolumn) + centrecolumn;//旋转
				switch (ctrl) {
				case 1://最近邻插值法
					nearestNeighbor(image, output, i, round(originrow) * width + round(origincolumn), width, height);
					break;
				case 2://双线性插值法
					bilinearNeighbor(image, output, row, column, originrow, origincolumn, width, height, newWidth, newHeight);
					break;
				}
			}//按照要求，旋转只针对黑白图像进行处理
		}//旋转
		else if (ctrl == 2) {
			printf("输入放缩的比例（大于1为放大，小于1为缩小）：\n");
			double scale;
			scanf("%lf", &scale);
			newWidth = (int)(width * scale);
			newHeight = (int)(height * scale);
			output = (unsigned char*)malloc(newWidth * newHeight * channels);
			printf("选择插值法：\n1-最近邻插值法\n2-双线性插值法\n");
			scanf("%d", &ctrl);
			for (int i = 0; i < newWidth * newHeight; i++) {
				int row = i / newWidth;
				int column = i % newWidth;
				originrow = row / scale;
				origincolumn = column / scale;//放缩
				switch (ctrl) {
				case 1://最近邻插值法
					nearestNeighbor(image, output, i, round(originrow) * width + round(origincolumn), width, height);
					break;
				case 2://双线性插值法
					bilinearNeighbor(image, output, row, column, originrow, origincolumn, width, height, newWidth, newHeight);
					break;
				}
			}
		}//放缩
	}//图像的平移旋转和放缩
	else if (ctrl == 2) {
		int originHist[256] = { 0 };//原图像的灰度值
		generateHist(image, originHist, width, height);//计算原图像的灰度值
		histogram(originHist);//绘制原图像的直方图
		newWidth = width;
		newHeight = height;
		output = (unsigned char*)malloc(newWidth * newHeight * channels);
		equalization(image, output, originHist, width, height);//图像均衡化
		int newHist[256] = { 0 };//均衡化后的灰度值
		generateHist(output, newHist, newWidth, newHeight);//计算均衡化后的灰度值
		histogram(newHist);//绘制均衡化后的直方图
	}//图像的直方图均衡化
	else if (ctrl == 3) {
		printf("1-超限邻域均值滤波\n2-超限邻域中值滤波\n3-普通均值滤波\n4-普通中值滤波\n");
		scanf("%d", &ctrl);
		int filterSize, T = 0;
		printf("输入邻域大小（奇数）：\n");
		scanf("%d", &filterSize);
		if (ctrl == 1 || ctrl == 2) {
			printf("输入阈值大小：\n");
			scanf("%d", &T);
		}
		newWidth = width;
		newHeight = height;
		output = (unsigned char*)malloc(newWidth * newHeight * channels);
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (ctrl == 1 || ctrl == 3) {
					int ave = averageFilter(image, row, column, width, height, filterSize);
					if (abs(image[trans(row, column, width)] - ave) > T) {
						output[trans(row, column, width)] = ave;
					}
					else {
						output[trans(row, column, width)] = image[trans(row, column, width)];
					}
				}//（超限邻域）均值滤波
				else if (ctrl == 2 || ctrl == 4) {
					int mid = medianFilter(image, row, column, width, height, filterSize);
					if (abs(image[trans(row, column, width)] - mid) > T) {
						output[trans(row, column, width)] = mid;
					}
					else {
						output[trans(row, column, width)] = image[trans(row, column, width)];
					}
				}//（超限邻域）中值滤波
			}
		}
	}//图像的空间域滤波去噪
	else if (ctrl == 4) {
		int K;//K值
		printf("输入K值：\n");
		scanf("%d", &K);
		newWidth = width;
		newHeight = height;
		output = (unsigned char*)malloc(newWidth * newHeight * channels);
		unsigned char* temp0 = (unsigned char*)malloc(K * 3 * 2);
		unsigned char* temp1 = (unsigned char*)malloc(K * 3 * 2);
		randChoose(image, temp0, width, height, K);
		do {

		} while (!convergence(temp0, temp1, K, width, height));
	}//彩色图像的K-means算法有损压缩
	else if (ctrl == 5) {

	}//图像的频率域滤波
	else if (ctrl == 6) {

	}//图像的四叉树分裂合并算法
	stbi_write_jpg("D:\\USTC\\Program\\ImageProcessing\\ImageProcessing\\TestData\\lena_random_4.jpg", newWidth, newHeight, 3, output, 100);//写出函数的图像
	stbi_image_free(image);
	free(output);//释放内存的函数
	return 0;
}