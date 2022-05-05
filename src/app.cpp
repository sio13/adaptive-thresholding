//
// Created by Martin Gano on 05.05.2022.
//

#include "app.h"

using namespace std;
using namespace cv;

void run_app(char **argv) {
    Mat img = readFile(argv[6]);
    Mat img_src, img_dst;
    cvtColor(img, img_src, cv::COLOR_RGB2GRAY);
    Mat dst;

    int global_threshold = 0;
    int method = 0;
    int area = 13;
    int constant = 3;
    bool global = true;

    while (true) {
        int mm;
        int am;
        if (method == 0) {
            mm = THRESH_BINARY;
        } else if (method == 1) {
            mm = THRESH_BINARY_INV;
        } else if (method == 2 and global) {
            mm = THRESH_TRUNC;
        } else if (method == 3 and global) {
            mm = THRESH_OTSU;
        } else if (method == 4 and global) {
            mm = THRESH_TRIANGLE;
        }

        if (global) {
            threshold(img_src, img_dst, global_threshold, 255, mm);
        } else {
            adaptiveThreshold(img_src,
                              img_dst,
                              255,
                              am,
                              mm,
                              area,
                              constant);
        }

        hconcat(img_src, img_dst, dst);
        cv::imshow("Demo App", dst);
        int key = cv::waitKey(0);
        cout << key << endl;
        if (key == 27) {
            return;
        }
        if (key == 3) {
            global_threshold = max(global_threshold - 1, 0);
        }
        if (key == 2) {
            global_threshold = min(global_threshold + 1, 255);
        }

        if (key == 49) {
            method = 0;
            cout << "Binary" << endl;
        }
        if (key == 50) {
            method = 1;
            cout << "Inv" << endl;
        }
        if (key == 51) {
            method = 2;
            cout << "Trunc" << endl;
        }
        if (key == 52) {
            method = 3;
            cout << "Otsu" << endl;
        }
        if (key == 53) {
            method = 4;
            cout << "Triangle" << endl;
        }
        if (key == 103) {
            global = not global;
            mm = THRESH_BINARY;
            cout << "Global is : " << (global ? "enabled" : "disabled") << endl;
        }

        if (key == 97) {
            img_src = img(cv::Range(0, img_src.rows), cv::Range(0, img_src.cols >> 1));
            cvtColor(img_src, img_src, cv::COLOR_RGB2GRAY);
        }
        if (key == 115) {
            img_src = img(cv::Range(0, img_src.rows), cv::Range(img_src.cols >> 1, img_src.cols));
            cvtColor(img_src, img_src, cv::COLOR_RGB2GRAY);
        }
        if (key == 100) {
            cvtColor(img, img_src, cv::COLOR_RGB2GRAY);
        }

        if (key == 110) {
            if(area - 2 > 1){
                area = area - 2;
            }
            cout << "Area is: " << area << endl;
        }
        if (key == 109) {
            area += 2;
            cout << "Area is: " << area << endl;
        }

        if (key == 118) {
            constant--;
            cout << "Constant is: " << constant << endl;
        }
        if (key == 98) {
            constant++;
            cout << "Constant is: " << constant << endl;
        }

        if (key == 112) {
            am = ADAPTIVE_THRESH_MEAN_C;
            cout << "The method is mean" << endl;
        }
        if (key == 111) {
            am = ADAPTIVE_THRESH_GAUSSIAN_C;
            cout << "The method is gaussian" << endl;
        }

        cout << "The global threshold is:  " << global_threshold << endl;

    }

}