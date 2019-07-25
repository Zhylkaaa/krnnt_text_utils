import time
from krnnt_utils import create_tags5_without_guesser

inp = []
total_time = 0.0

f = open('features.txt')
lines = f.readlines()
p = open('out2.txt', 'w+')

for i in lines:
    if(i != "EOW\n"):
        inp.append(i[:-1])
    else:
        start = time.time()
        res = create_tags5_without_guesser(inp)
        end = time.time()
        total_time += (end-start)
        inp = []
        for j in res:
            p.write(j)
            p.write('\n')
f.close()
p.close()

print(total_time)
