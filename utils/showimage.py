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
plt.imshow(np.clip(img, 0, 1))
plt.savefig('img/color.png')

# Normal
img = np.average(a[:n,:,:,3:6], axis=0)
plt.imshow((np.clip(img, -1, 1) + 1)/ 2)
plt.savefig('img/normal.png')

# Distance
img = np.average(-np.clip(a[:n,:,:,6], 0, 50), axis=0)
plt.imshow(img, cmap='Greys_r')
plt.savefig('img/dist.png')

# Sec Distance
img = np.average(-np.clip(a[:n,:,:,7], 0, 50), axis=0)
plt.imshow(img, cmap='Greys_r')
plt.savefig('img/dist2.png')

# Mat rgb
img = np.average(a[:n,:,:,8:11], axis=0)
plt.imshow(img)
plt.savefig('img/matcolor.png')

# Mat ka
img = np.average(a[:n,:,:,11], axis=0)
plt.imshow(img)
plt.savefig('img/matka.png')

# Mat kd
img = np.average(a[:n,:,:,12], axis=0)
plt.imshow(img, cmap='Greys_r')
plt.savefig('img/matkd.png')

# Mat kt
img = np.average(a[:n,:,:,13], axis=0)
plt.imshow(img, cmap='Greys_r')
plt.savefig('img/matkt.png')

# Mat ks
img = np.average(a[:n,:,:,14], axis=0)
plt.imshow(img, cmap='Greys_r')
plt.savefig('img/matks.png')

# Mat n
img = np.average(np.clip(a[:n,:,:,15], 0, 50), axis=0)
plt.imshow(img, cmap='Greys_r')
plt.savefig('img/matn.png')

# Mat ir
img = np.average(np.clip(a[:n,:,:,16], 0, 50), axis=0)
plt.imshow(img, cmap='Greys_r')
plt.savefig('img/matir.png')
