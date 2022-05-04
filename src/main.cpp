//
// Created by Martin Gano on 04.05.2022.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>

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

int main(int argc, char **argv) {



    ifstream paths("data/augmented_images_paths.txt", ios_base::in);
    while (paths) {
        string png_path;
        paths >> png_path;
        if(!png_path.empty()){
            Mat img = readFile(png_path);

            imshow("Display window", img);
            int k = waitKey(0); // Wait for a keystroke in the window
            if (k == 's') {
                imwrite("starry_night.png", img);
            }
        }

    }


}