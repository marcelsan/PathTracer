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
        print('waypoint: ', x)
        for t in range(0, num_frames):
            print('num_frames: ', num_frames)
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
    num_frames = int(sys.argv[3]) if len(sys.argv) >= 3 else 1

    waypoints = [
        [0, 0, 15, 0, 0, 0, 0, 1, 0],
        [0, 0,  2, 0, 0, 0, 0, 1, 0],
        [5, 0,  5, 2.09, -1.53, -19.0, 0, 1, 0],
        [10, 0, 5, 2.09, -1.53, -19.0, 0, 1, 0],
        [10, 5, 5, 2.09, -1.53, -19.0, 0, 1, 0],
        [10, 5, 10, 2.09, -1.53, -19.0, 0, 1, 0],
        [10, 5, 15, 2.09, -1.53, -19.0, 0, 1, 0],
        [0, 5, 20, 2.09, -1.53, -19.0, 0, 1, 0],
        [-10, 5, 25, 2.09, -1.53, -19.0, 0, 1, 0],
        [-10, 5, 30, 2.09, -1.53, -19.0, 0, 1, 0],
        [-20, 5, 35, 2.09, -1.53, -19.0, 0, 1, 0],
        [-25, 10, 35, 2.09, -1.53, -19.0, 0, 1, 0],
        [-25, 10, 20, 2.09, -1.53, -19.0, 0, 1, 0],
    ]
    exit(generate_image(sdl, waypoints, num_frames, dest_dir))
