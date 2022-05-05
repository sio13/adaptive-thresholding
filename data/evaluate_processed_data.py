import os

import imageio
from data_generator import yield_png


def evaluate(processed_data_folder, reference_data_folder):
    res_err_ = 0
    total_pixels_ = 0
    for png_file_ in yield_png(processed_data_folder):
        target_ = imageio.imread(os.path.join(processed_data_folder, png_file_))
        ref_ = imageio.imread(os.path.join(reference_data_folder, png_file_.split("_")[-1]))
        assert target_.shape == ref_.shape
        res_err_ += (target_ != ref_).sum()
        total_pixels_ += target_.shape[0] * target_.shape[1]
    print(res_err_)
    print(total_pixels_)


if __name__ == '__main__':
    evaluate("processed_data", "thresholded_references")
