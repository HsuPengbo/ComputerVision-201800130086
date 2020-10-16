//
// Created by XuPengbo on 2020/10/1.
//

#ifndef CV_E3_E3_H
#define CV_E3_E3_H
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat Fun1(const Mat &img){
    int H=img.rows,W=img.cols;
    double p,q,r,theta,op,oq; int I,J;
    Mat Out;
    Out.create(H,W,img.type());
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            p=(double)(i-0.5*H)/(0.5*H);
            q=(double)(j-0.5*W)/(0.5*W);
            r=sqrt(p*p+q*q); theta=(1-r)*(1-r);
            if(r>=1) {
                op=p; oq=q;
            }
            else{
                op=cos(theta)*p-sin(theta)*q;
                oq=cos(theta)*q+sin(theta)*p;
            }
            I=int ((op+1)*0.5*H);
            J=int ((oq+1)*0.5*W);
            Out.at<Vec3b>(i,j)[0]=img.at<Vec3b>(I,J)[0];
            Out.at<Vec3b>(i,j)[1]=img.at<Vec3b>(I,J)[1];
            Out.at<Vec3b>(i,j)[2]=img.at<Vec3b>(I,J)[2];
        }
    }
    return Out;
}

Mat Fun2(const Mat &img,double a, double b){
    int H=img.rows,W=img.cols;
    int nH=int(a*H);
    int nW=int (b*W);
    Mat Out;Out.create(nH,nW,img.type());
    int I,J; double x,y;
    int Channels=Out.channels();
    uchar c1,c2;
    for(int i=0;i<nH;i++){
        for(int j=0;j<nW;j++){
            x=(double)i/a; y=(double)j/b;
            if(x>=H-1) x=H-1; if(x<=0) x=0;
            if(y>=W-1) y=W-1; if(y<=0) y=0;
            I=floor(x);J=floor(y);
            if((x==0&&y==0)||(x==H-1&&y==W-1)||(x==0&&y==W-1)||(x==H-1&&y==0)){
                Out.at<Vec3b>(i,j)[0]=img.at<Vec3b>(I,J)[0];
                Out.at<Vec3b>(i,j)[1]=img.at<Vec3b>(I,J)[1];
                Out.at<Vec3b>(i,j)[2]=img.at<Vec3b>(I,J)[2];
            }
            else if(x==0||x==H-1){
                Out.at<Vec3b>(i,j)[0]=img.at<Vec3b>(I,J)[0]+(img.at<Vec3b>(I,J)[0]-img.at<Vec3b>(I,J+1)[0])*(y-J);
                Out.at<Vec3b>(i,j)[1]=img.at<Vec3b>(I,J)[1]+(img.at<Vec3b>(I,J)[1]-img.at<Vec3b>(I,J+1)[1])*(y-J);
                Out.at<Vec3b>(i,j)[2]=img.at<Vec3b>(I,J)[2]+(img.at<Vec3b>(I,J)[2]-img.at<Vec3b>(I,J+1)[2])*(y-J);
            }
            else if(y==0||y==W-1){
                Out.at<Vec3b>(i,j)[0]=img.at<Vec3b>(I,J)[0]+(img.at<Vec3b>(I,J)[0]-img.at<Vec3b>(I+1,J)[0])*(x-I);
                Out.at<Vec3b>(i,j)[1]=img.at<Vec3b>(I,J)[1]+(img.at<Vec3b>(I,J)[1]-img.at<Vec3b>(I+1,J)[1])*(x-I);
                Out.at<Vec3b>(i,j)[2]=img.at<Vec3b>(I,J)[2]+(img.at<Vec3b>(I,J)[2]-img.at<Vec3b>(I+1,J)[2])*(x-I);
            }
            else{
                Out.at<Vec3b>(i,j)[0]=  img.at<Vec3b>(I,J)[0]*(I+1-x)*(J+1-y)+
                                        img.at<Vec3b>(I,J+1)[0]*(I+1-x)*(y-J)+
                                        img.at<Vec3b>(I+1,J)[0]*(x-I)*(J+1-y)+
                                        img.at<Vec3b>(I+1,J+1)[0]*(x-I)*(y-J);
                Out.at<Vec3b>(i,j)[1]=  img.at<Vec3b>(I,J)[1]*(I+1-x)*(J+1-y)+
                                        img.at<Vec3b>(I,J+1)[1]*(I+1-x)*(y-J)+
                                        img.at<Vec3b>(I+1,J)[1]*(x-I)*(J+1-y)+
                                        img.at<Vec3b>(I+1,J+1)[1]*(x-I)*(y-J);
                Out.at<Vec3b>(i,j)[2]=  img.at<Vec3b>(I,J)[2]*(I+1-x)*(J+1-y)+
                                        img.at<Vec3b>(I,J+1)[2]*(I+1-x)*(y-J)+
                                        img.at<Vec3b>(I+1,J)[2]*(x-I)*(J+1-y)+
                                        img.at<Vec3b>(I+1,J+1)[2]*(x-I)*(y-J);
            }
        }
    }
    return Out;
}
Mat Fun3(const Mat &img,float t){
    int H=img.rows,W=img.cols;
    double p,q,r,theta,op,oq; int I,J;
    Mat Out; double R=1;
    Out.create(H,W,img.type());
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            p=(double)(i-0.5*H)/(0.5*H);
            q=(double)(j-0.5*W)/(0.5*W);
            r=sqrt(p*p+q*q);
            if(r>=R) {
                op=p; oq=q;
            }
            else{
                op=p*powf(r/R,t-1);  oq=q*powf(r/R,t-1);
            }
            I=int ((op+1)*0.5*H);
            J=int ((oq+1)*0.5*W);
            Out.at<Vec3b>(i,j)[0]=img.at<Vec3b>(I,J)[0];
            Out.at<Vec3b>(i,j)[1]=img.at<Vec3b>(I,J)[1];
            Out.at<Vec3b>(i,j)[2]=img.at<Vec3b>(I,J)[2];
        }
    }
    return Out;
}
#endif //CV_E3_E3_H
