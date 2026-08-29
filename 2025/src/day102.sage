#!/usr/bin/env sage

def read_arr(s):
    return list(map(int, s[1:-1].split(',')))

res = 0

while True:
    arr = None
    try:
        arr = input().split(' ')
    except:
        break

    S = list(map(read_arr, arr[1:-1]))
    R = read_arr(arr[-1])

    p = MixedIntegerLinearProgram()
    v = p.new_variable(integer=True, nonnegative=True)
    x = [v['x%d' % i] for i in range(len(S))]
    p.set_objective(sum([-xi for xi in x]))
    for i in range(len(R)):
        p.add_constraint(sum([(1 if i in S[j] else 0) * x[j] for j in range(len(S))]) == R[i])

    res += p.solve()

print(-res)
