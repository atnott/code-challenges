import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data = [list(map(int, s.split())) for s in open('result.txt', 'r').readlines()]
df = pd.DataFrame([(el[0], el[1] / 1000, el[2]) for el in data], columns=['n', 'seconds', 'result'])
df.to_csv('answer.csv', index=False)
x, y = [x for x, y, z in data], [y / 1000 for x, y, z in data]

'''МНК для квадратичной модели: y = a * (n^2) + b'''
z = [val ** 2 for val in x]
N = len(x)

sum_zi = sum(z)
sum_yi = sum(y)
sum_zi_yi = sum(zi * yi for zi, yi in zip(z, y))
sum_zi_2 = sum(zi ** 2 for zi in z)

a_fit = (N * sum_zi_yi - sum_zi * sum_yi) / (N * sum_zi_2 - sum_zi ** 2)
b_fit = (sum_yi - a_fit * sum_zi) / N
y_mnk = [a_fit * zi + b_fit for zi in z]

'''Данные для прогноза'''
x_forecast = np.linspace(max(x), 3_000_000, 500)
y_forecast = [a_fit * (val**2) + b_fit for val in x_forecast]

plt.figure(figsize=(10, 6))
plt.plot(x, y, label='Реальные данные', color='blue', linewidth=2)
plt.plot(x, y_mnk, label='МНК ($O(n^2)$)', color='green', linestyle='--', linewidth=5)
plt.plot(x_forecast, y_forecast, label='Прогнозируемые данные', color='red', linewidth=2, linestyle='--')

plt.xlabel('Количество элементов (n)')
plt.ylabel('Время выполнения (сек)')
plt.title('Анализ сложности: Квадратичная модель')
plt.legend()
plt.grid(True, linestyle=':', alpha=0.6)
plt.show()
