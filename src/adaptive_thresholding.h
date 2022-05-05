//
// Created by Martin Gano on 05.05.2022.
//

#ifndef ADAPTIVE_THRESHOLDING_ADAPTIVE_THRESHOLDING_H
#define ADAPTIVE_THRESHOLDING_ADAPTIVE_THRESHOLDING_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "mean_adaptive_thresholding.h"

#define CUSTOM_ADAPTIVE_THRESH_GAUSSIAN_C 0
#define CUSTOM_ADAPTIVE_THRESH_MEAN_C 1


void adaptiveThreshold(cv::Mat &src,
                       cv::Mat &dst,
                       int adaptiveMethod,
                       int blockSize,
                       double C);

#endif //ADAPTIVE_THRESHOLDING_ADAPTIVE_THRESHOLDING_H
