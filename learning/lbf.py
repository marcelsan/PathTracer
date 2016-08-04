#! /usr/bin/python
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-7.5/lib64/

import sys
import random
import tensorflow as tf
import numpy as np


def generate_groud_truth(filenames=[]):
    for fn in filenames:
        arr = np.load(fn, mmap_mode='r')
        arr = np.average(arr, axis=1)
        np.save('gt-' + fn, arr)


def get_random_frames(fn, spp=16, windowsize=16):
    arr = np.load(fn, mmap_mode='r')
    gt = np.load('gt-' + fn, mmap_mode='r')
    frames, samples, width, height, _ = arr.shape
    width -= windowsize
    height -= windowsize
    samples -= spp
    while True:
        rand_frame = random.randrange(0, frames)
        rand_samples = random.randrange(0, samples)
        rand_width = random.randrange(0, width)
        rand_height = random.randrange(0, height)

        sample_slice = slice(rand_samples, rand_samples + spp)
        width_slice = slice(rand_width, rand_width + windowsize)
        height_slice = slice(rand_height, rand_height + windowsize)

        yield arr[rand_frame, sample_slice, width_slice, height_slice,:], \
            gt[rand_frame, width_slice, height_slice, :]


if __name__ == '__main__':
    generate_groud_truth(sys.argv[1:])
    random_frames = get_random_frames(sys.argv[1])
    arr, gt = next(random_frames)
    print(arr.shape)
    print(gt.shape)
