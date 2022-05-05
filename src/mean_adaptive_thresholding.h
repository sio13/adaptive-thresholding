//
// Created by Martin Gano on 05.05.2022.
//

#ifndef ADAPTIVE_THRESHOLDING_MEAN_ADAPTIVE_THRESHOLDING_H
#define ADAPTIVE_THRESHOLDING_MEAN_ADAPTIVE_THRESHOLDING_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

void adaptiveThreshold(cv::Mat &src, cv::Mat &dst, int blockSize, double C);

#endif //ADAPTIVE_THRESHOLDING_MEAN_ADAPTIVE_THRESHOLDING_H
