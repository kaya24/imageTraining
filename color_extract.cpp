//
//  color_extract.cpp
//  SampleOpenCV
//
//  Created by 茅島翔 on 2018/05/29.
//  Copyright © 2018年 茅島翔. All rights reserved.
//
// https://reiji1020.gitbooks.io/play-opencv/content/pickupcolor.html


#include "main.h"

// 抽出する画像の輝度値の範囲を指定
#define H_MAX 180
#define H_MIN 160
#define S_MAX 255
#define S_MIN 50
#define V_MAX 255
#define V_MIN 50

int color_extract_func(){
    uchar hue, sat, val; // Hue, Saturation, Valueを表現する変数
    Mat src_video(Size(640,480),CV_8UC1,Scalar::all(255)); // サイズを指定する
    Mat smooth_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // ノイズを除去した映像を保存する
    Mat hsv_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // HSVに変換した映像を保存する
    Mat frame(Size(640, 480), CV_8UC1, Scalar::all(255));
    Mat dst_img(Size(640, 480), CV_8UC1, Scalar::all(0)); // 認識結果を表示する
    
    char hsvwindow[] = "HSV";
    namedWindow(hsvwindow, CV_WINDOW_AUTOSIZE);
    char dstwindow[] = "Recognition_result";
    namedWindow(dstwindow, CV_WINDOW_AUTOSIZE);
    
    VideoCapture capture(1);

    // カメラが使えない場合はプログラムを止める
    if(!capture.isOpened())
        return -1;
    
    capture.set(CV_CAP_PROP_FRAME_WIDTH,  WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

    while (cvWaitKey(1) == -1)
    {
        dst_img = Scalar(0, 0, 0); // この行を追加
        // カメラから1フレーム取得する
        capture >> frame;
        src_video = frame;
        // imshow(hsvwindow,src_video);
        
        /* ノイズ除去 */
        medianBlur(src_video, smooth_video, 5);
        /* BGRからHSVへ変換 */
        cvtColor(smooth_video, hsv_video, CV_BGR2HSV, 3);
        imshow(hsvwindow, hsv_video);
        
        // H,S,Vの要素に分割する
        /*
        for(int y = 0; y < hsv_video.rows; y++) {
            for (int x = 0; x < hsv_video.cols; x++) {
                hue = hsv_video.at<Vec3b>(y, x)[0];
                sat = hsv_video.at<Vec3b>(y, x)[1];
                val = hsv_video.at<Vec3b>(y, x)[2];
                // 居留地マップの検出 (赤色検出)
                if ((hue < 180 && hue > 160)
                    && (sat <= 255 && sat > 50)
                    && (val <= 255 && val > 50))
                {
                    dst_img.at<uchar>(y, x) = 255;
                }else {
                    dst_img.at<uchar>(y, x) = 0;
                }
            }
        }
        */

        /***********************************************/
        // inRangeを用いてフィルタリング
        Mat mask_image;
        Scalar s_min = Scalar(H_MIN, S_MIN, V_MIN);
        Scalar s_max = Scalar(H_MAX, S_MAX, V_MAX);
        inRange(hsv_video, s_min, s_max, mask_image);
        
        // マスクを基に入力画像をフィルタリング
        hsv_video.copyTo(dst_img, mask_image);
        /***********************************************/
        
        imshow(dstwindow,dst_img);
    }
    
    return 0;
}
