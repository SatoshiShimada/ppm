
/*
 * PPM picture image edit tools.
 */

#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_OK		1
#define FILE_NO		0
#define PPM_HEADER_OK		1
#define PPM_HEADER_ERROR	0

FILE *fin;
char f_setfile = FILE_NO;
char f_allocate = 0;;
unsigned char *image;

unsigned char *ppm_get_image(void);
int is_fileset(void);
int is_ppm_header(void);
static int ppm_write(FILE *fp, PPM_DATA data);

/*
 * read header of ppm image.
 */
PPM_DATA ppm_get_header(void)
{
	PPM_DATA header;
	int pos;
	char buf[1024];
	char *p;
	int i;

	if(is_fileset()) return header;

	pos = ftell(fin);
	fseek(fin, 3, SEEK_SET);
	for(i = 0; i < 2; ) {
		fgets(buf, sizeof(buf), fin);
		if(buf[0] == '#') {
			//header.comment = buf;
		} else {
			if(i == 0) {
				p = strchr(buf, ' ');
				if(p == NULL) return header;
				*p = '\0';
				header.width = atoi(buf);
				p++;
				header.height = atoi(p);
			} else if(i == 1) {
				header.max_color = atoi(buf);
				printf("max color: %d, %s\n", header.max_color, buf);
			}
			i++;
		}
	}
	fseek(fin, pos, SEEK_SET);

	header.image_size = (header.width * header.height * 3);

	header.data = ppm_get_image();

	return header;
}

unsigned char *ppm_get_image(void)
{
	char buf[1024];
	size_t size;
	int i;

	fseek(fin, 0, SEEK_END);
	size = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	for(i = 0; i != 3;) {
		fgets(buf, sizeof(buf), fin);
		if(buf[0] == '#') continue;
		i++;
	}
	size -= ftell(fin);		

	image = (unsigned char *)malloc(size);
	if(image == NULL) return NULL;
	f_allocate = 1;

	fread(image, 1, size, fin);
	return image;
}

/*
 * open file.
 */
int ppm_set_file(char *filename)
{
	fin = fopen(filename, "rb");
	if(!fin) {
		fprintf(stderr, "file open error\n");
		f_setfile = FILE_NO;
		return -1;
	}
	f_setfile = FILE_OK;

	if(is_ppm_header() == PPM_HEADER_ERROR) {
		fprintf(stderr, "file is not ppm image file\n");
		f_setfile = FILE_NO;
		return -2;
	} else {
		return 0;
	}
}

int is_fileset(void)
{
	if(f_setfile == FILE_OK) {
		return 0;
	} else {
		fprintf(stderr, "please PPM file import\n");
		return -1;
	}
}

int is_ppm_header(void)
{
	int pos;
	unsigned char buf[10];

	if(is_fileset()) return -1;

	pos = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	fread(buf, 1, 2, fin);
	fseek(fin, pos, SEEK_SET);

	if(buf[0] == 'P' && buf[1] == '6') {
		return PPM_HEADER_OK;
	} else {
		return PPM_HEADER_ERROR;
	}
}

int ppm_exit(void)
{
	if(f_allocate == 0) return 1;
	if(image == NULL) return 1;

	free(image);
	f_allocate = 0;
	return 0;
}

int ppm_image_write(char *filename, PPM_DATA data)
{
	FILE *fp;

	fp = fopen(filename, "wb");
	if(!fp) return -1;

	ppm_write(fp, data);

	fclose(fp);
	return 0;
}

static int ppm_write(FILE *fp, PPM_DATA data)
{
	fprintf(fp, "P%d\n%d %d\n%d\n", 6, data.width, data.height, data.max_color);
	fwrite(data.data, 1, data.width * data.height * 3, fp);

	return 0;
}

