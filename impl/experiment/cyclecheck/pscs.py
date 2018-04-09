#!/usr/bin/env python3
import math, code
import numpy as np

p = [1, 3, 8, 20, 52]

for i in range(100000):
    p.append(2*p[-1] + 4*p[-3])


c = [1, 3, 8, 20, 48, 112]
for i in range(6, 100000):
    c.append(16*p[i - 5] + 16*p[i-5] + 4*p[i - 2])

ppp = [1, 2, 3, 4, 6]

for i in range(100000):
    ppp.append(ppp[-1] + ppp[-3])

cpp = [1, 2, 3, 4, 5, 6]

for i in range(6, 100000):
    cpp.append(2*ppp[i-5] +ppp[i-2])

matica = np.array([[0, 0, 4], [1, 0, 0], [0, 1, 2]])
vlastne_cisla = np.linalg.eig(matica)[0]
najvacsie = np.absolute(vlastne_cisla [2])

code.interact(local=locals())
