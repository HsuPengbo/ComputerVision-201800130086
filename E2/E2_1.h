//
// Created by Xu Pengbo on 2020/9/25.
//
#ifndef CV_E2_E2_1_H
#define CV_E2_E2_1_H
#include "E2.h"
int Value1;
const int MaxSize1=100;
char TrackbarName1[50];
Mat img1,img2;
uchar sigmoid(uchar x,float e){//sigmoid函数
    float z=(float) x; uchar y;
    z=255.0/(1+exp((127.5-z)/e));
    y=(uchar) z; return y;
}
void Contrast_Adjustment(const Mat &In, Mat &Out, float e){ //E2-1
    int r=In.rows,c=In.cols, inStep=In.step, inChannel=In.channels(),outStep=Out.step;
    uchar* InM = In.data;   uchar* OutM = Out.data;
    for(int row=0;row<r;row++){
        for(int col=0;col<c;col++){
            for(int i=0;i<inChannel;++i){
                OutM[row * outStep + col * inChannel + i]=sigmoid(InM[row * inStep + col * inChannel + i],e);
            }
        }
    }
    imshow(WindowName, Out);
}
void on_Trackbar1(int,void*)//回调函数
{
    if (Value1 < 1)
    {
        Value1 = 1; setTrackbarPos(TrackbarName1, WindowName, Value1);
    }
    Mat element = getStructuringElement(MORPH_RECT, Size(Value1, Value1));
    img1.copyTo(img2);
    Contrast_Adjustment(img1, img2, (float)Value1);
}
void playWindow1(){
    Value1=10;
    namedWindow(WindowName, 0);
    sprintf(TrackbarName1, "e");
    createTrackbar(TrackbarName1, WindowName, &Value1, MaxSize1, on_Trackbar1);
    on_Trackbar1(0, 0);
}
#endif //CV_E2_E2_1_H
