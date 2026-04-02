import sqlite3 as sql

def print_answer(ans):
    print(ans, '\n', '=' * 50)

with sql.connect('schema.db') as con:
    cursor = con.cursor()

    '''ПЯТЬ ПРОСТЫХ ЗАПРОСОВ'''
    '''вывод общего количества записей в таблице orders'''
    cursor.execute('SELECT COUNT(order_code) from orders')
    print_answer(cursor.fetchall()[0][0])

    '''вывод самой большой суммы в таблице orders'''
    cursor.execute('SELECT MAX(sum) from orders')
    print_answer(cursor.fetchall()[0][0])

    '''вывод суммы всех заказов'''
    cursor.execute('SELECT SUM(sum) from orders')
    print_answer(cursor.fetchall()[0][0])

    '''вывод среднего чека среди заказов'''
    cursor.execute('SELECT AVG(sum) from orders')
    print_answer(cursor.fetchall()[0][0])

    '''вывод количества сотрудников в таблице employees'''
    cursor.execute('SELECT COUNT(employee_code) from employees')
    print_answer(cursor.fetchall()[0][0])

    '''ТРИ ЗАПРОСА С АГРЕГАЦИЕЙ'''
    '''вывод количества заказов у каждого клиента'''
    cursor.execute('''SELECT client_code, COUNT(order_code) FROM orders GROUP BY client_code''')
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{ans} - {cnt}' for ans, cnt in answer))

    '''вывод суммы продаж каждого сотрудника'''
    cursor.execute('SELECT employee_code, SUM(sum) FROM orders GROUP BY employee_code ORDER BY SUM(sum) DESC')
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{ans} - {cnt}' for ans, cnt in answer))

    '''вывод среднего чека для каждого клиента(менее переменной max_avg)'''
    max_avg = (1600, )
    cursor.execute('SELECT client_code, AVG(sum) FROM orders GROUP BY client_code HAVING AVG(sum) < ?', max_avg,)
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{id_} - {cnt}' for id_, cnt in answer))

    '''ТРИ ЗАПРОСА С ОБЪЕДИНЕНИЯМИ И УСЛОВИЯМИ'''
    '''вывод названий организаций, заказы которых еще не выполнены'''
    cursor.execute('''SELECT clients.organization, orders.sum, employees.last_name FROM clients
    JOIN orders ON clients.client_code = orders.client_code
    JOIN employees ON orders.employee_code = employees.employee_code
    WHERE completed = 0
    ''')
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{name} - {s} - {emp}' for name, s, emp in answer))

    '''вывод фамилий сотрудников, работающих по профессии name_emp, и их даты заказов'''
    name_emp = ('менеджер', )
    cursor.execute('''SELECT employees.last_name, jobs.name, date FROM jobs
    JOIN employees ON jobs.job_code = employees.job_code
    JOIN orders ON orders.employee_code = employees.employee_code
    WHERE jobs.name = ?
    ''', name_emp)
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{name} - {emp} - {date}' for name, emp, date in answer))

    '''вывод названия организации и ее суммы заказов, если сумма заказа меньше data[1] и компания - data[0]'''
    data = ('google', 1100)
    cursor.execute('''SELECT clients.organization, orders.sum FROM orders
    JOIN clients ON orders.client_code = clients.client_code
    WHERE clients.organization = ? AND orders.sum < ?
    ''', data)
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{name} - {s}' for name, s in answer))