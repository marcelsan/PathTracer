#!/usr/bin/python
import sys
import os
import numpy as np
import matplotlib.pyplot as plt
import imageio

axes = plt.axes()
axes.xaxis.set_visible(False)
axes.yaxis.set_visible(False)

dir = os.tempnam()
os.mkdir(dir)

def npy2png(filename, tmp=dir):
	if not filename.endswith('.npy'):
		raise Exception('you must give a .npy file')
	a = np.load(filename) # dir with .npy file
	img = np.average(a[:,:,:,:3], axis=0)
	pngfilename = os.path.join(tmp, filename.replace('.npy', '.png'))
	plt.imsave(pngfilename, np.clip(img, 0, 1))
	return pngfilename

with imageio.get_writer('movie.gif', mode='I') as writer:
    for i, filename in enumerate(npy2png(fn) for fn in sys.argv[1:]):
        print('reading i (%d) of %d' % (i, len(sys.argv) - 1))
        image = imageio.imread(filename)
        writer.append_data(image)
