//
// Created by Martin Gano on 05.05.2022.
//
#include "mean_adaptive_thresholding.h"

using namespace std;
using namespace cv;

void adaptiveThreshold(Mat &src, Mat &dst, int blockSize, double C) {
    dst = cv::Mat::zeros(src.size(), src.type());
    cv::Mat integral_image = cv::Mat::zeros(cv::Size(src.cols + 1, src.rows + 1), CV_32SC1);

    for (int j = 0; j < src.rows; ++j) {
        for (int i = 0; i < src.cols; ++i) {
            int left;
            if(i - 1 < 0){
                left = 0;
            } else {
                left =  integral_image.at<int>(j, i - 1, 0);
            }
            int up;
            if(j - 1 < 0){
                up = 0;
            } else {
                up = integral_image.at<int>(j - 1, i, 0);
            }

            int left_up;
            if(j - 1 < 0 && i - 1 < 0){
                left_up = 0;
            } else {
                left_up = integral_image.at<int>(j - 1, i - 1, 0);
            }

            integral_image.at<int>(j, i, 0) = left + up + (int)src.at<unsigned char>(j, i, 0) - left_up;
        }
    }

    int half_block_size = blockSize >> 1;
    for (int j = 0; j < src.rows; ++j) {
        for (int i = 0; i < src.cols; ++i) {

            int i_minus_half_block_size = max(i - half_block_size - 1, 0);
            int i_plus_half_block_size = min(i + half_block_size + 1, src.cols);

            int j_minus_half_block_size = max(j - half_block_size - 1, 0);
            int j_plus_half_block_size = min(j + half_block_size + 1, src.rows);

            int left_residual = integral_image.at<int>(j_plus_half_block_size - 1, i_minus_half_block_size - 1, 0);
            int up_residual = integral_image.at<int>(j_minus_half_block_size - 1, i_plus_half_block_size - 1, 0);

            int inters;
            if (i_minus_half_block_size - 1 > 0 && j_minus_half_block_size - 1 > 0){
                inters = integral_image.at<int>(j_minus_half_block_size - 1, i_minus_half_block_size - 1, 0);
            } else {
                inters = 0;
            }

            int alt_buffer = integral_image.at<int>(j_plus_half_block_size - 1, i_plus_half_block_size - 1, 0) -
                             left_residual - up_residual + inters;

            int pixels_cnt = (j_plus_half_block_size - j_minus_half_block_size)
                             * (i_plus_half_block_size - i_minus_half_block_size);
            float threshold = alt_buffer / pixels_cnt - C;
            dst.at<unsigned char>(j, i, 0) = src.at<unsigned char>(j, i, 0) > threshold ? 255 : 0;
        }
    }

    return;
}