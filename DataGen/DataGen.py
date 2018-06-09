import random
import sys

f = open("test_input.txt", "w")


ls = [(5,3),(7,3),(10,5),(25,7),(30,7),
      (50,17),(100,37),(500,53),(700,357),(1000,567),
      (2000,1111),(5000,2567),(10000,5035),(50000,25983),(100000,92453)]

f.write("15\n")

for arrsize, subarrsize in ls:
    str = "%d %d\n" % (arrsize, subarrsize)
    f.write(str)
    for i in range(arrsize):
        str = "%d " % random.randint(1, arrsize)
        f.write(str)

    f.write("\n")

f.close()        