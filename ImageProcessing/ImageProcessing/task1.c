#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
void nearestNeighbor(unsigned char* image, unsigned char* output, int i, int origini, int width, int height) {
	if (origini >= width * height || origini < 0) {
		output[i] = 0;//边界处理
	}
	else {
		output[i] = image[origini];
	}
}//最近邻插值法

void bilinearNeighbor(unsigned char* image, unsigned char* output, int row, int column, double originrow, double origincolumn, int width, int height, int newWidth, int newHeight) {
	if (trans(originrow, origincolumn, width) >= width * height || trans(originrow, origincolumn, width) < 0) {
		output[trans(row, column, newWidth)] = 0;//边界处理
	}
	else {
		int f_a = image[trans((int)originrow, (int)origincolumn, width)];
		int f_b = image[trans((int)originrow, (int)origincolumn + 1, width)];
		int f_c = image[trans((int)originrow + 1, (int)origincolumn, width)];
		int f_d = image[trans((int)originrow + 1, (int)origincolumn + 1, width)];
		double f_e = (originrow - (int)originrow) * (f_c - f_a) + f_a;
		double f_f = (originrow - (int)originrow) * (f_d - f_b) + f_b;
		double f_xy = (origincolumn - (int)origincolumn) * (f_f - f_e) + f_e;
		if (f_xy > 255) {
			f_xy = 255;
		}
		else if(f_xy < 0) {
			f_xy = 0;
		}
		output[trans(row, column, newWidth)] = f_xy;
	}
}//双线性插值法

