import sys
import os
from subprocess import Popen, PIPE
import numpy as np

def lerp(a, b, t):
    A = np.array(a)
    B = np.array(b)
    return ((1-t)*A + t*B)

def generate_image(sdl, waypoints, num_frames, dest_dir="."):
    input_data = ""
    waylen = len(waypoints)

    for x in range(0, waylen - 1):
        for t in range(0, num_frames):
            filename = os.path.join(dest_dir, "%0.5d%0.5d.npy" % (x, t))
            cam = lerp(waypoints[x], waypoints[x + 1], t/float(num_frames))
            input_data += "%s %s\n" % (filename, " ".join(str(i) for i in cam))
    print(input_data)

    pathtracer = Popen(["pathtracer", sdl], stdin=PIPE)
    pathtracer.communicate(input=input_data)

    return pathtracer.wait()

if __name__ == '__main__':
    sdl = sys.argv[1]
    dest_dir = sys.argv[2]
    num_frames = int(sys.argv[3])

    waypoints = [
        [0, 0, 10, 0, 0, 0, 0, 1, 0],
        [0, 0, 15, 0, 0, 0, 0, 1, 0],
        [0, 0, 15, 0, 0, 0, 0.75, 0.75, 0],
        [0, 0, 16, 0, 0, 0, 1, 0, 0]
    ]
    exit(generate_image(sdl, waypoints, num_frames, dest_dir))
