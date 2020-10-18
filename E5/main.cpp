#include "E5.h"
Mat input;
void Contrast(Mat input){
    Mat output1,output2;
    double start,end;
    string winName1="ÎÒµÄË«±ßÂË²¨",winName2="opencvµÄË«±ßÂË²¨",winName0="Ô­Í¼";
    namedWindow(winName0, WINDOW_NORMAL);
    imshow(winName0,input);
    start=clock();
    output1 = Bilateral_Filter(input, 30, 5);
    end=clock();
    cout<<"my time:"<<double((end-start)/1000)<<"s"<<endl;

    namedWindow(winName1, WINDOW_NORMAL);
    imshow(winName1,output1);
    start=clock();
    bilateralFilter(input,output2,29,30,5,BORDER_DEFAULT);
    end=clock();
    cout<<"opencv's time:"<<double((end-start)/1000)<<"s"<<endl;
    namedWindow(winName2, WINDOW_NORMAL);
    imshow(winName2,output2);
}
int main() {
    input = imread("D:\\Codes\\CV\\CV_works\\CV-E5\\img2.JPG");
    Contrast(input);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
