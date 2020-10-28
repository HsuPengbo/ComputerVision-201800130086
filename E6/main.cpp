#include<iostream>
#include<opencv2/opencv.hpp>
#include<ctype.h>
using namespace std;
using namespace cv;

Mat CurImg, CopyImg, RectImg;
Point PointX, PointY;
bool ButtonFlag=false;
bool GetTarget=false;
int h_bins = 50; int s_bins = 60;
int histSize[] = { h_bins, s_bins };
float h_ranges[] = { 0, 180 };
float s_ranges[] = { 0, 256 };
const float* ranges[] = { h_ranges, s_ranges };
int channels[] = { 0, 1 };
Mat RectHSV,RectHist;
void GetTrace();
void onMouse(int event, int x, int y, int flags, void *)            //鼠标操作截取目标图像
{
    if (event == EVENT_LBUTTONDOWN)
    {
        ButtonFlag=true;
        PointX = Point(x, y);
        PointY = PointX;
    }
    if (event == EVENT_MOUSEMOVE && ButtonFlag)//鼠标移动取点Y
    {
        CopyImg = CurImg.clone();
        PointY = Point(x, y);
        if (PointX != PointY)
        {
            rectangle(CopyImg, PointX, PointY, Scalar(0, 0, 255), 2);
        }
        imshow("Target", CopyImg);
    }
    if (event == EVENT_LBUTTONUP)//左键点击结束计算目标区域直方图和归一化
    {
        ButtonFlag=false;
        RectImg = CopyImg(Rect(PointX, PointY));
        cvtColor(RectImg, RectHSV, COLOR_BGR2HSV);
        calcHist(&RectHSV, 1, channels, Mat(), RectHist, 2, histSize, ranges, true, false);
        normalize(RectHist, RectHist, 0, 1, NORM_MINMAX);
        GetTarget=true;
    }
}
int main(int argc,char* argv[]) {
    VideoCapture VideoIn("D:\\Codes\\CV\\CV_works\\E6\\video.MP4");
    int fps = VideoIn.get(CAP_PROP_FPS);
    int W = VideoIn.get(CAP_PROP_FRAME_WIDTH);
    int H = VideoIn.get(CAP_PROP_FRAME_HEIGHT);
    int DisTime = 1000/ fps;
    if(!VideoIn.isOpened())
    {
        cout<< "Error : fail to open VideoIn\n"<<endl;
        return -1;
    }
    GetTarget=false;
                                                                //取出目标图像
    namedWindow("Target");
    setMouseCallback("Target", onMouse);
    while(true){
        if(!ButtonFlag){
            VideoIn >> CurImg;
        }
        imshow("Target", CurImg);
        if (CurImg.empty() || waitKey(DisTime) == 27|| GetTarget) break;
    }
    VideoIn.release();

    GetTrace();
    return 0;
}
void GetTrace()                                                     //目标跟踪
{
    VideoCapture VideoIn("D:\\Codes\\CV\\CV_works\\E6\\video.MP4");
    int fps = VideoIn.get(CAP_PROP_FPS);
    int W = VideoIn.get(CAP_PROP_FRAME_WIDTH);
    int H = VideoIn.get(CAP_PROP_FRAME_HEIGHT);
    int DisTime = fps;
    VideoWriter VideoOut;
    VideoOut.open("D:\\Codes\\CV\\CV_works\\E6\\out.MP4",
                  VideoWriter::fourcc('m', 'p', '4', 'v'),
                  fps, Size(W, H));

    Mat BestRect, CurRect, CurHSV, CurHist;
    Point A(0, 0), B(0, 0);
    double BestValue, curValue;
    int h = RectImg.rows, w = RectImg.cols;
    int x1 = PointX.x - w, y1 = PointX.y - h;
    int x2 = PointX.x + w, y2 = PointX.y + h;
    namedWindow("Video");
    while (true) {                                                                                                                  //目标跟踪
        VideoIn >> CurImg;
        if (CurImg.empty() || waitKey(DisTime) == 27) break;
        int rateX = 10, rateY = 10;
        x1 = (x1 > 0) ? x1 : 0;
        y1 = (y1 > 0) ? y1 : 0;
        BestValue = 1.0;
        Point Start, End;
        for (int y = y1; y < y2; y += rateY) {
            for (Start.x = x1, Start.y = y; Start.x < x2; Start.x += rateX) {
                End.x = (Start.x + w) < W ? Start.x + w : W - 1;
                End.y = (Start.y + h) < H ? Start.y + h : H - 1;
                if (Start.x < End.x && Start.y < End.y) {
                    CurRect = CurImg(Rect(Start, End));
                    cvtColor(CurRect, CurHSV, COLOR_BGR2HSV);
                    calcHist(&CurHSV, 1, channels, Mat(), CurHist, 2, histSize, ranges, true, false);   //直方图
                    normalize(CurHist, CurHist, 0, 1, NORM_MINMAX);                                                      //归一化
                    curValue = compareHist(CurHist, RectHist, HISTCMP_BHATTACHARYYA);                                                 //计算巴氏距离
                    if (curValue < BestValue) {
                        BestValue = curValue;
                        BestRect = CurRect;
                        A = Start;
                        B = End;
                    }
                }
            }
        }
        x1 = A.x - w;
        y1 = A.y - h;
        x2 = A.x + w;
        y2 = A.y + h;
        rectangle(CurImg, A, B, Scalar(0, 0, 255), 2);
        if(BestValue<0.15){                                                                                         //如果相似度较高就更新目标图像
            RectImg=BestRect;
            cvtColor(RectImg, RectHSV, COLOR_BGR2HSV);
            calcHist(&RectHSV, 1, channels, Mat(), RectHist, 2, histSize, ranges, true, false);
            normalize(RectHist, RectHist, 0, 1, NORM_MINMAX);
        }
        imshow("Video", CurImg);
        VideoOut << CurImg;
    }
    VideoIn.release();
    VideoOut.release();
}