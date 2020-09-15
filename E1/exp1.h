#pragma once
#include <opencv2\opencv.hpp> //����OpenCV 4.1ͷ�ļ�
#include <iostream>
#include<cstdio>
using namespace std;
using namespace cv; 

void getChannel(const uchar* input,
	int width, int height, 
	int inStep,  int inChannels, 
	uchar * output,  int outStep,  int channelToGet)			//��ȡͨ������
{
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			for (int k = 0; k < 3; ++k) {
				if (k == channelToGet)
					output[i * outStep + j * inChannels + k] = input[i * inStep + j * inChannels + k];
				else output[i * outStep + j * inChannels + k] = 0;
			}
		}
	}
}
Mat localGetChannel(const Mat input,Rect R,int channelToGet)	//��ȡ�ֲ�ͨ������
{
	int x = R.x, y = R.y, w = R.width, h = R.height;
	Mat Output;Output.create(h, w, CV_8UC3);
	uchar* inM = input.data;
	int wi = input.rows, he = input.cols, inStep = input.step, inChannels = input.channels();
	uchar* OutM = Output.data;
	int outStep = Output.step;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			for (int k = 0; k < 3; ++k) {
				if (k == channelToGet)
					OutM[i * outStep + j * inChannels + k] = inM[(x+i) * inStep + (y+j) * inChannels + k];
				else OutM[i * outStep + j * inChannels + k] = 0;
			}
		}
	}
	return Output;
}
Mat Test_8UC3to8UC1(const Mat input, Rect R, int channelToGet)	//��֤��ͨ������ͨ�������������ͨ��ͼ�����ʾ
{
	int x = R.x, y = R.y, w = R.width, h = R.height;
	Mat Output; Output.create(h, w, CV_8UC1);
	uchar* inM = input.data;
	int wi = input.rows, he = input.cols, inStep = input.step, inChannels = input.channels();
	uchar* OutM = Output.data;
	int outStep = Output.step;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			OutM[i * outStep + j * 1 ] = inM[(x + i) * inStep + (y + j) * inChannels + channelToGet];
		}
	}
	return Output;
}