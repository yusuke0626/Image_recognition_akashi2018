<<<<<<< HEA D
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>
#include <sstream>
#include <vector>
=======
#include<iostream>
#include<cstdio>
#include<vector>
#include<random>
#include<sstream>
#include<ctime>
#include<opencv2/opencv.hpp>
>>>>>>> df76a61ba50f374d6e91d394cd682e46e5c6e1cf

#define X_ORIGIN 130
#define Y_ORIGIN 50
#define X_SIZE 120
#define Y_SIZE 400
#define FRAME_X_SIZE 135
#define FRAME_Y_SIZE 400

using namespace cv;
using namespace std;

<<<<<<< HEAD
void BubbleSort(int[], int);

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

  VideoCapture cap(1);
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
    Mat rsi(img, Rect(130, 50, 120, 400)); // 120,190,500,200
    resize(rsi, rsi, Size(135, 400));
    imshow("img", rsi);

    int key = waitKey(250);

    if (key == 113) { // q
      a = a + 5;
    } else if (key == 97) { // a
      a = a - 3;
    } else if (key == 119) { // w
      b = b + 5;
    } else if (key == 115) { // s
      b = b - 3;
    } else if (key == 101) { // e
      c = c + 5;
    } else if (key == 100) { // d
      c = c - 3;
    } else if (key == 117) { // u
      d = d - 5;
    } else if (key == 106) { // j
      d = d + 3;
    } else if (key == 105) { // i
      e = e - 5;
    } else if (key == 107) { // k
      e = e + 3;
    } else if (key == 111) { // o
      f = f - 5;
    } else if (key == 108) { // l
      f = f + 3;
    } else if (key == 122) {
      break;
    }

    printf("(%d,%d,%d)\n", a, b, c);
    printf("(%d,%d,%d)\n", d, e, f);
    Mat dst(frame, Rect(130, 50, 120, 400));
    resize(dst, dst, Size(135, 400));
    cvtColor(dst, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(a, b, c), Scalar(d, e, f), frame);
    erode(frame, frame, Mat(), Point(-1, -1), 5);
    dilate(frame, frame, Mat(), Point(-1, -1), 8);
    imshow("binary img", frame);
    waitKey(200);
  }

  // int ready = waitKey(1)
  destroyAllWindows();
  // if(ready = 10){
  cout << "Main Start" << endl;
  //}

  pre_t = time(NULL);

  while (true) {

    Mat mainframe;
    Mat mainhsv;
    // Mat maindst;
    int stopkey = waitKey(200);

    if (stopkey == 97)
      break;

    now_t = time(NULL);
    diff_t = now_t - pre_t;

    if (flag = false || diff_t >= 4) {
      cap >> mainframe;
      Mat maindst(mainframe, Rect(130, 50, 120, 400));
      resize(maindst, maindst, Size(135, 400));
      cvtColor(maindst, mainhsv, COLOR_BGR2HSV);
      inRange(mainhsv, Scalar(a, b, c), Scalar(d, e, f), maindst);
      erode(maindst, maindst, Mat(), Point(-1, -1), 5);
      dilate(maindst, maindst, Mat(), Point(-1, -1), 8);
      waitKey(200);
      imshow("img", mainhsv);
      // imshow("binary img",maindst);

      //ラべリング処理
      Mat LabelImg;
      Mat stats;
      Mat centroids;
      int nLab =
          connectedComponentsWithStats(maindst, LabelImg, stats, centroids);

      // ラベリング結果の描画色を決定
      vector<Vec3b> colors(nLab);
      colors[0] = Vec3b(0, 0, 0);
      for (int i = 1; i < nLab; ++i) {
        colors[i] = Vec3b(
            (rand() & 255), (rand() & 255),
            (rand() &
             255)); //色をランダムで決定する（255で範囲指定しないといけないからビット演算）
      }

      // ラベリング結果の描画
      Mat Dst(maindst.size(), CV_8UC3);
      for (int i = 0; i < Dst.rows; ++i) {
        int *lb = LabelImg.ptr<int>(i);
        Vec3b *pix = Dst.ptr<Vec3b>(i);
        for (int j = 0; j < Dst.cols; ++j) {
          pix[j] = colors[lb[j]];
=======
void BubbleSort(int[],int);

int main(void){

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


    VideoCapture cap("video.webm");
    if(!cap.isOpened()){

        cout <<"Not Opened"<< endl;
        return -1;
    }else{
        cout <<"Open Successful"<<endl;
    }

    while (true) {
        Mat img;
        Mat frame;
        Mat hsv;
        cap >> img;
        cap >> frame;
        Mat rsi(img, Rect(X_ORIGIN, Y_ORIGIN, X_SIZE, Y_SIZE));;
        resize(rsi,rsi, Size(FRAME_X_SIZE, FRAME_Y_SIZE));
        imshow("img",rsi);

        int key = waitKey(250);
        bool swflag = false;

        switch (key){
            case 113:
                a = a + 5; break;
            case 97:
                a = a - 3; break;
            case 119:
                b = b + 5; break;
            case 115:
                b = b - 3; break;
            case 101:
                c = c + 5; break;
            case 100:
                c = c - 3; break;
            case 117:
                d = d - 5; break;
            case 106:
                d = d + 3; break;
            case 105:
                e = e - 5; break;
            case 107:
                e = e + 3; break;
            case 111:
                f = f - 5; break;
            case 108:
                f = f + 3; break;
            case 122:
                swflag = true; break;
        }


        if(swflag == true){
            break;
        }

        printf("(%d,%d,%d)\n",a,b,c);
        printf("(%d,%d,%d)\n",d,e,f);
        Mat dst(frame, Rect(X_ORIGIN, Y_ORIGIN, X_SIZE, Y_SIZE));;
        resize(dst, dst, Size(FRAME_X_SIZE, FRAME_Y_SIZE));
        cvtColor(dst,hsv, COLOR_BGR2HSV);
        inRange(hsv,Scalar(a,b,c),Scalar(d,e,f),frame);
        erode(frame,frame,Mat(),Point(-1,-1),3);
        dilate(frame,frame,Mat(),Point(-1,-1),5);
        imshow("binary img",frame);
        waitKey(200);
    }

    //int ready = waitKey(1)
    destroyAllWindows();
    //if(ready = 10){
        cout << "*---------Main Start---------*" << endl;
    //}

    pre_t = time(NULL);

    while(true){

        Mat mainframe;
        Mat mainhsv;
        //Mat maindst;
        int stopkey = waitKey(200);

        if(stopkey == 97)
            break;

        now_t = time(NULL);
        diff_t = now_t - pre_t;

        if(flag = false || diff_t >= 4){
            cap >> mainframe;
            Mat maindst(mainframe, Rect(X_ORIGIN, Y_ORIGIN, X_SIZE, Y_SIZE));;
            resize(maindst, maindst, Size(FRAME_X_SIZE, FRAME_Y_SIZE));
            cvtColor(maindst,mainhsv, COLOR_BGR2HSV);
            inRange(mainhsv,Scalar(a,b,c),Scalar(d,e,f),maindst);
            erode(maindst,maindst,Mat(),Point(-1,-1),3);
            dilate(maindst,maindst,Mat(),Point(-1,-1),5);
            waitKey(200);
            imshow("img",mainhsv);
            //imshow("binary img",maindst);


            //ラべリング処理
            Mat LabelImg;
            Mat stats;
            Mat centroids;
            int nLab = connectedComponentsWithStats(maindst, LabelImg, stats, centroids);

            // ラベリング結果の描画色を決定
            vector<Vec3b> colors(nLab);
            colors[0] = Vec3b(0, 0, 0);
            for (int i = 1; i < nLab; ++i) {
                colors[i] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255));//色をランダムで決定する（255で範囲指定しないといけないからビット演算）
            }

            // ラベリング結果の描画
            Mat Dst(maindst.size(), CV_8UC3);
            for (int i = 0; i < Dst.rows; ++i) {
                int *lb = LabelImg.ptr<int>(i);
                Vec3b *pix = Dst.ptr<Vec3b>(i);
                for (int j = 0; j < Dst.cols; ++j) {
                    pix[j] = colors[lb[j]];
                }
            }

            //ROIの設定
            for (int i = 1; i < nLab; ++i) {
                int *param = stats.ptr<int>(i);

                int x = param[ConnectedComponentsTypes::CC_STAT_LEFT];
                int y = param[ConnectedComponentsTypes::CC_STAT_TOP];
                int height = param[ConnectedComponentsTypes::CC_STAT_HEIGHT];
                int width = param[ConnectedComponentsTypes::CC_STAT_WIDTH];

                rectangle(Dst, Rect(x, y, width, height), Scalar(0, 255, 0), 2);
            }

            //重心の出力
            int centerX[nLab];
            int centerY[nLab];
            for (int i = 1; i < nLab; ++i) {
                double *param = centroids.ptr<double>(i);
                centerX[i] = static_cast<int>(param[0]);
                centerY[i] = static_cast<int>(param[1]);

                circle(Dst,Point(centerX[i],centerY[i]), 3, Scalar(0, 0, 255),-1);
            }

            for(int count = 1;count < nLab;++count)
                cout<< count <<" "<< "x:" << centerY[count] << "  y:"<< centerX[count] << endl;

            //面積値の出力
            for (int i = 1; i < nLab; ++i) {
                int *param = stats.ptr<int>(i);
                cout << "area "<< i <<" = " << param[ConnectedComponentsTypes::CC_STAT_AREA] << endl;

                //ROIの左上に番号を書き込む
                int x = param[ConnectedComponentsTypes::CC_STAT_LEFT];
                int y = param[ConnectedComponentsTypes::CC_STAT_TOP];
                stringstream num;
                num << i;
                putText(Dst, num.str(), Point(x+5, y+20), FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 255, 255), 2);
            }

            flag = true;
            pre_t = now_t;
            printf("%d,%d,%d,%d,%d,%d\n",a,b,c,d,e,f);
            //imshow("frame",mainframe);
            //imshow("Src", src);
            imshow("にゃーん", Dst);
            waitKey(200);


>>>>>>> df76a61ba50f374d6e91d394cd682e46e5c6e1cf
        }
      }

      // ROIの設定
      for (int i = 1; i < nLab; ++i) {
        int *param = stats.ptr<int>(i);

        int x = param[ConnectedComponentsTypes::CC_STAT_LEFT];
        int y = param[ConnectedComponentsTypes::CC_STAT_TOP];
        int height = param[ConnectedComponentsTypes::CC_STAT_HEIGHT];
        int width = param[ConnectedComponentsTypes::CC_STAT_WIDTH];

        rectangle(Dst, Rect(x, y, width, height), Scalar(0, 255, 0), 2);
      }

      //重心の出力
      int centerX[nLab];
      int centerY[nLab];
      for (int i = 1; i < nLab; ++i) {
        double *param = centroids.ptr<double>(i);
        centerX[i] = static_cast<int>(param[0]);
        centerY[i] = static_cast<int>(param[1]);

        circle(Dst, cv::Point(centerX[i], centerY[i]), 3, cv::Scalar(0, 0, 255),
               -1);
      }
      // BubbleSort(centerX, nLab);

      for (int count = 1; count < nLab; ++count)
        cout << count << " "
             << "x:" << centerY[count] << "  y:" << centerX[count] << endl;
      cout << "*----------------------*" << endl;

      //面積値の出力
      for (int i = 1; i < nLab; ++i) {
        int *param = stats.ptr<int>(i);

        /*cout << "area " << i << " = "
             << param[ConnectedComponentsTypes::CC_STAT_AREA] << endl;*/

        // ROIの左上に番号を書き込む
        int x = param[cv::ConnectedComponentsTypes::CC_STAT_LEFT];
        int y = param[cv::ConnectedComponentsTypes::CC_STAT_TOP];
        stringstream num;
        num << i;
        putText(Dst, num.str(), Point(x + 5, y + 20), FONT_HERSHEY_COMPLEX, 0.7,
                Scalar(0, 255, 255), 2);
      }

      flag = true;
      pre_t = now_t;
      // printf("%d,%d,%d,%d,%d,%d\n", a, b, c, d, e, f);
      // imshow("frame",mainframe);
      // imshow("Src", src);
      imshow("にゃーん", Dst);
      waitKey(200);
    }
<<<<<<< HEAD
  }
  cout << "Main finish" << endl;
  return 0;
=======
    cout << "*----------Main finish-----------*" << endl;
    return 0;

>>>>>>> df76a61ba50f374d6e91d394cd682e46e5c6e1cf
}

void BubbleSort(int array[], int n) {
  int i, j, temp;

<<<<<<< HEAD


=======
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1; j++) {
      if (array[j + 1] < array[j]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}
>>>>>>> e287f4430ce3ecd39aac580252e1f27fa5c9a590
