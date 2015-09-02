
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
	for(y = 0; y < dst_img->height; y++) {
		for(x = 0; x < dst_img->width; x++) {
			b = dst_img->imageData[dst_img->widthStep * y + x * 3 + 0];
			g = dst_img->imageData[dst_img->widthStep * y + x * 3 + 1];
			r = dst_img->imageData[dst_img->widthStep * y + x * 3 + 2];
			if(b > 100 && r > 100) {
				if(g > 130) {
					temp = ((int)(b * 2) < 0xff) ? ((int)(b * 2)) : 0xff;
					dst_img->imageData[dst_img->widthStep * y + x * 3 + 0] = temp;
					temp = ((int)(g * 2) < 0xff) ? ((int)(g * 2)) : 0xff;
					dst_img->imageData[dst_img->widthStep * y + x * 3 + 1] = temp;
					temp = ((int)(r * 2) < 0xff) ? ((int)(r * 2)) : 0xff;
					dst_img->imageData[dst_img->widthStep * y + x * 3 + 2] = temp;
					continue;
				}
			}
			dst_img->imageData[dst_img->widthStep * y + x * 3 + 0] = b;
			dst_img->imageData[dst_img->widthStep * y + x * 3 + 1] = g;
			dst_img->imageData[dst_img->widthStep * y + x * 3 + 2] = r;
		}
	}
	for(y = 0; y < dst_img->height; y++) {
		for(x = 0; x < dst_img->width; x++) {
			b = dst_img->imageData[dst_img->widthStep * y + x * 3 + 0];
			g = dst_img->imageData[dst_img->widthStep * y + x * 3 + 1];
			r = dst_img->imageData[dst_img->widthStep * y + x * 3 + 2];
			if(b > t && g > t && r > t) {
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 0] = 0xff;
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 1] = 0xff;
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 2] = 0xff;
			} else {
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 0] = 0x00;
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 1] = 0x00;
				dst_img->imageData[dst_img->widthStep * y + x * 3 + 2] = 0x00;
			}
		}
	}
	cvSmooth(dst_img, dst_img, CV_GAUSSIAN, 11, 11, 0, 0);
	cvCvtColor(dst_img, gray_img, CV_BGR2GRAY);
	//cvCvtColor(src_img, gray_img, CV_BGR2GRAY);
	storage = cvCreateMemStorage(0);
	circles = cvHoughCircles(gray_img, storage, CV_HOUGH_GRADIENT, 1, 100, 20, 50, 10,
		MAX(gray_img->width, gray_img->height));
	for(i = 0; i < circles->total; i++) {
		p = (float *)cvGetSeqElem(circles, i);
		cvCircle(src_img, cvPoint(cvRound(p[0]), cvRound(p[1])), 3, CV_RGB(0, 255, 0), -1, 8, 0);
		cvCircle(src_img, cvPoint(cvRound(p[0]), cvRound(p[1])), cvRound(p[2]), CV_RGB(255, 0, 0), 3, 8, 0);
	}
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
