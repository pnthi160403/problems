s = input().split()
k = int(s[0])
n = int(s[1])
i = int(s[2])
j = int(s[3])
s = int(s[4])

matrixs = []

for ii in range(0, k):
    matrix = []
    for jj in range(0, n):
        nums = input().split()
        for kk in range(0, n):
            nums[kk] = int(nums[kk])
        matrix.append(nums)
    matrixs.append(matrix)

def mul_matrix(a, b):
    res = [[0] * n] * n
    for jj in range(0, n):
        for kk in range(0, n):
            res[i][jj] += a[i][kk] * b[kk][jj] % s
            res[i][jj] %= s
    return res

res = matrixs[0]
for ii in range(0, n):
    for jj in range(0, n):
        res[ii][jj] %= s

i -= 1
j -= 1
for ii in range(1, k):
    res = mul_matrix(res, matrixs[ii])

print(res[i][j])