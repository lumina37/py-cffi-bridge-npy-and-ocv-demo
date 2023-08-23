import libfoo
import cv2 as cv

img = cv.imread("test.png")

img = libfoo.algorithm.mybgr2gray(img)
cv.imshow("debug", img)
cv.waitKey()
cv.destroyAllWindows()
