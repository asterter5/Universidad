import time

def search2d():
    inc = [0.01]
    for x in inc:
        maxim = 0.
        top = (-6.0, -6.0)
        nIter = 0
        t1 = time.clock()
        for i in frange2d(-6.0, 6.0, x):
            for j in frange2d(-6.0, 6.0, x):
                y = func2d(i, j)
                if y > maxim:
                    maxim = y
                    top = i, j
                nIter += 1
        t2 = time.clock()
        print top, maxim, nIter, ((t2 - t1)*1000)

search2d()
