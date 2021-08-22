#include "CV_Final.h"

Point P1,P2;
bool flag=false;
bool get_temp=false;
bool get_size=false;

Mat frame,tmp,output,temp_img,temp_out;
Rect Temp;

//  描述：声明全局变量
static string window_name = "tracking";
Mat gray,gray_prev,temp_gray;

vector<Point2f> points[2];  // point0为特征点的原来位置，point1为特征点的新位置
vector<Point2f> initial;    // 初始化跟踪点的位置


int maxCount = 500; // 检测的最大特征数
double qLevel = 0.01;   // 特征检测的等级
double minDist = 5.0;  // 两特征点之间的最小距离
vector<uchar> status;   // 跟踪特征的状态，特征的流发现为1，否则为0
vector<float> err;

bool Point_in_Rect(const Rect& rect,const Point2f& point)
{
    if (rect.x<=point.x && point.x<=rect.x+rect.width && rect.y<=point.y && point.y<=rect.y+rect.height)  return true;
    else   return false;
}
bool acceptTrackedPoint(int i)
{
    return  status[i] && Point_in_Rect(Temp,points[1][i]);
}
void Initial(){
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    cvtColor(temp_img,temp_gray,COLOR_BGR2GRAY);
    getMatch(temp_gray,initial,gray);
    //goodFeaturesToTrack(gray, initial, maxCount, qLevel, minDist);
    points[0].insert(points[0].end(), initial.begin(), initial.end());
    gray.copyTo(gray_prev);
    calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
    output.copyTo(temp_out);
    int k = 0;
    for (size_t i = 0; i < points[1].size(); i++) {
        if (acceptTrackedPoint(i)) {
            initial[k] = initial[i];
            points[1][k++] = points[1][i];
        }
    }
    points[1].resize(k);
    initial.resize(k);
    for (size_t i = 0; i < points[1].size(); i++) {
        circle(temp_out, initial[i], 3, Scalar(0, 255, 0), -1);
    }
    swap(points[1], points[0]);
    swap(gray_prev, gray);
    temp_img= temp_out(Temp);
}
void DrawMatch(vector<Point2f>& obj1,vector<Point2f>& obj2) {
    Mat H = findHomography(obj1, obj2, RANSAC);//计算透视变换矩阵
    Mat H_ni;
    invert(H, H_ni, DECOMP_LU);
    vector<Point2f> obj_corner(4);
    vector<Point2f> scene_corner(4);
    obj_corner[0] = Point(Temp.x, Temp.y);
    obj_corner[1] = Point(Temp.x+Temp.width, Temp.y);
    obj_corner[2] = Point(Temp.x+Temp.width, Temp.y+Temp.height);
    obj_corner[3] = Point(Temp.x, Temp.y+Temp.height);
    perspectiveTransform(obj_corner, scene_corner, H);//透视变换
    //画出边框线
    line(output, scene_corner[0], scene_corner[1], Scalar(0, 0, 255), 2,8, 0);
    line(output, scene_corner[1], scene_corner[2], Scalar(0, 0, 255), 2,8, 0);
    line(output, scene_corner[2], scene_corner[3], Scalar(0, 0, 255), 2,8, 0);
    line(output, scene_corner[3], scene_corner[0], Scalar(0, 0, 255), 2,8, 0);
    imshow("temp",temp_img);
}
void tracking() {
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
    int k = 0;
    for (size_t i = 0; i < points[1].size(); i++) {
        if (status[i] ) {
            initial[k] = initial[i];
            points[1][k++] = points[1][i];
        }
    }
    points[1].resize(k);
    initial.resize(k);
    DrawMatch(initial,points[1]);
    // 显示特征点和运动轨迹
    for (size_t i = 0; i < points[1].size(); i++) {
        //line(output, initial[i], points[1][i], Scalar(0, 0, 255));
        circle(output, points[1][i], 3, Scalar(0, 255, 0), -1);
    }
    // 把当前跟踪结果作为下一此参考
    swap(points[1], points[0]);
    swap(gray_prev, gray);
    imshow(window_name, output);
}
void onMouse(int event,int x,int y,int flag,void* param) {
    if (event == EVENT_LBUTTONDOWN) {
        flag = true;
        P1 = Point(x, y);
        P2 = P1;
    }
    if (event == EVENT_MOUSEMOVE && flag) {
        tmp = frame.clone();
        P2 = Point(x, y);
        if (P1 != P2) {
            rectangle(tmp, P1, P2, Scalar(255, 0, 0), 2);
        }
        imshow(window_name, tmp);
    }
    if (event == EVENT_LBUTTONUP) {
        flag = false;
        Temp=Rect(P1, P2);
        temp_img=tmp(Temp);
        Initial();
        get_temp = true;
    }
}

int main() {
    VideoCapture capture("D:\\Codes\\CV\\CV_works\\CV_Final\\img\\video1.avi");
    double fps = 25.0;
    string filename = "D:\\Codes\\CV\\CV_works\\CV_Final\\img\\output.avi";
    Size siz;//= Size(2689, 1080);
    VideoWriter writer;
    auto codec = VideoWriter::fourcc('M', 'J', 'P', 'G');

    namedWindow(window_name);
    setMouseCallback(window_name, onMouse);
    // 摄像头读取文件开关
    while (true) {
        if (!flag) {
            capture >> frame;
            frame.copyTo(output);
        }
        if (get_temp) {
            tracking();
            imshow(window_name, output);
            if (!get_size) {
                siz = Size(int(output.cols), int(output.rows));
                writer.open(filename, codec, fps, siz, true);
                get_size = true;
            }
            //writer << output;
        } else {
            imshow(window_name, output);
        }
        int c = waitKey(50);
        if (c == 27) break;
        if (c == 'q') waitKey(0);
    }
    capture.release();
    return 0;
}