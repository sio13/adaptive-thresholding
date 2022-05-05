import os

import sys
from data_generator import yield_png


def generate_augmented_paths(augmented_data_folder,
                             augmented_paths_filename="augmented_images_paths.txt"):
    augmented_paths_file_ = open(augmented_paths_filename, "w")
    for png_file_ in yield_png(augmented_data_folder):
        augmented_paths_file_.write(os.path.join("data", augmented_data_folder, png_file_))
        augmented_paths_file_.write("\n")


if __name__ == '__main__':
    augmented_data_folder = "augmented_data" if len(sys.argv) <= 1 else sys.argv[1]
    generate_augmented_paths(augmented_data_folder)
