import numpy as np

n = int(input())

b = np.zeros(n*n)
a = np.zeros((n*n, n*n))

for i in range(n):
	for j, c in enumerate(input().split()):
		b[i * n + j] = int(c)

for i in range(n*n):
	a[i, i] = 1
	if (i+1)%n != 0:
		a[i, i + 1] = 1
	if (i+1)%n != 1:
		a[i, i - 1] = 1
	if i < n*n - n:
		a[i, i + n] = 1
	if i >= n:
		a[i, i - n] = 1
	if i < n*n - n and (i+1)%n != 0:
		a[i, i + n + 1] = 1
	if i < n*n - n and (i+1)%n != 1:
		a[i, i + n - 1] = 1
	if i >= n and (i+1)%n != 1:
		a[i, i - n - 1] = 1
	if i >= n and (i+1)%n != 0:
		a[i, i - n + 1] = 1	

X = np.linalg.solve(a, b) 

for i, c in enumerate(X):
	print(str(int(c)) + ('\n' if (i+1) % n == 0 else ' '), end = '')