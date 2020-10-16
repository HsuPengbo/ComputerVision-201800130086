#include "E3.h"

int main() {

    Mat img =imread("D:\\Codes\\CV\\CV_works\\CV-E3\\pic1.JPG");
    imshow("Photo",img);
    Mat img1,img2,img3,img4;
    img1=Fun1(img);
    img2=Fun2(img,0.8,1.5);
    img3=Fun3(img,1.9);
    imshow("f变换",img1);
    imshow("双线性插值重采样",img2);
    imshow("哈哈镜",img3);
    imwrite(R"(D:\Codes\CV\CV_works\CV-E3\pic_1.JPG)",img1);
    imwrite(R"(D:\Codes\CV\CV_works\CV-E3\pic_2.JPG)",img2);
    imwrite(R"(D:\Codes\CV\CV_works\CV-E3\pic_3.JPG)",img3);
    //waitKey(0);

    VideoCapture cap;
    //cap.open("D:\\Codes\\CV\\CV_works\\CV-E3\\video.MP4");
    cap.open(0);
    double rate = cap.get(CAP_PROP_FPS);
    Size capsize=Size(cap.get(CAP_PROP_FRAME_WIDTH),cap.get(CAP_PROP_FRAME_HEIGHT));
    printf("fps=%lf",rate);
    double fps=(rate>0)?rate:25.0;
    VideoWriter outputVideo;
    outputVideo.open("D:\\Codes\\CV\\CV_works\\CV-E3\\out.mp4",
                     VideoWriter::fourcc('m','p','4','v'),
                     fps,capsize,true);
    if(!outputVideo.isOpened())
    {
        cout<< "Error : fail to open video writer\n"<<endl;
        return -1;
    }
    while (1)
    {
        Mat frame,Out;
        cap >> frame;
        if (frame.empty())
        {
            cout << "Finish" << endl; break;
        }
        Out=Fun3(frame,2.9);
        imshow("Out video",Out);
        outputVideo.write(Out);
        if (cv::waitKey(20)=='0') break;
    }
    cap.release();
    outputVideo.release();

    return 0;
}
