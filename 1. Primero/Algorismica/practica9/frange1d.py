def frange1d(start, end, inc):
    while start<end:
        yield start
        start += inc

for i in frange1d(1, 2, 0.01):
    print i
