#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void exp_2(Mat input) {
    Mat Bin;
    threshold(input, Bin, 70, 255, THRESH_BINARY);
    imshow("�Ҷ�ͼ", input);
    imshow("��ֵͼ",Bin);
    Mat output, Labels;
    distanceTransform(Bin, output, Labels, DIST_L2, 3,DIST_LABEL_CCOMP);
    normalize(output, output, 0, 1, NORM_MINMAX);
    imshow("����ת��", output);
}
void exp_1(Mat input,int AreaValue) {
    Mat BW, ColorImage, stats, centroids;
    threshold(input, BW, 150, 255, THRESH_BINARY);
    imshow("ԭͼ1", input);
    //int labels = connectedComponents(BW, ColorImage);
    int labels = connectedComponentsWithStats(BW, ColorImage, stats, centroids);
    vector<Vec3b> colors(labels);
    //colors[0] = Vec3b(0, 0, 0);
    for (int label = 0; label < labels; ++label) {
        if (stats.at<int>(label, cv::CC_STAT_AREA) < AreaValue)
            colors[label] = colors[0];
        else
            colors[label] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
    }
    Mat output(input.size(), CV_8UC3);
    for (int r = 0; r < output.rows; ++r) {
        for (int c = 0; c < output.cols; ++c) {
            int label = (int) ColorImage.at<int>(r, c);
            output.at<Vec3b>(r, c) = colors[label];
        }
    }
    imshow("��ɫͼ", output);
}
int main() {
    Mat img1=imread("D:\\Codes\\CV\\CV_works\\CV-E7\\img1.png",IMREAD_GRAYSCALE);
    //�趨��ȥ���������ֵΪ3500,ǡ�����Ͻǵ�һ�鱻���˵�,4000������.
    exp_1(img1,3500);
    Mat img2=imread("D:\\Codes\\CV\\CV_works\\CV-E7\\img3.JPG",IMREAD_GRAYSCALE);
    exp_2(img2);
    waitKey(0);
    return 0;
}
