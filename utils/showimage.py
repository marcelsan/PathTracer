#!/usr/bin/python
import sys
import numpy as np
import matplotlib.pyplot as plt

a = np.load(sys.argv[1]) # .npy file
n = int(sys.argv[2]) if len(sys.argv) >= 3 else -1
axes = plt.axes()
axes.xaxis.set_visible(False)
axes.yaxis.set_visible(False)

# Color
img = np.average(a[:n,:,:,:3], axis=0)
plt.imsave('img/01-color.png', np.clip(img, 0, 1))

# Normal
img = np.average(a[:n,:,:,3:6], axis=0)
plt.imsave('img/02-normal.png', (np.clip(img, -1, 1) + 1)/ 2)

# Distance
img = np.average(-np.clip(a[:n,:,:,6], 0, 50), axis=0)
plt.imsave('img/03-dist.png', img, cmap='Greys_r')

# Sec Distance
img = np.average(-np.clip(a[:n,:,:,7], 0, 50), axis=0)
plt.imsave('img/04-dist2.png', img, cmap='Greys_r')

# Mat rgb
img = np.average(a[:n,:,:,8:11], axis=0)
plt.imsave('img/05-matcolor.png', img)

# Mat ka
img = np.average(a[:n,:,:,11], axis=0)
plt.imsave('img/06-matka.png', img, cmap='Greys_r')

# Mat kd
img = np.average(a[:n,:,:,12], axis=0)
plt.imsave('img/07-matkd.png', img, cmap='Greys_r')

# Mat kt
img = np.average(a[:n,:,:,13], axis=0)
plt.imsave('img/08-matkt.png', img, cmap='Greys_r')

# Mat ks
img = np.average(a[:n,:,:,14], axis=0)
plt.imsave('img/09-matks.png', img, cmap='Greys_r')

# Mat n
img = np.average(np.clip(a[:n,:,:,15], 0, 50), axis=0)
plt.imsave('img/10-matn.png', img, cmap='Greys_r')

# Mat ir
img = np.average(np.clip(a[:n,:,:,16], 0, 50), axis=0)
plt.imsave('img/11-matir.png', img, cmap='Greys_r')
