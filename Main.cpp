#include<iostream>
#include<vector>
#include<random>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(void){

<<<<<<< HEAD
	Mat frame = imread("cap.jpeg");
	Mat hsv;
	Mat binary;
	Mat src;
	unsigned long int pre_t;
	unsigned long int now_t;
	unsigned long int diff_t;
	bool flag = false;

	VideoCapture cap(0);
	if(!cap.isOpened()){
=======
	Mat frame;
	Mat hsv;
	Mat binary;
	Mat src;

	VideoCapture cap(0);
    	if(!cap.isOpened()){
>>>>>>> origin/master
		cout <<"Not Opened"<< endl;
		return -1;
	}else{
		cout <<"Open Successful"<<endl;
	}

<<<<<<< HEAD
	pre_t = time_t();

	while(true){
		now_t = time_t();
		diff_t = now_t - pre_t;
		if(flag = false || diff_t >= 4000){
			cap >> frame;
			imwrite("sample.jpeg", frame);

			//グレースケール入力 膨張処理 ガウシアンフィルタ（ぼかし）メディアンフィルタ
			GaussianBlur(frame, frame, cv::Size(11,3), 80, 3);
			cvtColor(frame,hsv, COLOR_BGR2GRAY);
			inRange(hsv,Scalar(0,0,200),Scalar(200,255,255),src);
			medianBlur(src,src,1);
			dilate(src,src,Mat(),Point(-1,-1),9);
			erode(src,src,Mat(),Point(-1,-1),10);
			dilate(src,src,Mat(),Point(-1,-1),5);
			Mat neg = ~src;


			//ラべリング処理
			Mat LabelImg;
			Mat stats;
			Mat centroids;
			int nLab = connectedComponentsWithStats(neg, LabelImg, stats, centroids);

			// ラベリング結果の描画色を決定
			vector<Vec3b> colors(nLab);
			colors[0] = Vec3b(0, 0, 0);
			for (int i = 1; i < nLab; ++i) {
				colors[i] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255));//色をランダムで決定する（255で範囲指定しないといけないからビット演算）
			}	

			// ラベリング結果の描画
			Mat Dst(neg.size(), CV_8UC3);
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

				circle(Dst,cv::Point(centerX[i],centerY[i]), 3, cv::Scalar(0, 0, 255), -1);
				cout << i <<" "<< "x:" << centerX[i] << "  y:"<< centerY[i] << endl;
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

			flag = 1;
			pre_t = pre_t + now_t;
			imshow("frame",frame);
			imshow("Src", src);
			imshow("にゃーん", Dst);
			waitKey();

		}
	}

	return 0;
=======
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
>>>>>>> origin/master
}
