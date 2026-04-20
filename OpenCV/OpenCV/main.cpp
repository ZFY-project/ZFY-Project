#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
    // 1. 打开摄像头
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "摄像头打开失败！" << endl;
        return -1;
    }

    // 2. 加载人脸检测器（关键修复：添加绝对路径 + 加载校验）
    CascadeClassifier faceCascade;
    // 方案1：使用OpenCV安装目录的绝对路径（推荐，根据你的OpenCV安装位置修改）
    string cascadePath = "D:/opencv/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml";
    // 方案2：如果xml放在工程目录，直接写相对路径
    // string cascadePath = "haarcascade_frontalface_default.xml";

    if (!faceCascade.load(cascadePath)) {
        cout << "人脸分类器加载失败！请检查xml文件路径！" << endl;
        return -1;
    }

    Mat frame, gray;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // 3. 图像预处理
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);

        // 4. 检测人脸
        vector<Rect> faces;
        faceCascade.detectMultiScale(
            gray, faces, 1.1, 3, 0, Size(30, 30)
        );

        // 5. 绘制人脸框
        for (const Rect& f : faces) {
            rectangle(frame, f, Scalar(255, 0, 0), 2);
        }

        imshow("实时人脸检测", frame);
        if (waitKey(30) == 27) break; // ESC退出
    }

    cap.release();
    destroyAllWindows();
    return 0;
}