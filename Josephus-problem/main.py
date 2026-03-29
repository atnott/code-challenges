import matplotlib.pyplot as plt
import pandas as pd
import math

def func(a, x, b):
    return a * x + b

data = [list(map(int, s.split())) for s in open('result.txt', 'r').readlines()]
df = pd.DataFrame([(el[0], el[1] / 1000, el[2]) for el in data], columns=['n', 'seconds', 'result'])
df.to_csv('answer.csv', index=False)
x, y = [x for x, y, z in data], [y / 1000 for x, y, z in data]

'''данные для n * log(n)'''
scale_nlogn = y[-1] / (x[-1] * math.log2(x[-1]))
y_nlogn = [scale_nlogn * (val * math.log2(val)) if val > 0 else 0 for val in x]


'''данные для метода наименьших квадратов'''
z = [val * math.log2(val) if val > 1 else 0 for val in x]
N = len(x)
sum_zi_yi = sum(zi * yi for zi, yi in zip(z, y))
sum_zi, sum_yi = sum(z), sum(y)
sum_zi_2 = sum(zi ** 2 for zi in z)
a_fit = (N * sum_zi_yi - sum_zi * sum_yi) / (N * sum_zi_2 - sum_zi ** 2)
b_fit = (sum_yi - a_fit * sum_zi) / N
y_mnk = [a_fit * zi + b_fit for zi in z]

plt.figure(figsize=(10, 6))
plt.plot(x, y, label='Реальные данные', markersize=4)
plt.plot(x, y_nlogn, label=f'$O(n * log(n))$', linestyle='-', color='red')
plt.plot(x, y_mnk, color='green', label='MНK')

plt.ticklabel_format(style='plain', axis='x')
plt.xlabel('Количество элементов (n)')
plt.ylabel('Время выполнения (сек)')
plt.title('Задача Иосифа Флавия')
plt.legend()
plt.grid(True, linestyle=':', alpha=0.6)

plt.savefig('josephus_analysis.png', dpi=300, bbox_inches='tight')
plt.show()