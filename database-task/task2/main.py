import sqlite3 as sql

with sql.connect('schema.db') as conn:
    cursor = conn.cursor()
    cursor.execute('PRAGMA foreign_keys = ON')

    cursor.execute('DROP TABLE IF EXISTS orders')
    cursor.execute('DROP TABLE IF EXISTS employees')
    cursor.execute('DROP TABLE IF EXISTS jobs')
    cursor.execute('DROP TABLE IF EXISTS clients')

    cursor.execute('''
    CREATE TABLE IF NOT EXISTS jobs (
    job_code INTEGER PRIMARY KEY UNIQUE NOT NULL,
    name TEXT NOT NULL
    );''')
    job_name = [
        ('1', 'менеджер', ),
        ('2', 'разработчик', ),
        ('3', 'аналитик', ),
        ('4', 'дизайнер', )
    ]
    cursor.executemany('INSERT INTO jobs VALUES (?, ?)', job_name)

    cursor.execute('''
    CREATE TABLE IF NOT EXISTS employees (
    employee_code INTEGER PRIMARY KEY UNIQUE NOT NULL,
    last_name TEXT NOT NULL,
    first_name TEXT NOT NULL,
    number TEXT NOT NULL,
    job_code INTEGER NOT NULL,
    FOREIGN KEY (job_code) REFERENCES jobs (job_code)
    );''')
    employee_name = [
        ('2', 'Кротов', 'Антон', '+79642708441', '1', ),
        ('4', 'Молодчиков', 'Денис', '+83838383383', '2', ),
        ('3', 'Красный', 'ОЛЕГ', '-29292929299', '3', ),
        ('1', 'Юла', 'Юлия', '97193719739', '4', )
    ]
    cursor.executemany('INSERT INTO employees VALUES (?, ?, ?, ?, ?)', employee_name)

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS clients (
        client_code INTEGER PRIMARY KEY UNIQUE NOT NULL,
        organization TEXT NOT NULL,
        number TEXT NOT NULL
        );''')
    clients = [
        ('1', 'yandex', '88005353535'),
        ('2', 'google', '11122233345'),
        ('3', 'alfa bank', '91919191919'),
        ('4', 'tinkoff', '100-200-300')
    ]
    cursor.executemany('INSERT INTO clients VALUES (?, ?, ?)', clients)

    cursor.execute('''
    CREATE TABLE IF NOT EXISTS orders (
    order_code INTEGER PRIMARY KEY UNIQUE NOT NULL,
    client_code INTEGER NOT NULL,
    employee_code INTEGER NOT NULL,
    sum INTEGER NOT NULL,
    date TEXT,
    completed BOOLEAN NOT NULL,
    FOREIGN KEY (client_code) REFERENCES clients (client_code),
    FOREIGN KEY (employee_code) REFERENCES employees (employee_code)
    );''')
    orders = [
        ('2', '2', '2', 1000, '11:11', 1),
        ('3', '2', '1', 888, '14:12', 0),
        ('5', '4', '3', 2020, '', 0),
        ('4', '3', '4', 38203, '17:00', 0),
        ('1', '1', '1', 777, '11:01', 1),
    ]
    cursor.executemany('INSERT INTO orders VALUES (?, ?, ?, ?, ?, ?)', orders)

    '''ТРИ ПРОСТЫХ ЗАПРОСА'''
    '''вывод всех телефонных номеров из таблицы clients'''
    cursor.execute('SELECT organization, number FROM clients')
    answers = '\n'.join(f'{i[0]} - {i[1]}' for i in cursor.fetchall())
    print(answers, '\n', '=' * 50)

    '''вывод всех заказов из таблицы orders, которые еще не выполнены'''
    cursor.execute('SELECT order_code, sum FROM orders WHERE completed == 0')
    answers = '\n'.join(f'{i[0]} - {i[1]}' for i in cursor.fetchall())
    print(answers, '\n', '=' * 50)

    '''вывод всех отсортированных по фамилии сотрудников из таблицы employees'''
    cursor.execute('SELECT last_name, first_name FROM employees ORDER BY last_name')
    answer = '\n'.join(f'{i[0]} {i[1]}' for i in cursor.fetchall())
    print(answer, '\n', '=' * 50)

    '''ТРИ ЗАПРОСА С ПАРАМЕТРОМ'''
    '''вывод заказов, сумма которых больше переменной min_sum'''
    min_sum = (2000, )
    cursor.execute('SELECT order_code, sum FROM orders WHERE sum > ?', min_sum)
    answer = '\n'.join(f'{i[0]} {i[1]}' for i in cursor.fetchall())
    print(answer, '\n', '=' * 50)

    '''вывод телефона компании, заданной поиском'''
    search_name = ('google', )
    cursor.execute('SELECT number FROM clients WHERE organization LIKE ?', search_name)
    answer = '\n'.join(f'{i[0]}' for i in cursor.fetchall())
    print(answer, '\n', '=' * 50)

    '''вывод всех сотрудников, код должности которых соответствует переменной label_job_code'''
    label_job_code = (4, )
    cursor.execute('SELECT last_name, first_name FROM employees WHERE job_code LIKE ?', label_job_code)
    answer = '\n'.join(f'{i[0]} {i[1]}' for i in cursor.fetchall())
    print(answer, '\n', '=' * 50)

    '''ТРИ ЗАПРОСА С ГРУППИРОВКОЙ И АГРЕГАЦИЕЙ'''
    '''вывод количества сотрудников на каждой должности'''
    cursor.execute('''SELECT jobs.name, COUNT(employees.job_code) FROM jobs
    JOIN employees ON jobs.job_code == employees.job_code
    GROUP BY jobs.name''')
    answer = '\n'.join(f'{i[0]} {i[1]}' for i in cursor.fetchall())
    print(answers, '\n', '=' * 50)

    '''вывод общей суммы заказа для каждого клиента'''
    cursor.execute('''SELECT clients.client_code, SUM(orders.sum) FROM orders
    JOIN clients ON orders.client_code == clients.client_code
    GROUP BY orders.client_code''')
    answers = '\n'.join(f'{i[0]} - {i[1]}' for i in cursor.fetchall())
    print(answers, '\n', '=' * 50)

    '''вывод средней стоимости выполненных и невыполненных заказов для каждого клиента'''
    cursor.execute('''SELECT clients.organization, AVG(sum) FROM orders
    JOIN clients ON orders.client_code = clients.client_code
    GROUP BY clients.organization''')
    answers = '\n'.join(f'{i[0]} - {i[1]}' for i in cursor.fetchall())
    print(answers, '\n', '=' * 50)

    '''создание отчета на основе базы данных'''
    cursor.execute('''SELECT e.last_name, e.first_name, j.name, COUNT(o.order_code), SUM(o.sum) FROM jobs j
    JOIN employees  e ON e.job_code == j.job_code
    JOIN orders o ON o.employee_code == e.employee_code
    GROUP BY e.last_name ORDER BY SUM(o.sum) DESC
    ''')
    for row in cursor.fetchall():
        print(row)



