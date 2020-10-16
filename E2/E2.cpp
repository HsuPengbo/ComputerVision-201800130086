//
// Created by Xu Pengbo on 2020/9/25.
//
#include "E2_1.h"
#include "E2_2.h"
int main()
{
    img1= imread("D:\\Codes\\CV_works\\CV-E2\\E2_1.JPG");
    imgI = imread("D:\\Codes\\CV_works\\CV-E2\\bgs-data\\02.JPG");
    imgB = imread("D:\\Codes\\CV_works\\CV-E2\\bgs-data\\02_bg.JPG");
    //imshow("原图",img1);
    //playWindow1();
    playWindow2();
    int t= OTSU(imgI);
    Mat C=Image_Composite(imgI, imgB,t);
    imshow("OTSU-Mask",C);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
