#include "E4_gauss.h"
#include "E4_mean.h"
#include <time.h>
#define windowName "效果图"
Mat img,outImg1,outImg2;
string trackbar1 = "高斯滤波参数";
string trackbar2 = "快速均值滤波参数";
int value1;
int value2;
int Max1=200;
int Max2=20;
void imshow_2(const string& winName, const Mat& img1,const Mat& img2)
{
    Mat Display;
    int W=img1.cols, H=img1.rows;
    Display.create(H,2*W+100,CV_8UC3);
    for(int i=0;i<H;i++) {
        for (int j = 0; j < W; j++) {
            Display.ptr(i,j)[0]=img1.ptr(i,j)[0];
            Display.ptr(i,j)[1]=img1.ptr(i,j)[1];
            Display.ptr(i,j)[2]=img1.ptr(i,j)[2];
        }
        for (int j = W; j < W+100; j++){
            Display.ptr(i,j)[0]=255;
            Display.ptr(i,j)[1]=255;
            Display.ptr(i,j)[2]=255;
        }
        for (int j = 0; j < W; j++) {
            Display.ptr(i,j+100+W)[0]=img2.ptr(i,j)[0];
            Display.ptr(i,j+100+W)[1]=img2.ptr(i,j)[1];
            Display.ptr(i,j+100+W)[2]=img2.ptr(i,j)[2];
        }
    }
    namedWindow(winName);
    imshow(winName, Display);
}
void on_Trackbar1(int,void*){
    if (value1 < 1)
    {
        value1 = 1; setTrackbarPos(trackbar1,windowName, value1);
    }
    Mat element1 = getStructuringElement(MORPH_RECT, Size(value1, value1));
    Gaussian(img,outImg1,(double )value1/20.0);
    imshow_2(windowName, outImg1,outImg2);
}
void on_Trackbar2(int,void*){
    if (value2 < 1)
    {
        value2 = 1; setTrackbarPos(trackbar1,windowName, value2);
    }
    Mat element2 = getStructuringElement(MORPH_RECT, Size(value2, value2));
    MeanFilter(img,outImg2,value2);
    imshow_2(windowName, outImg1,outImg2);
}
void play1(){
    value1=5;value2=5;
    namedWindow( windowName,WINDOW_AUTOSIZE);
    createTrackbar(trackbar1,windowName,&value1,Max1,on_Trackbar1);
    createTrackbar(trackbar2,windowName,&value2,Max2,on_Trackbar2);
    on_Trackbar1(0,0);
    on_Trackbar2(0,0);
}
void play2(){
    clock_t start,end,start2,end2;
    start=clock();
    boxFilter( img, outImg1, 0,Size(15, 15));
    end=clock();
    cout<<"盒滤波用时:"<<float(end-start)<<"ms"<<endl;
    start2=clock();
    MeanFilter(img,outImg2,15);
    end2=clock();
    cout<<"快速均值滤波用时:"<<float(end2-start2)<<"ms"<<endl;
    imshow("盒滤波",outImg1);
    imshow("快速均值滤波",outImg2);
}
int main() {
    img =imread("D:\\Codes\\CV\\CV_works\\CV-E4\\images\\pic1.JPG");
    //imshow("原图",img);
    img.copyTo(outImg1);
    img.copyTo(outImg2);
    play1();
    //play2();
    waitKey(0);
    destroyAllWindows();
    return 0;
}
