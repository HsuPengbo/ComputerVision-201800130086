//
// Created by Xu Pengbo on 2020/9/25.
//
#ifndef CV_E2_E2_2_H
#define CV_E2_E2_H
#include "E2.h"
int Value2;
const int MaxSize2=200;
char TrackbarName2[50];
Mat imgI,imgB;
Mat Image_Composite(const Mat &Img1, const Mat &Img2,int p){//E2-2
    Mat Tag;
    subtract(Img1,Img2,Tag);
    int r=Tag.rows,c=Tag.cols, inStep=Tag.step, Channels=Tag.channels(),Step=Tag.step;
    Mat Mask;Mask.create(r, c, CV_8UC3);
    int outStep=Mask.step,MaskChannels=Mask.channels();
    uchar* Tdata=Tag.data,* MaskD=Mask.data,* I1data=Img1.data; int d;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            d=0;
            for(int k=0;k<Channels;++k){
                d+= Tdata[i * Step + j * Channels + k] * Tdata[i * Step + j * Channels + k];
            }
            d=sqrt(d);
            if(d<p) {
                for (int k = 0; k < Channels; ++k) {
                    MaskD[i * outStep + j * Channels + k] = 0;
                }
            }
            else{
                for(int k=0;k<Channels;++k){
                    MaskD[i * outStep + j * Channels + k]=255;
                }
            }
        }
    }
    return Mask;
}
int OTSU(const Mat img)
{
    int T=0; //阈值
    double curValue=0; //类间方差中间值保存
    double w0=0; //前景像素点数所占比例
    double w1=0; //背景像素点数所占比例
    double u0=0; //前景平均灰度
    double u1=0; //背景平均灰度
    double Huidu[256]={0}; //灰度直方图，灰度值对应的像素点总数
    uchar *data=img.data;
    double totalNum= img.rows * img.cols; //像素总数
    //计算灰度直方图
    for(int i=0; i < img.rows; i++)
    {
        for(int j=0; j < img.cols; j++)
        {
            Huidu[data[i * img.step + j]]++;
        }
    }
    for(int i=0;i<255;i++)
    {
        w1=0;   u1=0;   w0=0;   u0=0;
        for(int j=0;j<=i;j++)
        {
            w1+=Huidu[j];
            u1+= j * Huidu[j];
        }
        if(w1==0) //背景部分像素点数为0
        {
            continue;
        }
        u1=u1/w1; //背景平均灰度
        w1=w1/totalNum; // 背景所占比例
        for(int k=i+1;k<255;k++)
        {
            w0+=Huidu[k];  //前景部分总数
            u0+= k * Huidu[k]; //前景部分总灰度和
        }
        if(w0==0) //前景部分像素点数为0
        {
            break;
        }
        u0=u0/w0; //前景平均灰度
        w0=w0/totalNum; // 前景部分所占比例

        double varValueI=w0*w1*(u1-u0)*(u1-u0); //当前类间方差计算
        if(curValue < varValueI)
        {
            curValue=varValueI;
            T=i;
        }
    }
    return T;
}

void on_Trackbar2(int,void*)//回调函数
{
    if (Value2 < 1)
    {
        Value2 = 1; setTrackbarPos(TrackbarName2, WindowName, Value2);
    }
    Mat element = getStructuringElement(MORPH_RECT, Size(Value2, Value2));
    Mat mask=Image_Composite(imgI,imgB,Value2);
    imshow(WindowName,mask);
}
void playWindow2(){
    Value2=60;
    namedWindow(WindowName, WINDOW_AUTOSIZE);
    sprintf(TrackbarName1, "e");
    createTrackbar(TrackbarName2, WindowName, &Value2, MaxSize2, on_Trackbar2);
    on_Trackbar2(0, 0);
}
#endif //CV_E2_E2_2_H