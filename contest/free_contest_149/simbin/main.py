def f(l, r):
    print("l = ", l)
    print("r = ", r)
    print()
    if l == r:
        return [1]
    arr = [r - l + 1]
    mid = (l + r) // 2
    arr += f(l, mid)
    arr += f(mid + 1, r)
    print(f"l = {l} and r = {r}")
    print(arr)
    print("len arr = ", len(arr))
    print()
    return arr

l = int(input())
r = int(input())

print(f(l, r))