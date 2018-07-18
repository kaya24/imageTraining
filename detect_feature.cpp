//
//  detect_feature.cpp
//  SampleOpenCV
//
//  Created by 茅島翔 on 2018/05/29.
//  Copyright © 2018年 茅島翔. All rights reserved.
//

#include "main.h"

void detect_feature_func(){
    
    //読み込む画像のパス
    cv::String scene1_path = "./puyo_01.png";
    cv::String scene2_path = "./puyo_01.png";
    
    //書き出す画像のパス
    cv::String scene_12_path = "imgPath12.png";
    
    //比較用画像を読み込む (アルファチャンネル非対応のため、IMREAD_COLORで強制する)
    //-1(自動判別) 0(グレー) 1(デフォ)
    cv::Mat scene1 = cv::imread(scene1_path, 1);
    cv::Mat scene2 = cv::imread(scene2_path, 1);
    
    //AKAZE
    auto algorithm = cv::AKAZE::create();
    
    //KAZE
    //auto algorithm = cv::KAZE::create();
    
    //ORB
    //auto algorithm = cv::ORB::create();
    
    //BRISK
    //auto algorithm = cv::BRISK::create();
    
    //FAST
    //auto algorithm = cv::FastFeatureDetector::create();
    
    
    // 特徴点抽出
    std::vector<cv::KeyPoint> keypoint1, keypoint2;
    algorithm->detect(scene1, keypoint1);
    algorithm->detect(scene2, keypoint2);
    
    
    // 特徴記述
    cv::Mat descriptor1, descriptor2;
    algorithm->compute(scene1, keypoint1, descriptor1);
    algorithm->compute(scene2, keypoint2, descriptor2);
    
    // マッチング (アルゴリズムにはBruteForceを使用)
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce");
    std::vector<cv::DMatch> match, match12, match21;
    matcher->match(descriptor1, descriptor2, match12);
    matcher->match(descriptor2, descriptor1, match21);
    //クロスチェック(1→2と2→1の両方でマッチしたものだけを残して精度を高める)
    for (size_t i = 0; i < match12.size(); i++)
    {
        cv::DMatch forward = match12[i];
        cv::DMatch backward = match21[forward.trainIdx];
        if (backward.trainIdx == forward.queryIdx)
        {
            match.push_back(forward);
        }
    }
    
    // マッチング結果の描画
    cv::Mat dest;
    cv::drawMatches(scene1, keypoint1, scene2, keypoint2, match, dest);
    
    //マッチング結果の書き出し
    cv::imwrite(scene_12_path, dest);
    
    return ;
}
