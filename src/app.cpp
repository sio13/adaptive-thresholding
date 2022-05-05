//
// Created by Martin Gano on 05.05.2022.
//

#include "app.h"

using namespace std;
using namespace cv;

void run_app(char **argv) {
    Mat img = readFile(argv[6]);
    Mat dst;
    hconcat(img, img, dst);

    while (true) {
        cv::imshow("Demo App", dst);
        int key = cv::waitKey(0);
        std::cout << key << endl;
        if (key == 27) {
            return;
        }


//        if (key == 3) {
//        }
//        if (key == 2) {
//        }
//        if (key == 97) {
//        }
//        if (key == 115) {
//        }
//        if (key == 100) {
//        }
//        if (key == 102) {
//        }
//        if (key == 103) {
//        }
//        if (key == 104) {
//        }
    }

}