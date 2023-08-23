import os

import cv2 as cv

os.add_dll_directory("D:/Code/source/opencv-4.8.0/build/install/x64/vc17/bin")
import libfoo


img = cv.imread("test.png")

img = libfoo.algorithm.mybgr2gray(img)
cv.imshow("debug", img)
cv.waitKey()
cv.destroyAllWindows()
