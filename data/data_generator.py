import argparse
import os
from random import randint

import cv2
import numpy as np


def distance_matrix_v2(image_, index_):
    """
    Computes matrix of the distances of given point from the `image_`
    :param image_: original image
    :param index_: 2D index of the "light source"
    :return: 2D numpy array with floating point numbers with same shape as image_
    """
    i, j = np.indices(image_.shape[:2], sparse=True)
    return np.sqrt((i - index_[0]) ** 2 + (j - index_[1]) ** 2)


def add_shadow_to_black_and_white(image_, distance_matrix_, normalize_coefficient_, lighten_coefficient=100):
    """
    Subtracts original image by distance array to create shadow
    :param lighten_coefficient: coefficient to increase brightness in some points
    :param image_: original image with only one channel
    :param distance_matrix_: 2D numpy array with floating point numbers with same shape as image_
    :param normalize_coefficient_: distance_matrix_ is normalized to bring useful values
    :return: 2D array with implanted shadow
    """

    distance_matrix_ = distance_matrix_ / normalize_coefficient_
    distance_matrix_ -= lighten_coefficient
    xx = image_ - distance_matrix_ > 0
    yy = image_ - distance_matrix_ < 255

    image_[np.logical_and(xx, yy)] -= distance_matrix_[np.logical_and(xx, yy)].astype('uint8')
    image_[xx != True] = 0
    image_[yy != True] = 255
    return image_


# to keep image readable keep normalizing_coefficient_ below or equal 250
def distance_matrix_norm_coefficient(distances_matrix_, normalizing_coefficient_):
    return distances_matrix_.max() / normalizing_coefficient_


def get_random_index(image_):
    x_shape_, y_shape_ = image_.shape[0], image_.shape[1]
    return randint(0, x_shape_), randint(0, y_shape_)


def yield_png(folder_path_):
    for png_file_ in os.listdir(folder_path_):
        if png_file_.endswith(".png"):
            yield png_file_


def create_threshold_references(original_data_folder, threshold_references_folder):
    for png_file_ in yield_png(original_data_folder):
        original_png_ = cv2.imread(os.path.join(original_data_folder, png_file_))
        img_grey_ = cv2.cvtColor(original_png_, cv2.COLOR_BGR2GRAY)
        threshed_ = cv2.adaptiveThreshold(src=img_grey_,
                                          maxValue=255,
                                          adaptiveMethod=cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
                                          thresholdType=cv2.THRESH_BINARY,
                                          blockSize=15,
                                          C=3)
        cv2.imwrite(os.path.join(threshold_references_folder, png_file_), threshed_)


def create_shaded_dataset(threshold_references_folder, augmented_data_folder, random_indexes_=10):
    for png_file_ in yield_png(threshold_references_folder):
        for _ in range(random_indexes_):
            threshed_png_ = cv2.imread(os.path.join(threshold_references_folder, png_file_), cv2.IMREAD_GRAYSCALE)
            random_index_ = get_random_index(image_=threshed_png_)
            distances_matrix_ = distance_matrix_v2(image_=threshed_png_, index_=random_index_)

            for normalizing_coefficient_ in [230, 240, 250, 254, 256, 260, 265, 280, 300, 350, 400]:
                # restore original image
                threshed_png_ = cv2.imread(os.path.join(threshold_references_folder, png_file_), cv2.IMREAD_GRAYSCALE)
                distance_normalization_coefficient_ = distance_matrix_norm_coefficient(
                    distances_matrix_=distances_matrix_,
                    normalizing_coefficient_=normalizing_coefficient_)
                res_ = add_shadow_to_black_and_white(image_=threshed_png_,
                                                     distance_matrix_=distances_matrix_,
                                                     normalize_coefficient_=distance_normalization_coefficient_)
                new_file_name_ = f"{random_index_[0]}_{random_index_[1]}_{normalizing_coefficient_}_{png_file_}"
                cv2.imwrite(os.path.join(augmented_data_folder, new_file_name_), res_)


if __name__ == '__main__':
    parser: argparse.ArgumentParser = argparse.ArgumentParser(description="Generator for shaded data")
    parser.add_argument('--original_data_path',
                        default='original_data',
                        help='Original data before initial thresholding')

    parser.add_argument('--threshold_references_data_path',
                        default='thresholded_references',
                        help='Path to folder with threshold samples')

    parser.add_argument('--augmented_data_path',
                        default='augmented_data',
                        help='Path to folder with augmented data samples')

    parser.add_argument('--random_indexes_per_sample',
                        default=10,
                        help='Number of entries in the root directory')

    parser.add_argument('--needs_references',
                        action='store_true',
                        help='Set for generating new references')

    args = parser.parse_args()

    if args.needs_references:
        create_threshold_references(args.original_data_path,
                                    args.threshold_references_data_path)
    create_shaded_dataset(args.threshold_references_data_path,
                          args.augmented_data_path,
                          random_indexes_=args.random_indexes_per_sample)
