def negatius(n):
    pos = [];
    neg = [];
    for i in n:
        if i < 0:
            neg.append(i);
        else:
            pos.append(i);
    print (neg + pos);

a = [1, -2, 3, -4, -3, 5, -6];
negatius(a);
