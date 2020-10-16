//
// Created by Xu Peng bo on 2020/10/9.
//

#ifndef CV_E4_E4_GAUSS_H
#define CV_E4_E4_GAUSS_H
#include "E4.h"
double Kernel1D[1000];
int D=0;
int K=0;
void Get_Kernel1D(double sigma){
    int d=int(6*sigma-1); D=d/2*2+1;K=D/2; double sum=0;
    for(int i=0;i<D;++i){
        Kernel1D[i] = exp((-1*(i-K)*(i-K))/(2*sigma*sigma));
        sum += Kernel1D[i];
    }
    for(int i=0;i<D;++i)    Kernel1D[i]/=sum;
}
void Gaussian(const Mat &input, Mat &output, double sigma){
    input.copyTo(output);Mat tmp;input.copyTo(tmp);
    int H=output.rows,W=output.cols,outChannels=output.channels();
    double sum; Get_Kernel1D(sigma);
    for(int c=0;c<outChannels;++c) {
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                sum = 0;
                for (int p = 0; p < D; ++p) {
                    int q = p+y-K;
                    if (q < 0) q = -q;
                    if (q >= W) q = 2 * W - 1 - q;
                    sum += (double) input.ptr(x, q)[c] * Kernel1D[p];
                }
                tmp.ptr(x, y)[c] = (int) sum;
            }
        }
    }
    for(int c=0;c<outChannels;++c) {
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                sum = 0;
                for (int p = 0; p < D; ++p) {
                    int q = p + x - K;
                    if (q < 0) q = -q;
                    if (q >= H) q = 2 * H - 1 - q;
                    sum += (double) tmp.ptr(q, y)[c] * Kernel1D[p];
                }
                output.ptr(x, y)[c] = (int) sum;
            }
        }
    }
}


#endif //CV_E4_E4_GAUSS_H
