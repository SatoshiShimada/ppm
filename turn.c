#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
	#define M_PI		3.141592
#endif

#include "picture.h"

/*
 * turn image for degree
 */
int turn(unsigned char *image, int width, int height, int deg)
{
	int i, j;
	int x, y;
	double rad;
	unsigned char *data;

	rad = deg * (M_PI / 180);

	data = (unsigned char *)malloc(width * height * 3);
	if(!data) return -2;

	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			x = (j * cos(rad)) - (i * sin(rad));
			y = (j * sin(rad)) + (i * cos(rad));

			if(x < 0) continue;
			if(x > width) continue;
			if(y < 0) continue;
			if(y > height) continue;

			data[(i * width + j) * 3 + 0] = image[(y * width + x) * 3 + 0];
			data[(i * width + j) * 3 + 1] = image[(y * width + x) * 3 + 1];
			data[(i * width + j) * 3 + 2] = image[(y * width + x) * 3 + 2];
		}
	}

	memcpy(image, data, width * height * 3);
	free(data);

	return 0;
}
