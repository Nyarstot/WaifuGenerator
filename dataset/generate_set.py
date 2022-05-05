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

# The original lbcascade_animeface.xnl was provided by nagadomi 
# and is used under license from the product.
# https://github.com/nagadomi/lbpcascade_animeface

import cv2
import os
from os.path import exists

def detect_face_and_save(img, filename : str):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.03, 5)
    for face in faces:
        x,y,w,h = face
        crop_img = img[y:y+h, x:x+w]
        cv2.imwrite(os.path.join('clean', filename), crop_img)

face_cascade = cv2.CascadeClassifier(r'lbpcascade_animeface/lbpcascade_animeface.xml')
raw_folder = r'raw/'

if not os.path.exists('clean'):
    os.mkdir('clean')

counter = 1
for file in os.listdir(raw_folder):
    image = cv2.imread(os.path.join(raw_folder, file))
    if image is not None:
        detect_face_and_save(image, 'dsetimage_' + str(counter) + '.jpg')
        counter += 1

print('DONE')