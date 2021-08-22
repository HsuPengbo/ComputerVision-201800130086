#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat Harris_Corner(const Mat& input,double alpha) {
    Mat gray;
    cvtColor(input, gray, COLOR_RGB2GRAY);
    gray.convertTo(gray, CV_64F);
    Mat Ix, Iy;
    Sobel(gray, Ix, -1, 1, 0);
    Sobel(gray, Iy, -1, 0, 1);
    Mat Ix2, Ixy, Iy2;
    Ix2 = Ix.mul(Ix);
    Ixy = Ix.mul(Iy);
    Iy2 = Iy.mul(Iy);
    GaussianBlur(Ix2, Ix2, cv::Size(7, 7), 1, 1);
    GaussianBlur(Ixy, Ixy, cv::Size(7, 7), 1, 1);
    GaussianBlur(Iy2, Iy2, cv::Size(7, 7), 1, 1);
    Mat Corner(gray.size(), gray.type());
    for (int i = 0; i < Corner.rows; ++i) {
        for (int j = 0; j < Corner.cols; ++j) {
            double det_M = Ix2.at<double>(i, j) * Iy2.at<double>(i, j)- Ixy.at<double>(i,j) * Ixy.at<double>(i,j);;
            double trace_M = Ix2.at<double>(i, j) + Iy2.at<double>(i, j);
            Corner.at<double>(i, j) = det_M - alpha * trace_M * trace_M;
        }
    }
    double MaxValue;
    minMaxLoc(Corner, NULL, &MaxValue, NULL, NULL);

    Mat dilated, localMax;
    dilate(Corner, dilated, Mat());
    compare(Corner, dilated, localMax, CMP_EQ);
    Mat CornerMAP;
    double Val = 0.01;
    double threshold = Val * MaxValue;
    cout<<"max:"<<MaxValue<<endl;
    CornerMAP = Corner > threshold;
    bitwise_and(CornerMAP, localMax, CornerMAP);
    return CornerMAP;
}
Mat DrawCircle(Mat& input,const Mat& Bin) {
    Mat output = input.clone();
    Mat_<uchar>::const_iterator it = Bin.begin<uchar>();
    Mat_<uchar>::const_iterator it_end = Bin.end<uchar>();
    for (int i = 0; it != it_end; it++, i++) {
        if (*it)
            circle(output, Point(i % output.cols, i / output.cols), 3, Scalar(200, 0, 0), 1);
    }
    return output;
}
void OpencvHarris(Mat& input){
    Mat gray,output;
    output=input.clone();
    cvtColor(input, gray, COLOR_RGB2GRAY);
    Mat Corner;
    cornerHarris(gray, Corner, 3, 3, 0.01);
    int thresh = 0.001;
    threshold(Corner, Corner, 0.001, 255, THRESH_BINARY);
    for (int i = 0; i < Corner.rows; ++i) {
        for (int j = 0; j < Corner.cols; ++j) {
            if(Corner.at<int>(i,j)>thresh)
                circle(output, Point(j, i), 3, Scalar(200, 0, 0), 1);
        }
    }

    imshow("opencv",output);
}
int main() {
    string str1="D:\\Codes\\CV\\CV_works\\CV-E10\\images\\";
    string str2="03";
    string str3=".png";
    Mat img=imread(str1+str2+str3);
    Mat cormap=Harris_Corner(img,0.04);
    Mat out=DrawCircle(img,cormap);
    imshow("harris",out);
    OpencvHarris(img);
    waitKey(0);
    return 0;
}
