#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
void randChoose(unsigned char* image, unsigned char* temp, int width, int height, int K) {
	srand((unsigned int)(time(NULL)));
	int selected[256 * 256] = { 0 };//记录已经选择的点
	for (int i = 0; i < K; i++) {
		int r, c;
		do {
			r = rand() % height;
			c = rand() % width;
		} while (selected[trans(r, c, width)] == 1);
		selected[trans(r, c, width)] = 1;
		for (i = 0; i < 3; i++) {
			temp[K * 3 + i] = image[transRGB(r, c, width, i)];
		}
	}
}//随机选择K个中心

void kmeans(unsigned char* image, unsigned char* temp0, unsigned char* temp1, int K, int width, int height) {
	int sort[64][4] = { 0 };
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			int nearest = 0;
			unsigned char coordinate[3][2] = { {image[transRGB(r,c,width,0)],temp0[0]},{image[transRGB(r,c,width,1)],temp0[1]} ,{image[transRGB(r,c,width,1)],temp0[2]} };
			double minDistance = distance(coordinate, 3);
			for (int i = 1; i < K; i++) {
				unsigned char coordinate[3][2] = { {image[transRGB(r,c,width,0)],temp0[i * 3 + 0]},{image[transRGB(r,c,width,1)],temp0[i * 3 + 1]} ,{image[transRGB(r,c,width,2)],temp0[i * 3 + 2]} };
				if (distance(coordinate, 3) < minDistance) {
					minDistance = distance(coordinate, 3);
					nearest = i;
				}
			}
			sort[nearest][4]++;
			for (int i = 0; i < 3; i++) {
				sort[nearest][i] += image[transRGB(r, c, width, i)];
			}
		}
	}

}

int convergence(unsigned char* temp0, unsigned char* temp1, int K, int width, int height) {
	int flag = 1;
	for (int i = 0; i < K * width * height * 3; i++) {
		if (temp0[i] != temp1[i]) {
			flag = 0;
			break;
		}
	}
	return flag;
}//判断是否收敛