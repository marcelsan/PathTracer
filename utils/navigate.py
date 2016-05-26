import sys
import os
from subprocess import Popen, PIPE
import numpy as np


def generate_image(sdl, waypoints, dest_dir="."):
    input_data = ""
    for i, cam in enumerate(waypoints):
        filename = os.path.join(dest_dir, "%0.5d.npy" % i)
        input_data += "%s %s\n" % (filename, " ".join(str(i) for i in cam))
    print(input_data)

    pathtracer = Popen(["pathtracer", sdl], stdin=PIPE)
    pathtracer.communicate(input=input_data)

    return pathtracer.wait()

if __name__ == '__main__':
    sdl = sys.argv[1]
    dest_dir = sys.argv[2]
    waypoints = [
        [0, 0, 10, 0, 0, 0, 0, 1, 0],
        [0, 0, 15, 0, 0, 0, 0, 1, 0],
        [0, 0, 15, 0, 0, 0, 0.75, 0.75, 0],
        [0, 0, 16, 0, 0, 0, 1, 0, 0]
    ]
    exit(generate_image(sdl, waypoints, dest_dir))