import time

def search1d():
    inc = [0.01, 0.0001, 0.000001]
    for j in inc:
        maxim = 0.
        xtop = -1.
        nIter = 0
        t1 = time.clock()
        for i in frange1d(-1.0, 2.0, j):
            y = func1d(i)
            if y > maxim:
                maxim = y
                xtop = i
            nIter += 1
        t2 = time.clock()
        print xtop, maxim, nIter, ((t2 - t1)*1000)

search1d()
