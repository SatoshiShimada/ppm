
#include "cv.h"
#include "highgui.h"
#include "ctype.h"

int main(void)
{
	IplImage *src_img = 0;
	IplImage *dst_img = 0;
	IplImage *gray_img = 0;
	IplImage *gray_img2 = 0;
	char *filename = (char *)"image_320x240.png";
	unsigned char r, g, b;
	int x, y;
	int i;
	int temp;
	float *p;
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *contours = 0;
	CvBox2D ellipse;
	CvTreeNodeIterator it;
	CvPoint2D32f pt[4];

	src_img = cvLoadImage(filename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	dst_img = cvCloneImage(src_img);

	gray_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	gray_img2 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);

	////////////////////////////////////////////////
	for(y = 0; y < dst_img->height; y++) {
		for(x = 0; x < dst_img->width; x++) {
			b = dst_img->imageData[dst_img->widthStep * y + x * 3 + 0];
			g = dst_img->imageData[dst_img->widthStep * y + x * 3 + 1];
			r = dst_img->imageData[dst_img->widthStep * y + x * 3 + 2];
			if(r < 100 || b < 100) {
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 0] = 0x00;
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 1] = 0x00;
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 2] = 0x00;
			}
		}
	}
	////////////////////////////////////////////////
	// save image to file
	//cvSaveImage("out_5.png", gray_img);
	////////////////////////////////////////////////
	cvNamedWindow("Source", CV_WINDOW_AUTOSIZE);
	cvShowImage("Source", src_img);
	cvNamedWindow("Threshold", CV_WINDOW_AUTOSIZE);
	cvShowImage("Threshold", dst_img);
	cvNamedWindow("Gray", CV_WINDOW_AUTOSIZE);
	cvShowImage("Gray", gray_img);

	cvWaitKey(0);

	cvDestroyWindow("Source");
	cvDestroyWindow("Threshold");
	cvDestroyWindow("Gray");

	cvReleaseImage(&src_img);
	cvReleaseImage(&dst_img);

	return 0;
}
