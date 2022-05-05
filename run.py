#!/usr/bin/env python3

import subprocess
import os
import sys

method = "mean"
area = 13
constant = 3
global_threshold = 50

if len(sys.argv) > 1 and sys.argv[1] == 'force_new':
    os.system("cmake . && make")
    print("Built successfully")

    print("Creating folder data/augmented_data")
    os.makedirs("data/augmented_data")
    print("Creating folder data/processed_data")
    os.makedirs("data/processed_data")
    print("Creating folder data/thresholded_references")
    os.makedirs("data/thresholded_references")

    print("Generating data")
    os.system("cd data && python3 data_generator.py --needs_references")
    print("Generating paths")
    os.system("cd data && python3 generate_augmented_paths.py")

print("Running thresholding")
p = subprocess.run(f"./adaptive-thresholding {method} {area} {constant} {global_threshold}", shell=True)

print("Running evaluation")
os.system("cd data && python3 evaluate_processed_data.py")
