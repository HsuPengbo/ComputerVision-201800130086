#include "exp1.h"

int main(){
	Mat img = imread("B://CV//exp//images//10111.png");				//问题1.1
	if (img.empty()){
		cout << "图像不存在" << endl;
		return -1;
	}
	imshow("原图", img); 
	
	/*																// 问题1.2
	uchar *input = img.data;
	int wi = img.rows, he = img.cols,inStep = img.step,inChannels = img.channels();
	
	Mat OutImage; OutImage.create(wi, he,CV_8UC3);
	uchar* output=OutImage.data; 
	int outStep=OutImage.step; 
	int channelToGet;	cin>>channelToGet;
	getChannel(input, wi, he, inStep, inChannels, output, outStep, channelToGet);
	imshow("Out", OutImage);
	*/

	Rect R(0, 0, 300, 200);
	int channelToGet;	cin>>channelToGet;
	Mat Out = localGetChannel(img, R, channelToGet);				//问题1.3
	//Mat Out = Test_8UC3to8UC1(img, R, channelToGet);				//验证问题1.3第二个小问题
	imshow("Out", Out);
	
	
	waitKey(0); //等待键盘输入
	return 0; //程序结束
}