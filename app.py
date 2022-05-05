#!/usr/bin/env python3

import subprocess


print("Running app")
hh = "data/augmented_data/2_1185_230_70_6.png"
p = subprocess.run(f"./adaptive-thresholding c c c c APP {hh}", shell=True)