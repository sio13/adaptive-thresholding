import os

import imageio
from data_generator import yield_png


def evaluate(processed_data_folder, reference_data_folder):
    res_err_ = 0
    total_pixels_ = 0
    res_err_weighted = 0
    for png_file_ in yield_png(processed_data_folder):
        target_ = imageio.imread(os.path.join(processed_data_folder, png_file_))
        ref_ = imageio.imread(os.path.join(reference_data_folder, png_file_.split("_")[-1]))

        # w_w = b / w
        weight_white = (ref_ == 0).sum() / (ref_ == 255).sum()
        # w_b = w / b
        weight_black = (ref_ == 255).sum() / (ref_ == 0).sum()

        assert (ref_ == 255).sum() + (ref_ == 0).sum() == ref_.shape[0] * ref_.shape[1]
        assert target_.shape == ref_.shape
        res_err_ += (target_ != ref_).sum()
        wrong_white_ = (ref_[ref_ == 255] != target_[ref_ == 255]).sum()
        wrong_black_ = (ref_[ref_ == 0] != target_[ref_ == 0]).sum()
        res_err_weighted += (wrong_white_ * weight_white + wrong_black_ * weight_black)
        total_pixels_ += target_.shape[0] * target_.shape[1]
    print(f"Wrong pixels: {res_err_}")
    print(f"Wrong weighted: {res_err_weighted}")
    print(f"Total pixels: {total_pixels_}")
    print(f"Error: {100 * (res_err_ / total_pixels_)} %")
    print(f"Error weighted: {100 * (res_err_weighted / total_pixels_)} %")


if __name__ == '__main__':
    evaluate("processed_data", "thresholded_references")
