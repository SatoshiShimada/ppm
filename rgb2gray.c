
#include "ppm.h"
#include <stdio.h>

int rgb2gray(unsigned char *image, int width, int height)
{
	int r, g, b;
	int i, j;
	unsigned char gray;
	int index;

	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			index = (i * width + j) * 3;
			r = 0.2989 * image[index + 0];
			g = 0.5870 * image[index + 1];
			b = 0.1140 * image[index + 2];

			gray = (unsigned char)(r + g + b);
			image[index + 0] = gray;
			image[index + 1] = gray;
			image[index + 2] = gray;
		}
	}
	printf("%d, %d\n", i, j);

	return 0;
}
