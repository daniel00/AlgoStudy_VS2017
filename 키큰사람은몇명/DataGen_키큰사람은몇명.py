import random
import sys

f = open("test_input_tall.txt", "w")

f.write("13\n")

#(N,Q)
ls = [(5,3),(10,7), (100, 80), (500, 450), (1000, 980)
     , (3000, 2500), (5000, 4500), (7000, 6700), (9000, 8750), (10000, 9900)
    , (100000, 95000), (200000, 197850), (300000, 300000) ];


for N, Q in ls:
    f.write("%d" % N)
    f.write("\n");
    #Make N array
    for i in range(N):
        str = "%d " % random.randint(1, 250)
        f.write(str)
    f.write("\n")
    
    #Make Q
    f.write("%d" % Q)
    f.write("\n")
    for i in range(Q):
        a = random.randint(1, N)
        b = random.randint(a, N)
        k = random.randint(1, 250)
        str = "%d %d %d" % (a, b, k)
        f.write(str)
        f.write("\n")

f.close()        