#include <cstdio>
#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>
#include <sstream>
#include <vector>
#include "filerw.hpp"

#define X_ORIGIN 80
#define Y_ORIGIN 0
#define X_SIZE 200
#define Y_SIZE 460
#define FRAME_X_SIZE 400
#define FRAME_Y_SIZE 920

using namespace cv;
using namespace std;

int main(void) {

    time_t pre_t;
    time_t now_t;
    time_t diff_t;
    bool flag = false;

    unsigned int a = 0;
    unsigned int b = 0;
    unsigned int c = 0;
    unsigned int d = 255;
    unsigned int e = 255;
    unsigned int f = 255;

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Not Opened" << endl;
        return -1;
    } else {
        cout << "Open Successful" << endl;
    }

    while (true) {
        Mat img;
        Mat frame;
        Mat hsv;
        cap >> img;
        cap >> frame;
        Mat rsi(img, Rect(X_ORIGIN, Y_ORIGIN, X_SIZE, Y_SIZE));
        line(rsi, Point(0, 230), Point(400, 230), Scalar(200,100,100), 5, CV_AA);
        resize(rsi, rsi, Size(FRAME_X_SIZE, FRAME_Y_SIZE));
        imshow("img", rsi);

        int key = waitKey(250);
        bool swflag = false;

        switch (key) {
            case 113:
                a = a + 5;break;
            case 97:
                a = a - 3;break;
            case 119:
                b = b + 5;break;
            case 115:
                b = b - 3;break;
            case 101:
                c = c + 5;break;
            case 100:
                c = c - 3;break;
            case 117:
                d = d - 5;break;
            case 106:
                d = d + 3;break;
            case 105:
                e = e - 5;break;
            case 107:
                e = e + 3;break;
            case 111:
                f = f - 5;break;
            case 108:
                f = f + 3;break;
            case 122:
                swflag = true;break;
        }

        if (swflag == true){
            break;
        }
        printf("(%d,%d,%d)\n", a, b, c);
        printf("(%d,%d,%d)\n", d, e, f);
        Mat dst(frame, Rect(X_ORIGIN, Y_ORIGIN, X_SIZE, Y_SIZE));;
        resize(dst, dst, Size(FRAME_X_SIZE, FRAME_Y_SIZE));
        cvtColor(dst, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(a, b, c), Scalar(d, e, f), frame);
        erode(frame, frame, Mat(), Point(-1, -1), 3);
        dilate(frame, frame, Mat(), Point(-1, -1), 5);
        imshow("binary img", frame);
        waitKey(200);
    }

    destroyAllWindows();
    cout << "*---------Main Start---------*" << endl;

    pre_t = time(NULL);

    while(true){

        Mat mainframe;
        Mat mainhsv;
        int stopkey = waitKey(1000);

        if (stopkey == 97)
            break;

        now_t = time(NULL);
        diff_t = now_t - pre_t;

        if (flag = false || diff_t >= 1) {
            cap >> mainframe;
            Mat maindst(mainframe, Rect(X_ORIGIN, Y_ORIGIN, X_SIZE, Y_SIZE));
            resize(maindst, maindst, Size(FRAME_X_SIZE, FRAME_Y_SIZE));
            cvtColor(maindst, mainhsv, COLOR_BGR2HSV);
            inRange(mainhsv, Scalar(a, b, c), Scalar(d, e, f), maindst);
            erode(maindst, maindst, Mat(), Point(-1, -1), 3);
            dilate(maindst, maindst, Mat(), Point(-1, -1), 5);
            waitKey(200);
            //imshow("img", mainhsv);

            //ラべリング
            Mat LabelImg;
            Mat stats;
            Mat centroids;
            int nLab =connectedComponentsWithStats(maindst, LabelImg, stats, centroids);

            // 描画色決定
            vector<Vec3b> colors(nLab);
            colors[0] = Vec3b(0, 0, 0);
            for (int i = 1; i < nLab; ++i) {
                colors[i] = Vec3b((rand() & 255), (rand() & 255),(rand() &  255)); //色をランダムで決定する（255で範囲指定しないといけないからビット演算）
            }
            //描画
            Mat Dst(maindst.size(), CV_8UC3);
            for (int i = 0; i < Dst.rows; ++i) {
                int *lb = LabelImg.ptr<int>(i);
                Vec3b *pix = Dst.ptr<Vec3b>(i);
                for (int j = 0; j < Dst.cols; ++j) {
                    pix[j] = colors[lb[j]];
                }
            }

            //重心計算
            int centerX[nLab];
            int centerY[nLab];
            for (int i = 1; i < nLab; ++i){
                double *param = centroids.ptr<double>(i);
                centerX[i] = static_cast<int>(param[0]);
                centerY[i] = static_cast<int>(param[1]);
                circle(Dst, Point(centerX[i], centerY[i]), 3, Scalar(0, 0, 255), -1);
            }

            int tableXpoint[nLab] = {};
            int tableYpoint[nLab] = {};
            int tdata = 0;
            //座標
            for (int i = 1; i < nLab; ++i){
                int *param = stats.ptr<int>(i);
                if(param[ConnectedComponentsTypes::CC_STAT_AREA] > 1000){
                    int x = param[ConnectedComponentsTypes::CC_STAT_LEFT];
                    int y = param[ConnectedComponentsTypes::CC_STAT_TOP];
                    int height = param[ConnectedComponentsTypes::CC_STAT_HEIGHT];
                    int width = param[ConnectedComponentsTypes::CC_STAT_WIDTH];
                    rectangle(Dst, Rect(x, y, width, height), Scalar(0, 255, 0), 2);
                    tableXpoint[tdata] = param[ConnectedComponentsTypes::CC_STAT_LEFT];
                    tableYpoint[tdata] = param[ConnectedComponentsTypes::CC_STAT_TOP];
                    stringstream num;
                    num << tdata;
                    putText(Dst, num.str(), Point(tableXpoint[tdata] + 5,tableYpoint[tdata] + 20), FONT_HERSHEY_COMPLEX,0.7, Scalar(0, 255, 255), 2);
                    cout << tdata<< " "<< "x:" <<  tableXpoint[tdata] << "  y:" << tableYpoint[tdata] << endl;
                    tdata = tdata + 1;
                }
            }
            FRW::write("tabledata.txt",tableXpoint);
            //FRW::send("tabledata.txt");
            flag = false;//true;
            //pre_t = now_t;
           // printf("%d,%d,%d,%d,%d,%d\n", a, b, c, d, e, f);
            //imshow("にゃーん", Dst);
            waitKey(1000);
            imwrite("a.jpeg",Dst);
            break;
        }
    }
    cout << "*----------Main finish-----------*" << endl;
    return 0;
}
