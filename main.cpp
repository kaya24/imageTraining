//
//  main.cpp
//  SampleOpenCV
//
//  Created by 茅島翔 on 2018/05/27.
//  Copyright © 2018年 茅島翔. All rights reserved.
//
// xcodeでopencvを使う（導入編）
// http://www.yukisako.xyz/entry/opencv-mac
// xcodeの相対パス設定について
// http://capricciosocantabile.blogspot.jp/2013/10/xcode.html

#include "main.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    /*
     Mat img(256,256, CV_8UC3, Scalar(100, 100, 100));
     circle(img, Point(128, 128), 100, Scalar(200, 100, 100), 4);
     imshow("image",img);
     waitKey(0);
     */
    
    //Read_img();
    //test_camera();
    //detect_feature_func();
    //color_extract_func();
    //colorExtractorRGB();
    colorExtractorHSV();
    
    return 0;
}

int Read_img()
{
    // 画像データをファイルから読み込む
    Mat src = imread("./puyo_01.png");
    
    // 画像の読み込みに失敗したらエラー終了する
    if(src.empty())
    {
        cerr << "Failed to open image file." << endl;
        return -1;
    }
    
    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", src);
    waitKey(5000);
    //destroyAllWindows();
    
    return 0;
}

int test_camera()
{
    cv::VideoCapture cap;
    cap.open(1);
    
    cap.set(CV_CAP_PROP_FRAME_WIDTH,  WIDTH);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);
    
    if(!cap.isOpened()){
        return -1;
    }
    
    cv::namedWindow("Capture", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    while(1)
    {
        cv::Mat frame;
        cap >> frame;
        cv::imshow("Capture", frame);
        
        if(cv::waitKey(30) >= 0)
        {
            cv::imwrite("frame.png",  frame);
            break;
        }
    }
    return 0;
}

