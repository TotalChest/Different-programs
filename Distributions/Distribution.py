import math
import matplotlib.pyplot as plt
import numpy as np


np.random.seed(19680801)


# Custom distribution
def generate_custom():
 	x = np.random.rand() * 0.75
 	return x if x < 0.5 else 1 - math.sqrt(3 - 4 * x) / 2


# Uniform distribution
def generate_uniform(a , b):
	return (np.random.rand()*(b - a) + a)


# Normal distribution
def generate_normal(mu, sigma):
	return np.random.normal(mu, sigma)


# Exponential distribution
def generate_exponential(b):
	return np.random.exponential(b)


# Binomial distribution
def generate_binomial(n, p):
	return np.random.binomial(n, p)


plt.hist([generate_custom() for _ in range(1000000)], bins=100)
plt.title('Custom distribution')
plt.show()

plt.hist([generate_uniform(1, 4) for _ in range(1000000)], bins=100)
plt.title('Uniform distribution')
plt.show()

plt.hist([generate_normal(0, 5) for _ in range(1000000)], bins=100)
plt.title('Normal distribution')
plt.show()

plt.hist([generate_exponential(10) for _ in range(1000000)], bins=100)
plt.title('Exponential distribution')
plt.show()

plt.hist([generate_binomial(10000, 0.6) for _ in range(1000000)], bins=100)
plt.title('Binomial distribution')
plt.show()