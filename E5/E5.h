//
// Created by Xu Pengbo on 2020/10/16.
//

#ifndef CV_E5_E5_H
#define CV_E5_E5_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace cv;
using namespace std;

double **Get_SpaceKernel(int size_d,double sigmaSpace) {
    double **SpaceKernel = new double *[size_d];
    for (int i = 0; i < size_d; ++i) {
        SpaceKernel[i] = new double[size_d];
    }
    double tmp = -2 * sigmaSpace * sigmaSpace;
    int kx, ky;
    kx = ky = size_d / 2;
    for (int i = 0; i < size_d; ++i) {
        for (int j = 0; j < size_d; ++j) {
            SpaceKernel[i][j] = exp(((i - kx) * (i - kx) + (j - ky) * (j - ky)) / tmp);
        }
    }
    return SpaceKernel;
}
double **Get_ColorKernel(double sigmaColor) {
    double **ColorKernel = new double *[256];
    for (int i = 0; i < 256; ++i) {
        ColorKernel[i] = new double[256];
    }
    double tmp = -2 * sigmaColor * sigmaColor;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            ColorKernel[i][j] = exp((i - j) * (i - j) / tmp);
        }

    }
    return ColorKernel;
}
Mat Bilateral_Filter(const Mat &input,  double sigmaColor,double sigmaSpace) {
    Mat output;
    input.copyTo(output);
    int N = int(6 * sigmaSpace - 1) / 2; //一半长度
    int D = N * 2 + 1;//窗口总长度
    int H = output.rows, W = output.cols;
    int x, y;
    double **WeightColor = Get_ColorKernel(sigmaColor);
    double **WeightSpace = Get_SpaceKernel(D, sigmaSpace);
    double Value, NormalSum, Weight;
    for (int c = 0; c < 3; ++c) {
        for (int i = N; i < H - N; i++) {
            for (int j = N; j < W - N; j++) {
                Value = NormalSum = 0.0;
                for (int p = 0; p < D; ++p) {
                    for (int q = 0; q < D; ++q) {
                        x = i - p + N;
                        y = j - q + N;
                        Weight = WeightSpace[p][q] * WeightColor[input.at<Vec3b>(i, j)[c]][input.at<Vec3b>(x, y)[c]];
                        NormalSum += Weight;
                        Value += input.at<Vec3b>(x, y)[c] * Weight;
                    }
                }
                output.at<Vec3b>(i, j)[c] = Value / NormalSum;
            }
        }
    }
    return output;
};

#endif //CV_E5_E5_H
