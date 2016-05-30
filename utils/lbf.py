import sys
import tensorflow as tf
import numpy as np

tf.InteractiveSession()

def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

samples = np.load(sys.argv[1])
n_instances, height, width, feat_size = samples.shape

x = tf.placeholder(tf.float32, [None, height, width, feat_size])
y_ = tf.placeholder(tf.float32, [None, height, width, 3])

def network(x):
    w_conv1 = tf.Variable(tf.random_uniform((5, 5, feat_size, 32)))
    b_conv1 = tf.Variable(tf.random_uniform((32,)))

    w_conv2 = tf.Variable(tf.random_uniform((5, 5, 32, 32)))
    b_conv2 = tf.Variable(tf.random_uniform((32,)))

    w_conv3 = tf.Variable(tf.random_uniform((5, 5, 32, 3)))
    b_conv3 = tf.Variable(tf.random_uniform((3,)))

    layer1 = tf.sigmoid(conv2d(x, w_conv1) + b_conv1)
    layer2 = tf.sigmoid(conv2d(layer1, w_conv2) + b_conv2)
    layer3 = tf.sigmoid(conv2d(layer2, w_conv3) + b_conv3)

    return layer3

y = network(x)
mse = tf.reduce_sum(tf.square(y - y_))
train_step = tf.train.AdamOptimizer(1e-4).minimize(mse)

sess = tf.InteractiveSession()
sess.run(tf.initialize_all_variables())

bsize = 16
frame = np.average(samples[:,:,:,:3], axis=0)
expected = np.repeat(np.expand_dims(frame, axis=0), bsize, axis=0)

print(expected.shape)
for i in range(n_instances / bsize):
    begin = i * bsize
    end = begin + bsize
    train_step.run(feed_dict={x: samples[begin:end,:,:,:], y_: expected})
