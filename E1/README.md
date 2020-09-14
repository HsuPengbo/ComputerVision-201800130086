# 实验E1 图像基本操作
## 实验1.1：图像加载、显示
安装配置OpenCV ，并实现从文件加载图像，在
窗口中进行显示的功能；利用常见的图像文件格
式（.jpg; .png; .bmp等）进行测试
## 实验1.2：图像通道分离
以下C/C++函数原型用于从多通道图像（交叉存
贮）中读取任意通道，请完成该函数的实现并基
于OpenCV进行测试:
void getChannel(const uchar *input, int width, 
int height, int inStep, int inChannels, uchar 
*output, int outStep,  int channelToGet );
其中input, width, height, inStep, inChannels分别是输入图像的数
据、宽、高、step和通道数。Output和outStep是输出图像的数据和step，
宽高与输入图像相同、通道数为1.
channelToGet是要获取的通道索引，比如如果input是BGR格式的数据，
则channelToGet=0将获取B通道， channelToGet=1将获取G通道……
## 实验1.3 图像子区域操作
图像的子区域是指在图像内部的一块矩形
区域，在OpenCV中通常由cv::Rect表示。
请基于你在1.2实现的getChannel函数，实
现对图像子区域的通道获取和输出：
–对图像I的任意一个子区域r，调用getChannel函数获
取r的某一个通道；
–如果O是一个数据类型为CV_8UC1的图像，getChannel
是否可以直接输出到O的某一个子区域中？（即以O的
一个子区域接收输出图像）
