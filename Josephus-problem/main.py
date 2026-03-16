import matplotlib.pyplot as plt
data = [list(map(int, s.split())) for s in open('result.txt', 'r').readlines()]
x, y = [x for x, y in data], [y / 1000 for x, y in data]

plt.figure(figsize=(8, 6))
plt.plot(x, y)

plt.ticklabel_format(style='plain', axis='x')
plt.xlabel('Количество элементов')
plt.ylabel('Время выполнения (сек)')
plt.title('Задача Иосифа Флавия')

plt.show()












