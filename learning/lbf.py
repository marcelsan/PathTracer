#! /usr/bin/python

import sys
import os
import random
import tensorflow as tf
import numpy as np


def generate_groud_truth(filenames=[]):
    for fn in filenames:
        arr = np.load(fn, mmap_mode='r')
        arr = np.average(arr, axis=1)
        np.save('gt-' + fn, arr)


def get_random_frames(fn, spp=64, windowsize=55):
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

def avg_and_std(frame):
    avg = np.average(arr[:,:,:,:3], axis=0)
    std = np.std(arr[:,:,:,:3], axis=0)
    return np.append(avg, std, axis=3) 

def show_frames(arr, gt):
    import matplotlib.pyplot as plt
    plt.subplot(1, 2, 1)
    plt.imshow(np.average(arr[:,:,:,:3], axis=0))
    plt.subplot(1, 2, 2)
    plt.imshow(gt[:,:,:3])
    plt.show()

def create_neural_network(x, spp=64, windowsize=55):
    layer1 = spp * windowsize * 2
    layer2 = spp * windowsize
    layer3 = spp * windowsize / 2
    layer4 = layer1

    # First layer
    W1 = tf.Variable(tf.random_uniform([layer1, layer2]))
    b1 = tf.Variable(tf.random_uniform([layer2]))
    x1 = tf.sigmoid(tf.matmul(x, W1) + b1)

    # Second layer
    secLayerSize = spp * windowsize
    W2 = tf.Variable(tf.random_uniform([layer2, layer3]))
    b2 = tf.Variable(tf.random_uniform([layer3]))
    x2 = tf.sigmoid(tf.matmul(x1, W2) + b2)

    # Third layer
    secLayerSize = spp * windowsize
    W3 = tf.Variable(tf.random_uniform([layer3, layer4]))
    b3 = tf.Variable(tf.random_uniform([layer4]))
    # Using softmax is an addition to kalantari
    x3 = tf.nn.softmax(tf.matmul(x2, W3) + b3)

    return x3

def mse(x, y):
    return tf.reduce_mean(tf.square(x - y))

if __name__ == '__main__':
    try:
        for fn in sys.argv[1:]:
            os.stat(fn)
    except OSError:
        generate_groud_truth(sys.argv[1:])

    random_frames = get_random_frames(sys.argv[1])
    arr, gt = next(random_frames)
    print(arr.shape)
    print(gt.shape)
    # show_frames(arr, gt)

    graph = tf.Graph()
    with graph.as_default():
        spp=64
        windowsize=55
        x = tf.placeholder(tf.float32, [1, spp * windowsize * 2], name='x') # 2 is for avg and std
        y = create_neural_network(x, spp, windowsize)
        y_ = tf.placeholder(tf.float32, [1, spp * windowsize * 2], name='y_')
        train = tf.train.AdamOptimizer().minimize(mse(y, y_))

        sess = tf.Session()
        sess.run(tf.initialize_all_variables())

        arr, gt = next(random_frames)
        train.run(session=sess, feed_dict={'x': arr, 'y_': gt})
