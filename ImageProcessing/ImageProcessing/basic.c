#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
int trans(int row, int column, int width) {
	return row * width + column;
}//将二维坐标转换为一维坐标

double distance(double coordinate[][2],int dim) {
	double sum = 0;
	for (int i = 0; i < dim; i++) {
		sum += (coordinate[i][0] - coordinate[i][1]) * (coordinate[i][0] - coordinate[i][1]);
	}
	return sqrt(sum);
}//计算距离的函数

int median(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return arr[(n - 1) / 2];
}

int transRGB(int row, int column, int width, int channel) {
	return (row * width + column) * 3 + channel;
}//将二维坐标转换为一维坐标（RGB图像）