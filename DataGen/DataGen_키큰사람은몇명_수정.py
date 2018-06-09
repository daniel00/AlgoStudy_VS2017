import random
import sys

f = open("test_input_tall_8.txt", "w")
f.write("13\n")

max_n = max_q = 300000
max_a = max_b = max_k = 1000000000

#(N,Q)
ls = [(5,3),(7,4), (10, 8), (30, 10), (50, 35)
     , (150, 100), (500, 80), (800, 50), (1000, 60), (1000, 500)
    , (10000, 100), (20000, 150), (300000,300000) ];


for N, Q in ls:
    f.write("%d" % N)
    f.write("\n");
    #Make N array
    for i in range(N):
        str = "%d " % random.randint(1,max_k)
        f.write(str)
    f.write("\n")
    
    #Make Q
    f.write("%d" % Q)
    f.write("\n")
    for i in range(Q):
        a = random.randint(1, max_a)
        b = random.randint(a, max_b)
        k = random.randint(1, max_k)
        str = "%d %d %d" % (a, b, k)
        f.write(str)
        f.write("\n")

f.close()        