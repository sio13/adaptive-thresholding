#!/usr/bin/env python3

import subprocess
import sys

print("Running app")
if len(sys.argv) <= 1:
    png_path_ = "data/augmented_data/2_1185_230_70_6.png"
else:
    png_path_ = sys.argv[1]
method = "GLOBAL"
p = subprocess.run(f"./adaptive-thresholding c c c c APP {png_path_} {method}", shell=True)