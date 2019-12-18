#Печать всевозможных перестановок символов строки

#Факториал
def f(n):
    c = 1
    for i in range(n):
        c *= i + 1
    return c


#Печать непутого n-ого символа
def print_num(string, mas, n):
    c = -1
    for i in range(len(string)):
        if mas[i]:
            c += 1
        if c == n:
            print(string[i], end = '')
            mas[i] = 0
            return mas

    
#Печать всех перестановок
def permutations(string):
    n = len(string)
    string = sorted(string)
    for i in range(f(n)):
        print(str(i+1)+'\t', end = '')
        mas = [1 for t in range(n)]
        k = i
        for j in range(n):
            mas = print_num(string, mas, k // f(n - j - 1))
            k = k % f(n - j - 1)
        print()


permutations(str(input('Введите символы перестановки: ')))
