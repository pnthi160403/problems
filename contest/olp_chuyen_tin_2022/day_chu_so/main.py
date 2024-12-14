s = input()

n = len(s)

u = 0
v = 0

max_len = n
min_sum = None

for len1 in range(1, n + 1):
    for len2 in range(1, n - len1 + 1):
        len3 = n - len1 - len2
        if len3 <= 0:
            continue
        if (s[len1] == '0' and len2 >= 2) or (s[len1 + len2] == '0' and len3 >= 2):
            continue
        if max([len1, len2, len3]) > max_len:
            continue
        start = 0
        _n1 = int(s[0:start + len1])
        start += len1
        _n2 = int(s[start:start + len2])
        start += len2
        _n3 = int(s[start:start + len3])

        if min_sum == None:
            min_sum = _n1 + _n2 + _n3
        else:
            min_sum = min(min_sum, _n1 + _n2 + _n3)

print(min_sum)