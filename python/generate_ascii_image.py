# -*- coding: utf-8 -*-
"""
@author: zhipeng.ge @ 20241017
@file: tmp.py
@brief: tmp
"""
import matplotlib.pyplot as plt

import numpy as np
import os
import cv2

def generage_image(ch, patch_size):
    img = np.zeros((patch_size, patch_size), dtype=np.uint8)
    # make sure the text is in the center
    font = cv2.FONT_HERSHEY_TRIPLEX
    font_scale = patch_size / 40
    font_thickness = patch_size // 32
    font_thickness = max(1, font_thickness)
    text_size = cv2.getTextSize(ch, font, font_scale, font_thickness)[0]
    text_x = (patch_size - text_size[0]) // 2
    text_y = (patch_size + text_size[1]) // 2
    img = cv2.putText(img, ch, (text_x, text_y), font, font_scale, 255, font_thickness)
    return img

def generage_images(patch_size, save_dir):
    os.makedirs(save_dir, exist_ok=True)
    imgs = []
    for i in range(32, 128):
        print(f"generating {chr(i)}")
        img = generage_image(chr(i), patch_size)
        imgs.append(img)
    # reshape
    cols = 8
    rows = (len(imgs) + cols - 1) // cols
    total = np.zeros((rows * patch_size, cols * patch_size), dtype=np.uint8)
    for i, img in enumerate(imgs):
        r = i // cols
        c = i % cols
        total[r*patch_size:(r+1)*patch_size, c*patch_size:(c+1)*patch_size] = img
    image_path = os.path.join(save_dir, f"ascii_{patch_size}.png")
    cv2.imwrite(image_path, total)


if __name__ == "__main__":
    # for i in range(8, 128):
    #     if i % 8 == 0:
    #         generage_images(i, "tmp/ascii")
    # write such image buffer of each ascii character into a header file
    header_filename = "src/cv/ascii_image.h"
    with open(header_filename, "w") as f:
        f.write("#ifndef ASCII_IMAGE_H\n")
        f.write("#define ASCII_IMAGE_H\n")
        for i in range(1, 9):
            patch_size = i * 8
            f.write(f"static const unsigned char ascii_image_{patch_size}[][{patch_size * patch_size}] = {{\n")
            for ch in range(32, 128):
                img = generage_image(chr(ch), patch_size)
                f.write("{\n")
                for row in range(len(img)):
                    for col in range(len(img[row])):
                        index = row * len(img[row]) + col
                        if index == patch_size * patch_size - 1:
                            f.write(f"{img[row][col] // 255}")
                        else:
                            f.write(f"{img[row][col] // 255},")
                    if row != len(img) - 1:
                        f.write("\n")
                if ch != 127:
                    f.write("},\n")
                else:
                    f.write("}\n")
            f.write("};\n")
        f.write("#define MAX_FONT_SIZE_VALUE 8\n")
        f.write("#define MIN_FONT_SIZE_VALUE 1\n")
        f.write("#define MAX(x, y) ((x) > (y) ? (x) : (y))\n")
        f.write("#define MIN(x, y) ((x) < (y) ? (x) : (y))\n")
        f.write("static inline int adjust_font_size(int font_size) {\n")
        f.write("    return MIN(MAX(font_size, MIN_FONT_SIZE_VALUE), MAX_FONT_SIZE_VALUE);\n")
        f.write("}\n")
        f.write("static inline const unsigned char* get_ascii_image(int font_size, char ch) {\n")
        f.write("    int adjusted_font_size = adjust_font_size(font_size) * 8;\n")
        f.write("    unsigned chr = ch < 32 || ch > 126 ? 0 : ch - 32;\n")
        f.write("    switch (adjusted_font_size) {\n")
        for i in range(1, 9):
            patch_size = i * 8
            f.write(f"        case {patch_size}: return ascii_image_{patch_size}[chr];\n")
        f.write("        default: return ascii_image_8[chr]; // impossible\n")
        f.write("    }\n")
        f.write("}\n")
        f.write("#endif  // ASCII_IMAGE_H\n")