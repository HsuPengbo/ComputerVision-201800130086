//
// Created by Xu Pengbo on 2020/10/10.
//

#ifndef CV_E4_E4_MEAN_H
#define CV_E4_E4_MEAN_H
#include "E4.h"

void MeanFilter(const Mat &input, Mat &output, int window_size){
    input.copyTo(output);
    int H=output.rows,W=output.cols,outChannels=output.channels();
    vector<vector<int> > Sum(H, vector<int>(W));
    for (int c = 0; c < outChannels; c++)
    {
        //初始化积分图为0
        for (int x = 0; x < H; x++)
            for (int y = 0; y < W; y++)
                Sum[x][y] = 0;
        //生成积分图
        for (int x = 0; x < H; x++) {
            int tmp = 0;
            for (int y = 0; y < W; y++) {
                tmp += (int) input.ptr(x, y)[c];
                if (x == 0)
                    Sum[x][y] = tmp;
                else
                    Sum[x][y] = tmp + Sum[x - 1][y];
            }
        }
        //均值滤波
        int x1,x2,y1,y2;
        for (int x = 0; x < H; x++) {
            for (int y = 0; y < W; y++) {
                x1 = x - window_size - 1;
                y1 = y - window_size - 1;
                x2 = x + window_size;
                y2 = y + window_size;
                if (x1 < 0)     x1 = x1 + window_size + 1;
                if (y1 < 0)     y1 = y1 + window_size + 1;
                if (x2 >= H)    x2 = x2 - window_size;
                if (y2 >= W)    y2 = y2 - window_size;
                output.ptr(x, y)[c] = (Sum[x1][y1] + Sum[x2][y2] - Sum[x2][y1] - Sum[x1][y2]) / pow(2 * window_size + 1, 2);
            }
        }
    }
}

#endif //CV_E4_E4_MEAN_H
