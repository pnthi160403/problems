import sys
import math

def cnt(list_num = [], n = 0):
    lcm = 1
    for num in list_num:
        lcm = math.lcm(lcm, num)
    return int(n / lcm)

for line in sys.stdin:
    s = line.split(" ")
    n = int(s[0])
    p = int(s[1])
    q = int(s[2])
    r = int(s[3])
    ans = cnt([p, q], n) + cnt([q, r], n) + cnt([p, r], n) - 3 * cnt([p, q, r], n)
    print(ans)