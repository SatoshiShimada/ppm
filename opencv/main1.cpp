
#include "cv.h"
#include "highgui.h"
#include "ctype.h"

int main(void)
{
	CvCapture *capture = 0;
	IplImage *src_img = 0;
	IplImage *dst_img = 0;
	double w = 320, h = 240;
	int c;
	int i;
	char *filename = "image_320x240.png";

	src_img = cvLoadImage(filename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

	dst_img = cvCloneImage(src_img);

	cvSmooth(src_img, dst_img, CV_BLUR, 5, 0, 0, 0);

	cvNamedWindow("Sample", CV_WINDOW_AUTOSIZE);
	cvShowImage("Sample", dst_img);

	cvWaitKey(0);

	cvDestroyWindow("Sample");

	cvReleaseImage(&src_img);
	cvReleaseImage(&dst_img);

	return 0;
}
