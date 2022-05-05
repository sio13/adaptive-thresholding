//
// Created by Martin Gano on 05.05.2022.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include <string>
#include <chrono>
#include "adaptive_thresholding.h"



#ifndef ADAPTIVE_THRESHOLDING_MAIN_BASE_H
#define ADAPTIVE_THRESHOLDING_MAIN_BASE_H

void processData(char **argv);
cv::Mat readFile(const std::string &image_path);

#endif //ADAPTIVE_THRESHOLDING_MAIN_BASE_H
