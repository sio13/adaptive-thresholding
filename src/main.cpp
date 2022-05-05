//
// Created by Martin Gano on 04.05.2022.
//

#include "main_base.h"
#include "app.h"

using namespace std;
using namespace cv;


int main(int argc, char **argv) {

    if (!strcmp("EXP", argv[5])){
        processData(argv);
    } else if (!strcmp("APP", argv[5])){
        run_app(argv);
    }

    return 0;
}