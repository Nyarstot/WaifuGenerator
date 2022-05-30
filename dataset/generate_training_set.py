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
import glob

file = open('AnimeFaceTrainingData.txt', "a")

for image in glob.glob('clean\clenSize64\*.jpg'):
    img = cv2.imread(image)
    height, width = img.shape[:2]

    for i in range(height):
        for j in range(width):
            pixel_b, pixel_g, pixel_r = img[i][j] / 255.0

            pixel_r = "%.6f" % pixel_r
            pixel_g = "%.6f" % pixel_g
            pixel_b = "%.6f" % pixel_b

            file.write("[" + pixel_r + "," + pixel_g + "," + pixel_b + "]")
        file.write('\n')
    print("Done with file: " + image)
    file.write("<TRAIN_DATA_REGION_END>\n")

file.close()
print("DONE")