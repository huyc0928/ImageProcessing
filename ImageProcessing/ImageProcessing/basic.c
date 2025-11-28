#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
int trans(int row, int column, int width) {
	return row * width + column;
}

double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}