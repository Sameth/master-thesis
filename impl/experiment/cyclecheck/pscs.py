#!/usr/bin/env python3
import math, code
import numpy as np

p = [1, 3, 8, 20, 52]

for i in range(100000):
    p.append(2*p[-1] + 4*p[-3])


c = [1, 3, 8, 20, 48, 112]
for i in range(6, 100000):
    c.append(16*p[i - 5] + 16*p[i-5] + 4*p[i - 2])

code.interact(local=locals())
