
#include "cv.h"
#include "highgui.h"
#include "ctype.h"

int main(void)
{
	IplImage *src_img = 0;
	IplImage *dst_img = 0;
	IplImage *gray_img = 0;
	IplImage *gray_img2 = 0;
	char *filename = (char *)"out_2.png";
	unsigned char r, g, b;
	unsigned char t = 220;
	int x, y;
	int i;
	int temp;
	float *p;
	CvMemStorage *storage;
	CvSeq *circles = 0;

	src_img = cvLoadImage(filename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	dst_img = cvCloneImage(src_img);

	gray_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	gray_img2 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);

	////////////////////////////////////////////////
	cvCvtColor(src_img, gray_img, CV_BGR2GRAY);
	/*
	cvAnd(dst_img, src_img, dst_img);
	cvCvtColor(dst_img, gray_img2, CV_BGR2GRAY);

	cvCanny(gray_img2, gray_img, 50.0, 200.0);
	*/

	cvSmooth(gray_img, gray_img, CV_GAUSSIAN, 3, 3, 0, 0);

	storage = cvCreateMemStorage(0);
	circles = cvHoughCircles(gray_img, storage, CV_HOUGH_GRADIENT, 1, 100, 20, 50, 10,
		MAX(gray_img->width, gray_img->height));
	for(i = 0; i < circles->total; i++) {
		p = (float *)cvGetSeqElem(circles, i);
		cvCircle(src_img, cvPoint(cvRound(p[0]), cvRound(p[1])), 3, CV_RGB(0, 255, 0), -1, 8, 0);
		cvCircle(src_img, cvPoint(cvRound(p[0]), cvRound(p[1])), cvRound(p[2]), CV_RGB(255, 0, 0), 2, 8, 0);
	}
	/*
	CvSeq *lines = 0;
	CvPoint *point;
	lines = cvHoughLines2(gray_img, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 50, 50, 10);
	for(i = 0; i < lines->total; i++) {
		point = (CvPoint *)cvGetSeqElem(lines, i);
		cvLine(src_img, point[0], point[1], CV_RGB(0, 0, 255), 3, 8, 0);
	}
	*/
	////////////////////////////////////////////////
	// save image to file
	//cvSaveImage("out_2.png", src_img);
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
