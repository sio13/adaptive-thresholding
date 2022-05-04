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


def add_shadow(image_, distance_matrix_, normalize_coefficient_):
    """
    Subtracts original image by distance array to create shadow
    :param image_: original image
    :param distance_matrix_: 2D numpy array with floating point numbers with same shape as image_
    :param normalize_coefficient_: distance_matrix_ is normalized to bring useful values
    :return: 2D array with implanted shadow
    """
    hsv = cv2.cvtColor(image_, cv2.COLOR_BGR2HSV)
    h, s, v = cv2.split(hsv)

    distance_matrix_ = distance_matrix_ / normalize_coefficient_
    xx = v - distance_matrix_ > 2

    v[xx] -= distance_matrix_[xx].astype('uint8')

    final_hsv = cv2.merge((h, s, v))
    img = cv2.cvtColor(final_hsv, cv2.COLOR_HSV2BGR)
    return img
