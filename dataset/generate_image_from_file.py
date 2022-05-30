# Author: Nikita Kozlov
# Link: github.com/nyarstot
#
# This file is part of WaifuGenerator neural network
#
# WaifuGenerator is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# WaifuGenerator is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with WaifuGenerator. If not, see <https://www.gnu.org/licenses/>.

import cv2
import numpy as np
import re

pixelDataPattern = re.compile("[0-9.]\+")
pixelData = []

height = 64
width = 64
image = np.zeros((height, width, 3), np.uint8)

file = open("test.txt")

for line in file:
    pixelData = re.findall("[0-9.]+", line)

pdc = 2
for h in range(height):
    for w in range(width):
        image[h][w] = [round(float(pixelData[pdc - 2]) * 255), round(float(pixelData[pdc - 1]) * 255), round(float(pixelData[pdc]) * 255)]
        pdc += 3

cv2.imwrite("test" + ".jpg", image)
cv2.imshow("result", image)
cv2.waitKey()
cv2.destroyAllWindows()