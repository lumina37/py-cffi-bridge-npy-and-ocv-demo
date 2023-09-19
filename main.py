import cv2 as cv

import libfoo

img = cv.imread("test.jpg")

img = libfoo.algorithm.mybgr2gray(img)
cv.imshow("debug", img)
cv.waitKey()
cv.destroyAllWindows()
