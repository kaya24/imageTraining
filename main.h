//
//  main.h
//  SampleOpenCV
//
//  Created by 茅島翔 on 2018/05/29.
//  Copyright © 2018年 茅島翔. All rights reserved.
//

#ifndef main_h
#define main_h

#include <stdio.h>
#include <cv.h>
#include <highgui.h>

#include <opencv.hpp>
#include <core.hpp>
#include <imgcodecs.hpp>
#include <highgui.hpp>
#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

#define WIDTH  640
#define HEIGHT 480


/* プロトタイプ宣言 */
int Read_img();
int test_camera();
void detect_feature_func();
int color_extract_func();
int colorExtractorRGB();
int colorExtractorHSV();

    
#endif /* main_h */
