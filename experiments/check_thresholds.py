import sys

import cv2
import matplotlib.pyplot as plt

if __name__ == '__main__':
    exp_img_ = cv2.imread(sys.argv[1])
    for i in range(256):
        img_grey = cv2.cvtColor(exp_img_, cv2.COLOR_BGR2GRAY)
        (T, threshInv) = cv2.threshold(img_grey, i, 255, cv2.THRESH_BINARY)
        f, ax = plt.subplots(1, 2, figsize=(20, 5))

        ax[0].imshow(threshInv, cmap='gray', vmin=0, vmax=255)
        ax[0].axis("off")
        ax[1].imshow(img_grey, cmap='gray', vmin=0, vmax=255)
        ax[1].axis("off")
        plt.savefig(f"gif_data3/{i}")
