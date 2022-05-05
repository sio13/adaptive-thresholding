//
// Created by Martin Gano on 04.05.2022.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <chrono>

#define AREA 13
#define CONSTANT 3
#define METHOD "cv_gauss"
#define SHOW_IM false
#define VERBOSE false

using namespace std;
using namespace cv;

Mat readFile(const string &image_path) {
    Mat img = imread(image_path, IMREAD_COLOR);

    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        exit(1);
    }
    return img;
}

string split_on_slash(const string &path) {
    size_t file_pos = path.find_last_of('/');
    string file_name = path.substr(file_pos + 1, path.length());
    return file_name;
}

int main(int argc, char **argv) {


    string processed_data_folder = "data/processed_data/";
    ifstream paths("data/augmented_images_paths.txt", ios_base::in);
    long long total_time = 0;
    while (paths) {
        string png_path;
        paths >> png_path;
        if (!png_path.empty()) {
            Mat img = readFile(png_path);

            string png_file_name = split_on_slash(png_path);

            if (SHOW_IM) {
                imshow("Display window", img);
                waitKey(0);
            }


            Mat img_src, img_dst;
            cvtColor(img, img_src, cv::COLOR_RGB2GRAY);

            auto start = chrono::steady_clock::now();
            if (!strcmp("cv_gauss", METHOD)) {
                adaptiveThreshold(img_src,
                                  img_dst,
                                  255,
                                  ADAPTIVE_THRESH_GAUSSIAN_C,
                                  THRESH_BINARY,
                                  AREA,
                                  CONSTANT);
            } else if (!strcmp("cv_mean", METHOD)) {
                adaptiveThreshold(img_src,
                                  img_dst,
                                  255,
                                  ADAPTIVE_THRESH_MEAN_C,
                                  THRESH_BINARY,
                                  AREA,
                                  CONSTANT);
            } else if(!strcmp("cv_global", METHOD)){
                threshold( img_src, img_dst, 127, 255, THRESH_BINARY );
            }
            auto end = chrono::steady_clock::now();
            total_time += chrono::duration_cast<chrono::microseconds>(end - start).count();
            if(VERBOSE){
                cout << "Thresholding: "
                     << chrono::duration_cast<chrono::microseconds>(end - start).count()
                     << " micros"
                     << endl;
            }

            imwrite(processed_data_folder + png_file_name, img_dst);
            if (VERBOSE) {
                cout << "Processing: " << png_path << endl;
            }


            if (SHOW_IM) {
                imshow("Display window", img_dst);
                waitKey(0);
            }
        }
    }
    cout << "Thresholding took: " << total_time << " microseconds";
    return 0;
}