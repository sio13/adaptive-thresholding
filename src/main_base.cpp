//
// Created by Martin Gano on 05.05.2022.
//

#include "main_base.h"

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

void selectMethod(Mat &img_src, Mat &img_dst, char **argv) {
    int area = stoi(argv[2]);
    int constant = stoi(argv[3]);
    int global_threshold = stoi(argv[4]);

    if (!strcmp("cv_gauss", argv[1])) {
        adaptiveThreshold(img_src,
                          img_dst,
                          255,
                          ADAPTIVE_THRESH_GAUSSIAN_C,
                          THRESH_BINARY,
                          area,
                          constant);
    } else if (!strcmp("cv_mean", argv[1])) {
        adaptiveThreshold(img_src,
                          img_dst,
                          255,
                          ADAPTIVE_THRESH_MEAN_C,
                          THRESH_BINARY,
                          area,
                          constant);
    } else if (!strcmp("cv_global", argv[1])) {
        threshold(img_src, img_dst, global_threshold, 255, THRESH_BINARY);
    } else if (!strcmp("cv_otsu", argv[1])) {
        threshold(img_src, img_dst, 0, 255, THRESH_BINARY + THRESH_OTSU);
    } else if (!strcmp("cv_otsu_gauss_blur", argv[1])) {
        GaussianBlur(img_src, img_dst, Size(5, 5), 0);
        threshold(img_dst, img_dst, 0, 255, THRESH_BINARY + THRESH_OTSU);
    } else if (!strcmp("mean", argv[1])) {
        adaptiveThreshold(img_src,
                          img_dst,
                          CUSTOM_ADAPTIVE_THRESH_MEAN_C,
                          area,
                          constant);
    }
}

void processData(char **argv) {
    string processed_data_folder = "data/processed_data/";
    ifstream paths("data/augmented_images_paths.txt", ios_base::in);
    long long total_time = 0;
    int images_count = 0;
    while (paths) {
        string png_path;
        paths >> png_path;
        images_count++;
        if (!png_path.empty()) {
            Mat img = readFile(png_path);

            string png_file_name = split_on_slash(png_path);


            Mat img_src, img_dst;
            cvtColor(img, img_src, cv::COLOR_RGB2GRAY);

            auto start = chrono::steady_clock::now();

            selectMethod(img_src, img_dst, argv);

            auto end = chrono::steady_clock::now();
            total_time += chrono::duration_cast<chrono::microseconds>(end - start).count();

            imwrite(processed_data_folder + png_file_name, img_dst);
        }
    }
    cout << "Thresholding took: " << total_time << " microseconds" << endl;
    cout << "Processed " << images_count << " images" << endl;
}