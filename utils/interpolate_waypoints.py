import sys
import os
import numpy as np


def lerp(a, b, t):
    return ((1 - t) * a + t * b)


def interpolate_waypoints(n, waypoints):
    w0 = next(waypoints)
    for w1 in waypoints:
        for t in range(0, n):
            yield lerp(w0, w1, t / float(n))
        w0 = w1
    yield w0


def read_waypoints(input):
    n = int(input.readline())
    def gen():
        for _ in range(n):
            yield np.array([float(x) for x in input.readline().split(',')])
    return n, gen()


def write_waypoints(n, waypoints, output):
    output.write(str(n))
    output.write('\n')
    for p in waypoints:
        output.write(','.join(str(n) for n in p))
        output.write('\n')


if __name__ == '__main__':
    n = int(sys.argv[1])
    infile = open(sys.argv[2]) if len(sys.argv) > 2 else sys.stdin
    outfile = open(sys.argv[3], 'w') if len(sys.argv) > 3 else sys.stdout

    nw, waypoints = read_waypoints(infile)
    interpolated = interpolate_waypoints(n, waypoints)
    write_waypoints(n * nw, interpolated, outfile)
