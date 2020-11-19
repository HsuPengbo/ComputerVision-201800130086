#include "E8.h"

int main() {
    Mat img1=imread("D:\\Codes\\CV\\CV_works\\CV_E8\\dataset\\10.jpg");
    hough(img1,60,160,25,75,95);
    //Mat img2=imread("D:\\Codes\\CV\\CV_works\\E8\\dataset\\7.jpg");
    //hough(img2,60,160,20,25,300);
    waitKey(0);
    return 0;
}
