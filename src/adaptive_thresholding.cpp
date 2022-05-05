//
// Created by Martin Gano on 05.05.2022.
//

#include "adaptive_thresholding.h"

using namespace std;
using namespace cv;


void adaptiveThreshold(Mat &src,
                       Mat &dst,
                       int adaptiveMethod,
                       int blockSize,
                       double C) {

    if (adaptiveMethod == CUSTOM_ADAPTIVE_THRESH_MEAN_C) {
        adaptiveThreshold(src, dst, blockSize, C);
    }

    return;
}