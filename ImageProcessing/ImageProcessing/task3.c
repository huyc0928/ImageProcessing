#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
int averageFilter(unsigned char* image, int row, int column, int width, int height, int filterSize) {
	int sum = 0;
	row -= (filterSize - 1) / 2;
	column -= (filterSize - 1) / 2;
	for (int i = 0; i < filterSize; i++) {
		for (int j = 0; j < filterSize; j++) {
			if (row + i < 0 || row + i >= height || column + j < 0 || column + j >= width) {
				sum += 0;
			}
			else {
				sum += image[trans(row + i, column + j, width)];
			}
		}
	}
	return sum / (filterSize * filterSize);
}//均值滤波函数

int medianFilter(unsigned char* image, int row, int column, int width, int height, int filterSize) {
	row -= (filterSize - 1) / 2;
	column -= (filterSize - 1) / 2;
	int* temp = (int*)malloc(filterSize * filterSize * sizeof(int));
	int cnt = 0;
	for (int i = 0; i < filterSize; i++) {
		for (int j = 0; j < filterSize; j++) {
			if (row + i < 0 || row + i >= height || column + j < 0 || column + j >= width) {
				temp[cnt++] = 0;
			}
			else {
				temp[cnt++] = image[trans(row, column, width)];
			}
		}
	}
	return median(temp, filterSize * filterSize);
}//中值滤波函数