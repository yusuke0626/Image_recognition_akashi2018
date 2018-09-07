#include<iostream>
#include<vector>
#include<random>
#include<string>
#include<sstream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(void){

	Mat frame;
	Mat hsv;
	Mat binary;
	Mat src;

	VideoCapture cap(0);
    	if(!cap.isOpened()){
		cout <<"Not Opened"<< endl;
       		return -1;
    	}else{
		cout <<"Open Successful"<<endl;
	}

	cap >> frame;
	imwrite("sample.jpeg", frame);
    	
	//グレースケール入力 膨張処理 モルフォロジー処理　メディアンフィルタ
	cvtColor(frame,hsv,CV_BGR2HSV);
	inRange(hsv,Scalar(0,230,40),Scalar(40,255,255),src);
	morphologyEx(src, src, MORPH_CLOSE, Mat(), Point(-1, -1), 3);
	medianBlur(src,src,1);
    	dilate(src,src,Mat(),Point(-1,-1),4);

    	//ラべリング処理
    	Mat LabelImg;
    	Mat stats;
    	Mat centroids;
    	int nLab = connectedComponentsWithStats(src, LabelImg, stats, centroids);

    	// ラベリング結果の描画色を決定
    	vector<Vec3b> colors(nLab);
    	colors[0] = Vec3b(0, 0, 0);
    	for (int i = 1; i < nLab; ++i) {
        	colors[i] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255));//色をランダムで決定する（255で範囲指定しないといけないからビット演算）
   	}	

    	// ラベリング結果の描画
    	Mat Dst(src.size(), CV_8UC3);
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
    	for (int i = 1; i < nLab; ++i) {
        	double *param = centroids.ptr<double>(i);
        	int x = static_cast<int>(param[0]);
        	int y = static_cast<int>(param[1]);

        	circle(Dst,cv::Point(x,y), 3, cv::Scalar(0, 0, 255), -1);
		cout << i <<" "<< "x:" << x << "  y:"<< y << endl;
    	}

    	//面積値の出力
    	for (int i = 1; i < nLab; ++i) {
        	int *param = stats.ptr<int>(i);
        	cout << "area "<< i <<" = " << param[ConnectedComponentsTypes::CC_STAT_AREA] << endl;

        	//ROIの左上に番号を書き込む
        	int x = param[cv::ConnectedComponentsTypes::CC_STAT_LEFT];
        	int y = param[cv::ConnectedComponentsTypes::CC_STAT_TOP];
        	stringstream num;
        	num << i;
        	putText(Dst, num.str(), Point(x+5, y+20), FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 255, 255), 2);
    	}
	imshow("frame",frame);
    	imshow("Src", src);
    	imshow("にゃーん", Dst);
	waitKey();
    	return 0;
}
