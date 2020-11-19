//
// Created by Xu Pengbo on 2020/11/6.
//
#ifndef CV_E8_E8_H
#define CV_E8_E8_H
#include <iostream>
#include <cstring>
#include <string>
#include <opencv2/opencv.hpp>
#define maxn 600
using namespace std;
using namespace cv;
//int H[maxn][maxn][600];
int Houg[maxn*maxn*maxn];
void hough(Mat img,int threshold1,int threshold2,int flag,int min_redius,int max_redius) {
    imshow("原始图", img);
    Mat BW, edges;
    cvtColor(img, BW, COLOR_BGR2GRAY);
    GaussianBlur(BW, BW, Size(3, 3), 3, 3);
    Canny(BW, edges, threshold1, threshold2);
    imshow("轮廓图", edges);
    memset(Houg,0,sizeof(Houg));
    int deta_r = 5;
    int theta, a, b, cura, curb;
    for (int i = 0; i < edges.rows; i++) {
        for (int j = 0; j < edges.cols; j++) {
            if (edges.at<uchar>(i, j) == 0) continue;
            for (int r = min_redius; r < max_redius; r += deta_r) {
                cura = curb = -1;
                for (theta = 0; theta < 360; theta += 3) {
                    b = (int) i - r * cos(theta * CV_PI / 180);
                    a = (int) j - r * sin(theta * CV_PI / 180);
                    if (a > 0 && a < img.cols
                        && b > 0 && b < img.rows
                        && cura != a && curb != b
                            ) {
                        Houg[a*maxn*maxn+b*maxn+r]++;
                        cura = a;
                        curb = b;
                    }
                }
            }
        }
    }
    for (int i = 0; i < maxn; i+=5) {
        for (int j = 0; j < maxn; j+=5) {
            for (int r = min_redius; r < max_redius; r += deta_r) {
                if(Houg[i*maxn*maxn+j*maxn+r]>flag){
                    circle(img, Point(i, j), r, Scalar(0, 0, 0), 1);
                }
            }
        }
    }
    imshow("效果图", img);
}


#endif //CV_E8_E8_H

