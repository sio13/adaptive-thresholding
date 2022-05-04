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


#define METHOD "cv_mean"

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

string split_on_slash(const string& path){
    size_t file_pos = path.find_last_of('/');
    string file_name = path.substr(file_pos + 1, path.length());
    return file_name;
}

int main(int argc, char **argv) {



    ifstream paths("data/augmented_images_paths.txt", ios_base::in);
    while (paths) {
        string png_path;
        paths >> png_path;
        if(!png_path.empty()){
            Mat img = readFile(png_path);

            string png_file_name = split_on_slash(png_path);

            imshow("Display window", img);
            int k = waitKey(0); // Wait for a keystroke in the window

            Mat img_ref, image_final;
            cvtColor(img, img_ref, cv::COLOR_RGB2GRAY);


            if(!strcmp("cv_gauss", METHOD)){
                adaptiveThreshold(img_ref,image_final,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,13,3);
            } else if(!strcmp("cv_mean", METHOD)){
                adaptiveThreshold(img_ref,image_final,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,13,3);
            }

            imshow("Display window", image_final);
            k = waitKey(0);

        }

    }


}