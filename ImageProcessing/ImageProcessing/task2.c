#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
void histogram(int hist[]) {
	int H = 200;
	unsigned char* out = calloc(256 * H, 1);
	memset(out, 0, 256 * H);
	int max = hist[0];
	for (int i = 1; i < 256; ++i) {
		if (hist[i] > max) max = hist[i];
	}
	for (int x = 0; x < 256; x++) {
		int bar_h = (int)((double)hist[x] / max * (H - 1));
		for (int y = 0; y < bar_h; y++) {
			out[(H - 1 - y) * 256 + x] = 255;
		}
	}
	stbi_write_jpg("D:\\USTC\\Program\\ImageProcessing\\ImageProcessing\\TestData\\hist_lena_1.jpg", 256, H, 1, out, 100);
	free(out);
}//绘制直方图

void generateHist(unsigned char* image, int* hist, int width, int height) {
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			hist[image[trans(row, column, width)]]++;
		}
	}
	
}//计算灰度值

void equalization(unsigned char* image, unsigned char* output, int* originHist, int width, int height) {
	double temp[256] = { 0 };
	temp[0] = originHist[0];
	for (int i = 1; i < 256; i++) {
		temp[i] = temp[i - 1] + originHist[i];
	}
	for(int i=0; i < 256; i++) {
		temp[i] /= (width * height);
	}
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			output[trans(row, column, width)] = (int)((L - 1) * temp[image[trans(row, column, width)]] + 0.5);
		}
	}
}//图像均衡化