#include <iostream>
#include <opencv2/opencv.hpp>

#define WinName "Ä£°åÆ¥Åä"
#define TarName "method:"
using namespace cv;
using namespace std;

Mat input,input_temp;
int value=0;
const int MaxValue=5;
void Get_MatchImage(int, void *){
    if(value<0) value=0;
    Mat img,temp,img_match,result;
    input.copyTo(result);
    cvtColor(input, img, COLOR_BGR2GRAY);
    cvtColor(input_temp, temp, COLOR_BGR2GRAY);
    matchTemplate(img, temp, img_match, value);
    normalize( img_match, img_match, 0, 1, NORM_MINMAX, -1 );
    imshow("match",img_match);
    double minVal,maxVal;   Point minLoc,maxLoc;
    minMaxLoc(img_match, &minVal, &maxVal, &minLoc, &maxLoc);
    if(value<2)cout<<"min_val:"<<minVal<<endl;
    else cout<<"max_val:"<<maxVal<<endl;
    if(value<2)
        rectangle(result, minLoc, Point(minLoc.x + temp.cols, minLoc.y + temp.rows), Scalar(0, 0, 255), 4, 8, 0);
    else
        rectangle(result, maxLoc, Point(maxLoc.x + temp.cols, maxLoc.y + temp.rows), Scalar(0, 0, 255), 4, 8, 0);
    imshow(WinName, result);
}
int main() {
    input=imread("D:\\Codes\\CV\\CV_works\\CV-E9\\images\\img3.jpg");
    input_temp=imread("D:\\Codes\\CV\\CV_works\\CV-E9\\images\\img3_temp.jpg");
    imshow("Ä£°å", input_temp);
    namedWindow(WinName,WINDOW_AUTOSIZE);
    namedWindow("match",WINDOW_NORMAL);
    createTrackbar(TarName, WinName, &value, MaxValue, Get_MatchImage);
    Get_MatchImage(0, 0);
    waitKey();
    return 0;
}
