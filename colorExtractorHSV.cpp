//
//  colorExtractorHSV.cpp
//  SampleOpenCV
//
//  Created by 茅島翔 on 2018/07/18.
//  Copyright © 2018年 茅島翔. All rights reserved.
//

/*
BがH値、GがS値、RがV値になっています。
よって、暗いところほど赤くなったりしている。
このHSV値に対してフィルタを掛けますが、注意点があります。
① 色相(H)：0～180 (×2すると度数になり、0～360度を示す)
② 彩度(S)：0～255
③ 明度(V)：0～255
 
*/
#include "main.h"

// 抽出する画像の輝度値の範囲を指定
#define H_MAX 180
#define H_MIN 160
#define S_MAX 255
#define S_MIN 50
#define V_MAX 255
#define V_MIN 50

int colorExtractorHSV(){

    // 入力画像名(ファイルパス)
    string input_filename = "./field01.png";

    // 画像を3チャンネル(BGR)で読み込む
    Mat input_image_rgb = imread(input_filename, CV_LOAD_IMAGE_COLOR);
    if (input_image_rgb.empty()) {
        cerr << "入力画像が見つかりません" << endl;
        return -1;
    }
    
    // 表示して確認
    namedWindow("input_RGB");
    imshow("input_RGB", input_image_rgb);

    // BGRからHSVへ変換
    Mat hsv_image, mask_image, output_image;
    cvtColor(input_image_rgb, hsv_image, CV_BGR2HSV, 3);
    
    // HSV変換した画像を表示して確認
    namedWindow("input_HSV");
    imshow("input_HSV", hsv_image);
    imwrite("hsv.jpg", hsv_image);
    
    // inRangeを用いてフィルタリング
    Scalar s_min = Scalar(H_MIN, S_MIN, V_MIN);
    Scalar s_max = Scalar(H_MAX, S_MAX, V_MAX);
    inRange(hsv_image, s_min, s_max, mask_image);
    
    // マスク画像を表示
    namedWindow("mask");
    imshow("mask", mask_image);
    imwrite("mask.jpg", mask_image);
    
    // マスクを基に入力画像をフィルタリング
    input_image_rgb.copyTo(output_image, mask_image);
    
    // 結果の表示と保存
    namedWindow("output");
    imshow("output", output_image);
    imwrite("output.jpg", output_image);
    waitKey(0);
    
    
    return 0;
}

