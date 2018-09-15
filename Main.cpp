#include<iostream>
#include<cstdio>
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
        Mat rsi(img, Rect(100, 150, 500, 200));;
        resize(rsi,rsi, Size(1000, 400));
        imshow("img",rsi);

        int key = waitKey(1);

        if(key==113){//q
            a=a+5;
        }else if(key==97){//a
            a=a-3;
        }else if(key==119){//w
            b=b+5;
        }else if(key==115){//s
            b=b-3;
        }else if(key==101){//e
            c=c+5;
        }else if(key==100){//d
            c=c-3;
        }else if(key==117){//u
            d=d-5;
        }else if(key==106){//j
            d=d+3;
        }else if(key==105){//i
            e=e-5;
        }else if(key==107){//k
            e=e+3;
        }else if(key==111){//o
            f=f-5;
        }else if(key==108){//l
            f=f+3;
        }else if(key==10){
            break;
        }

        printf("(%d,%d,%d)\n",a,b,c);
        printf("(%d,%d,%d)\n",d,e,f);
        erode(frame,frame,Mat(),Point(-1,-1),1);
        dilate(frame,frame,Mat(),Point(-1,-1),3);
        Mat dst(frame, Rect(100, 150, 500, 200));;
        resize(dst, dst, Size(1000, 400));
        cvtColor(dst,hsv, COLOR_BGR2HSV);
        inRange(hsv,Scalar(a,b,c),Scalar(d,e,f),dst);
        imshow("binary img",dst);
        waitKey(1);
    }

    int ready = waitKey(1);

    if(ready = 10){
        cout << "Main Start" << endl;
    }

    pre_t = time(NULL);

    while(true){

        Mat mainframe;
        Mat mainhsv;
        Mat maindst;

        now_t = time(NULL);
        diff_t = now_t - pre_t;

        if(flag = false || diff_t >= 4){
            cap >> mainframe;
            erode(mainframe,mainframe,Mat(),Point(-1,-1),1);
            dilate(mainframe,mainframe,Mat(),Point(-1,-1),3);
            Mat dst(mainframe, Rect(100, 150, 500, 200));;
            resize(maindst, maindst, Size(1000, 400));
            cvtColor(maindst,mainhsv, COLOR_BGR2GRAY);
            inRange(mainhsv,Scalar(a,b,c),Scalar(d,e,f),maindst);
            imshow("binary img",maindst);

            //imwrite("sample.jpeg", frame);

            //グレースケール入力 膨張処理 ガウシアンフィルタ（ぼかし）メディアンフィルタ
            /*GaussianBlur(frame, frame, cv::Size(11,3), 80, 3);
              cvtColor(frame,hsv, COLOR_BGR2GRAY);
              inRange(hsv,Scalar(0,0,0),Scalar(10,255,255),src);
              medianBlur(src,src,1);
              dilate(src,src,Mat(),Point(-1,-1),9);
              erode(src,src,Mat(),Point(-1,-1),10);
              dilate(src,src,Mat(),Point(-1,-1),5);
              Mat neg = ~src;*/


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

            flag = true;
            pre_t = now_t;
            //imshow("frame",frame);
            //imshow("Src", src);
            //imshow("にゃーん", Dst);
            //waitKey();

        }

    }

    return 0;

}
=======
	Mat frame;
	Mat hsv;
	Mat binary;
	Mat src;
	time_t pre_t;
	time_t now_t;
	time_t diff_t;
	bool flag = false;

	VideoCapture cap(0);
    	if(!cap.isOpened()){

		cout <<"Not Opened"<< endl;
		return -1;
	}else{
		cout <<"Open Successful"<<endl;
	}


	pre_t = time(NULL);

	while(true){
		
		now_t = time(NULL);
		diff_t = now_t - pre_t;

		if(flag = false || diff_t >= 1){
			cap >> frame;
			imwrite("sample.jpeg", frame);

			//グレースケール入力 膨張処理 メディアンフィルタ
			//GaussianBlur(frame, frame, cv::Size(11,3), 80, 3);//ガウシアンフィルタ（ぼかし）
			cvtColor(frame,hsv, COLOR_BGR2HSV);
			inRange(hsv,Scalar(160,50,50),Scalar(180,255,255),src);
			medianBlur(src,src,1);//メディアンフィルタ
			dilate(src,src,Mat(),Point(-1,-1),3);
			erode(src,src,Mat(),Point(-1,-1),10);
			dilate(src,src,Mat(),Point(-1,-1),5);
			Mat neg = ~src;
			neg = src;


			//ラべリング処理
			Mat LabelImg;
			Mat stats;
			Mat centroids;
			int nLab = connectedComponentsWithStats(neg, LabelImg, stats, centroids);//ラベリング画像、重心

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

			//輪郭線の設定
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
				if(centerY[i]>= 50){
					cout<< "no" <<endl;
				}else{
					cout <<"stand"<<endl;
				}

			}
			
			vector<vector<Point> > contours;
			findContours(src, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
			double contour_len=0;
			for(int i = 0; i < contours.size(); ++i) {
				contour_len += arcLength(contours.at(i),0);
			}
			cout<<" Line Length = "<<contour_len/2<<endl;	if(centerY >= 390){
				cout<< "stand" <<endl;
			}else{
				cout <<"no"<<endl;
			}

				
			flag = true;
			pre_t = now_t;
			//imshow("frame",frame);
			//imshow("Src", src);
			//imshow("にゃーん", Dst);
			//imwrite("a.jpeg",Dst);
			//imwrite("b.jpeg",src);
			//imwrite("c.jpeg",frame);
			//waitKey();
		
		}
	}

	return 0;

}	



/*void BubbleSort(int array[],int n)
{
    int i,j,temp;

    for (i = 0;i < n - 1;i++) {
        for (j = 0;j < n - 1;j++) {
            if (array[j + 1] < array[j]) {
                temp = array[j];array[j] = array[j + 1];array[j + 1] = temp;
            }
        }
    }
}*/
>>>>>>> 0a9a67e2daa729127bdca0bf78f985be0c9524b6
