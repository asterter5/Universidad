def frange2d(start, end, inc):
    while start<end:
        yield start
        start += inc

for i in frange2d(1, 2, 0.1):
    for j in frange2d(1, 2, 0.1):
        print i, j
