
typedef struct {
	unsigned char *data;
	char filename[32];
	char *comment;
	int  width, height;
	int  max_color;
	int  image_size;
} PPM_DATA;

PPM_DATA ppm_get_header(void);
//unsigned char *ppm_get_image(void);
int ppm_set_file(char *);
int ppm_exit(void);
int ppm_image_write(char *, PPM_DATA);
