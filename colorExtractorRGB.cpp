//
//  colorExtractorRGB.cpp
//  SampleOpenCV
//
//  Created by 茅島翔 on 2018/07/18.
//  Copyright © 2018年 茅島翔. All rights reserved.
//
//  参考にしたソースコード
//  http://tecsingularity.com/opencv/colorextraction/

#include "main.h"

// 抽出する画像の輝度値の範囲を指定
#define B_MAX 100
#define B_MIN 0
#define G_MAX 255
#define G_MIN 100
#define R_MAX 100
#define R_MIN 0

int colorExtractorRGB(){

    // 入力画像名(ファイルパス)
    //string input_filename = "./puyo_01.png";
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
    // waitKey(5000); // これがないと表示画像が見れない

    // 結果保存用Matを定義
    Mat mask_image, output_image_rgb;
    
    // inRangeを用いてフィルタリング
    // OpenCVではRGBではなく、BGRの順でカラーが設定されている
    Scalar s_min = Scalar(B_MIN, G_MIN, R_MIN);
    Scalar s_max = Scalar(B_MAX, G_MAX, R_MAX);
    inRange(input_image_rgb, s_min, s_max, mask_image);
    
    // マスク画像を表示
    namedWindow("mask");
    imshow("mask", mask_image);
    imwrite("mask.jpg", mask_image);
    
    // マスクを基に入力画像をフィルタリング
    input_image_rgb.copyTo(output_image_rgb, mask_image);

    // 結果の表示と保存
    namedWindow("output");
    imshow("output", output_image_rgb);
    imwrite("output.jpg", output_image_rgb);
    waitKey(0);
    
    return 0;
}
