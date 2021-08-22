//
// Created by 17844 on 2020/12/18.
//

#ifndef CV_FINAL_CV_FINAL_H
#define CV_FINAL_CV_FINAL_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;
void getMatch(const Mat& temp, vector<Point2f>&initial, const Mat& src) {
    int minHessian = 400;
    Ptr<SURF> detector = SURF::create(minHessian, 4, 3, true, true);
    Mat src_vector, temp_vector;
    vector<KeyPoint> K1, K2;
    detector->detect(temp, K1);
    detector->detect(src, K2);
    detector->detectAndCompute(temp, Mat(), K1, temp_vector);//输入图像，输入掩码，输入特征点，输出Mat，存放所有特征点的描述向量
    detector->detectAndCompute(src, Mat(), K2, src_vector);
    FlannBasedMatcher matcher;
    vector<DMatch> matches;
    if (src_vector.type() != CV_32F || temp_vector.type() != CV_32F) {
        src_vector.convertTo(src_vector, CV_32F);
        temp_vector.convertTo(temp_vector, CV_32F);
    }
    matcher.match(temp_vector,src_vector,matches);

    double minDistance = 1000;//反向逼近
    double maxDistance = 5;
    for (int i = 0; i < temp_vector.rows; i++) {
        double distance = matches[i].distance;
        if (distance > maxDistance) {
            maxDistance = distance;
        }
        if (distance < minDistance) {
            minDistance = distance;
        }
    }
    vector<DMatch> good_matches;
    sort(matches.begin(), matches.end());
    int ptsPairs = std::min(50, (int) (matches.size() * 0.1));//匹配点数量不大于50
    for (int i = 0; i < ptsPairs; i++) {
        good_matches.push_back(matches[i]);
    }
    cout<< "\nsize="<<good_matches.size()<<endl;
    for (size_t t = 0; t < good_matches.size(); t++) {
        //obj.push_back(K1[good_matches[t].queryIdx].pt);//返回对象在模板图特征点坐标
        initial.push_back(K2[good_matches[t].trainIdx].pt);//返回对象在背景查找图的坐标
    }
    cout<< "\nsize="<<good_matches.size()<<endl;
}
/*
 *
    Mat H = findHomography(obj, initial, RANSAC);//计算透视变换矩阵
    Mat H_ni;
    invert(H , H_ni,DECOMP_LU );
    vector<Point2f> obj_corner(4);
    vector<Point2f> scene_corner(4);
    obj_corner[0] = Point(0, 0);
    obj_corner[1] = Point(img1.cols, 0);
    obj_corner[2] = Point(img1.cols, img1.rows);
    obj_corner[3] = Point(0, img1.rows);

    perspectiveTransform(obj_corner, scene_corner, H);//透视变换

    //画出边框线
    line(output, scene_corner[0] + Point2f(img1.cols, 0), scene_corner[1] + Point2f(img1.cols, 0), Scalar(0, 0, 255), 2,
         8, 0);
    line(output, scene_corner[1] + Point2f(img1.cols, 0), scene_corner[2] + Point2f(img1.cols, 0), Scalar(0, 0, 255), 2,
         8, 0);
    line(output, scene_corner[2] + Point2f(img1.cols, 0), scene_corner[3] + Point2f(img1.cols, 0), Scalar(0, 0, 255), 2,
         8, 0);
    line(output, scene_corner[3] + Point2f(img1.cols, 0), scene_corner[0] + Point2f(img1.cols, 0), Scalar(0, 0, 255), 2,
         8, 0);
    line(img2, scene_corner[0], scene_corner[1], Scalar(0, 0, 255), 2, 8, 0);
    line(img2, scene_corner[1], scene_corner[2], Scalar(0, 0, 255), 2, 8, 0);
    line(img2, scene_corner[2], scene_corner[3], Scalar(0, 0, 255), 2, 8, 0);
    line(img2, scene_corner[3], scene_corner[0], Scalar(0, 0, 255), 2, 8, 0);
    imshow("Video", output);
 *
 */
#endif //CV_FINAL_CV_FINAL_H
