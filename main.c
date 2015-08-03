
#include <stdio.h>
#include "ppm.h"
#include "picture.h"

/*
 * smaple for ppm image and turn function.
 */
int main(void)
{
	PPM_DATA data;

	ppm_set_file("test.ppm");

	data = ppm_get_header();

	turn(data.data, data.width, data.height, 30);

	ppm_image_write("out.ppm", data);

	ppm_exit();

	return 0;
}
