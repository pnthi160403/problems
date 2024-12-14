res = 1
res1 = 1

max_res = 13
max_res1 = 200

for i in range(1, max_res + 1):
    res *= i

for i in range(200 - 12 + 1, max_res1 + 1):
    res1 *= i

print((res1 / res))