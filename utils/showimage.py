#!/usr/bin/python
import sys
import numpy as np
import matplotlib.pyplot as plt

a = np.load(sys.argv[1])
img = np.average(a[:,:,:,:3], axis=0)

plt.imshow(img)
plt.show()