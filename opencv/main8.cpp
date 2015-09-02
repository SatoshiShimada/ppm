
#include "cv.h"
#include "highgui.h"
#include "ctype.h"

int main(void)
{
	IplImage *src_img = 0;
	IplImage *src_img_gray = 0;
	IplImage *dst_img = 0;
	IplImage *dst_img1 = 0;
	IplImage *dst_img2 = 0;
	IplImage *tmp_img = 0;
	IplImage *out1 = 0, *out2 = 0, *out3 = 0;
	char *filename = (char *)"image_320x240.png";
	int x, y;
	unsigned char r, g, b;

	src_img = cvLoadImage(filename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	tmp_img = cvCloneImage(src_img);
	dst_img = cvCloneImage(src_img);

	dst_img1 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	dst_img2 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	out1 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	out2 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	out3 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);

	////////////////////////////////////////////////////////////
	src_img_gray = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	cvCvtColor(src_img, src_img_gray, CV_BGR2GRAY);
	cvThreshold(src_img_gray, dst_img1, 138, 255, CV_THRESH_BINARY);
	////////////////////////////////////////////////////////////
	for(y = 0; y < tmp_img->height; y++) {
		for(x = 0; x < tmp_img->width; x++) {
			b = tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 0];
			g = tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 1];
			r = tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 2];
			if(r < 100 || b < 100) {
				tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 0] = 0x00;
				tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 1] = 0x00;
				tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 2] = 0x00;
			} else {
				tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 0] = 0xff;
				tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 1] = 0xff;
				tmp_img->imageData[tmp_img->widthStep * y + x * 3 + 2] = 0xff;
			}
		}
	}
	cvCvtColor(tmp_img, dst_img2, CV_BGR2GRAY);
	////////////////////////////////////////////////////////////
	/* AND OR */
	cvAnd(dst_img1, dst_img2, out1, NULL);
	cvOr(dst_img1, dst_img2, out2, NULL);
	cvXor(dst_img1, dst_img2, out3);
	cvCvtColor(out2, tmp_img, CV_GRAY2BGR);
	cvAnd(src_img, tmp_img, dst_img);
	////////////////////////////////////////////////////////////
	cvNamedWindow("Source", CV_WINDOW_AUTOSIZE);
	cvShowImage("Source", src_img);
	cvNamedWindow("Threshold1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Threshold1", dst_img1);
	cvNamedWindow("Threshold2", CV_WINDOW_AUTOSIZE);
	cvShowImage("Threshold2", dst_img2);
	cvNamedWindow("AND", CV_WINDOW_AUTOSIZE);
	cvShowImage("AND", out1);
	cvNamedWindow("OR", CV_WINDOW_AUTOSIZE);
	cvShowImage("OR", out2);
	cvNamedWindow("EX_OR", CV_WINDOW_AUTOSIZE);
	cvShowImage("EX_OR", out2);
	cvNamedWindow("Robot vision", CV_WINDOW_AUTOSIZE);
	cvShowImage("Robot vision", dst_img);

	cvWaitKey(0);

	cvDestroyWindow("Source");
	cvDestroyWindow("Threshold1");
	cvDestroyWindow("Threshold2");
	cvDestroyWindow("AND");
	cvDestroyWindow("OR");
	cvDestroyWindow("EX_OR");
	cvDestroyWindow("Robot vision");

	cvReleaseImage(&src_img);
	cvReleaseImage(&src_img_gray);
	cvReleaseImage(&dst_img1);
	cvReleaseImage(&dst_img2);

	return 0;
}
