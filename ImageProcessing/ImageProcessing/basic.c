#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
int trans(int row, int column, int width) {
	return row * width + column;
}//将二维坐标转换为一维坐标

double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}//计算两点间距离的函数

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