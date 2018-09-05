#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[]){
  
	VideoCapture cap(0);//camera open 
	
	if(!cap.isOpened()){
		return -1;
	}

	//int picture_max = cap.get(CV_CAP_PROP_FRAME_COUNT);
	
	while(1){
		Mat img;//カメラデータ
		Mat hsv;//RGBからHSV
		Mat elmo;//表示するやつ
		Mat bigel;
		Mat element = Mat::ones(3,3,CV_8UC1);
		cap >> img;
		cvtColor(img,hsv,CV_BGR2HSV);
		inRange(hsv,Scalar(0,140,100),Scalar(20,255,255),elmo);
		dilate(elmo,bigel,element,Point(-1,-1),3);
		imshow("elmon",bigel);
 		waitKey(1);
		
	}


	return 0;
}
