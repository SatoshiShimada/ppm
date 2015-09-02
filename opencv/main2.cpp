
#include "cv.h"
#include "highgui.h"
#include "ctype.h"

int main(void)
{
	CvCapture *capture = 0;
	IplImage *src_img = 0;
	IplImage *src_img_gray = 0;
	IplImage *dst_img = 0;
	IplImage *dst_img_smooth = 0;
	double w = 320, h = 240;
	int c;
	int i;
	char *filename = (char *)"image_320x240.png";

	src_img = cvLoadImage(filename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

	dst_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	dst_img_smooth = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);

	////////////////////////////////////////////////////////////
	//cvSmooth(src_img, dst_img, CV_BLUR, 5, 0, 0, 0);
	src_img_gray = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	cvCvtColor(src_img, src_img_gray, CV_BGR2GRAY);
	cvThreshold(src_img_gray, dst_img, 138, 255, CV_THRESH_BINARY);

	cvSmooth(src_img_gray, src_img_gray, CV_GAUSSIAN, 5);
	cvThreshold(src_img_gray, dst_img_smooth, 139, 255, CV_THRESH_BINARY);
	////////////////////////////////////////////////////////////
	cvNamedWindow("Source", CV_WINDOW_AUTOSIZE);
	cvShowImage("Source", src_img);
	cvNamedWindow("Gray", CV_WINDOW_AUTOSIZE);
	cvShowImage("Gray", src_img_gray);
	cvNamedWindow("Threshold1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Threshold1", dst_img);
	cvNamedWindow("Threshold2", CV_WINDOW_AUTOSIZE);
	cvShowImage("Threshold2", dst_img_smooth);

	cvWaitKey(0);

	cvDestroyWindow("Gray");
	cvDestroyWindow("Source");
	cvDestroyWindow("Threshold1");
	cvDestroyWindow("Threshold2");

	cvReleaseImage(&src_img);
	cvReleaseImage(&src_img_gray);
	cvReleaseImage(&dst_img);

	return 0;
}
