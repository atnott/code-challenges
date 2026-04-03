import sqlite3 as sql

def print_answer(ans):
    print(ans, '\n', '=' * 50)

with sql.connect("database.db") as connection:
    cursor = connection.cursor()
    cursor.execute("PRAGMA foreign_keys = ON;")

    cursor.execute('DROP TABLE IF EXISTS students')
    cursor.execute('DROP TABLE IF EXISTS level_of_study')
    cursor.execute('DROP TABLE IF EXISTS direction')
    cursor.execute('DROP TABLE IF EXISTS type_of_training')

    cursor.execute('''CREATE TABLE IF NOT EXISTS level_of_study (
    id_level INTEGER PRIMARY KEY UNIQUE,
    name_level VARCHAR
    );''')

    cursor.execute('''CREATE TABLE IF NOT EXISTS direction (
    id_direction INTEGER PRIMARY KEY,
    name_direction VARCHAR  
    );''')

    cursor.execute('''CREATE TABLE IF NOT EXISTS type_of_training (
    id_type INTEGER PRIMARY KEY,
    name_type VARCHAR
    );''')

    cursor.execute('''CREATE TABLE IF NOT EXISTS students (
    id_student INTEGER PRIMARY KEY UNIQUE,
    id_level INTEGER,
    id_direction INTEGER,
    id_type INTEGER,
    last_name VARCHAR,
    first_name VARCHAR,
    patronymic VARCHAR,
    avg_mark INTEGER,
    FOREIGN KEY (id_level) REFERENCES level_of_study (id_level),
    FOREIGN KEY (id_direction) REFERENCES direction (id_direction),
    FOREIGN KEY (id_type) REFERENCES type_of_training (id_type)
    );''')

    levels = [
        (1, 'Бакалавриат'),
        (2, 'Магистратура')
    ]

    directions = [
        (1, 'Прикладная информатика'),
        (2, 'Реклама и связь с общественностью'),
        (3, 'Туризм'),
        (4, 'Дизайн'),
    ]

    types = [
        (1, 'Очная'),
        (2, 'Заочная'),
        (3, 'Вечерняя')
    ]

    students_data = [
        (1, 1, 1, 1, 'Krotov', 'Anton', 'Dmitrievich', 72),
        (2, 1, 1, 3, 'Krotov', 'Igor', 'Olegovich', 85),
        (3, 2, 2, 1, 'Ivanova', 'Maria', 'Sergeevna', 94),
        (4, 1, 3, 1, 'Ivanov', 'Petr', 'Petrovich', 65),
        (5, 1, 3, 1, 'Ivanov', 'Petr', 'Petrovich', 70),
        (6, 2, 1, 2, 'Sidorov', 'Dmitry', 'Ivanovich', 88),
        (7, 1, 1, 1, 'Smirnov', 'Alexey', 'Petrovich', 95),
        (8, 1, 1, 1, 'Volkova', 'Elena', 'Igorevna', 92),
        (9, 1, 1, 1, 'Kuznetsov', 'Pavel', 'Andreevich', 88),
        (10, 1, 1, 1, 'Lebedeva', 'Anna', 'Viktorovna', 98)
    ]

    cursor.executemany('INSERT OR IGNORE INTO level_of_study VALUES(?, ?)', levels)
    cursor.executemany('INSERT OR IGNORE INTO direction VALUES(?, ?)', directions)
    cursor.executemany('INSERT OR IGNORE INTO type_of_training VALUES(?, ?)', types)
    cursor.executemany('INSERT OR IGNORE INTO students VALUES(?, ?, ?, ?, ?, ?, ?, ?)', students_data)

    '''Вывести количество всех студентов'''
    cursor.execute('SELECT COUNT(id_student) FROM students')
    print_answer(cursor.fetchone()[0])

    '''Количество студентов по направлениям'''
    cursor.execute('''SELECT direction.name_direction, COUNT(*) FROM students
    JOIN direction ON students.id_direction = direction.id_direction
    GROUP BY direction.name_direction ORDER BY COUNT(*) DESC
    ''')
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{name} - {cnt}' for name, cnt in answer))

    '''Количество студентов по формам обучения (очная, вечерняя, заочная)'''
    cursor.execute('''SELECT name_type, COUNT(*) FROM students
    JOIN type_of_training ON students.id_type = type_of_training.id_type
    GROUP BY name_type
    ''')
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{name} - {cnt}' for name, cnt in answer))

    '''Максимальный, минимальный, средний баллы студентов по направлениям'''
    cursor.execute('''SELECT name_direction, MAX(avg_mark), MIN(avg_mark), AVG(avg_mark) FROM students
    JOIN direction ON students.id_direction = direction.id_direction
    GROUP BY name_direction
    ''')
    answer = cursor.fetchall()
    print_answer('\n'.join(f'{name} - {max_} - {min_} - {round(avg_, 2)}' for name, max_, min_, avg_ in answer))

    '''Средний балл студентов по направления, уровням и формам обучения'''
    cursor.execute('''SELECT direction.name_direction, level_of_study.name_level, type_of_training.name_type, AVG(avg_mark) FROM students
    JOIN direction ON direction.id_direction = students.id_direction
    JOIN type_of_training ON type_of_training.id_type = students.id_type
    JOIN level_of_study ON level_of_study.id_level = students.id_level
    GROUP BY direction.name_direction, level_of_study.name_level, type_of_training.name_type
    ''')
    for answer in cursor.fetchall():
        print(' | '.join(str(i).rjust(35) for i in answer))
    print_answer('')

    '''Для приказа о назначении повышенной стипендии необходимо отобрать 5 студентов направления "Прикладная Информатика" очной формы обучения (отбор по среднему баллу)'''
    name = ('Прикладная информатика', 'Очная')
    cursor.execute('''SELECT last_name, first_name, avg_mark FROM students
    JOIN direction ON direction.id_direction = students.id_direction
    JOIN type_of_training ON type_of_training.id_type = students.id_type
    WHERE direction.name_direction = (?) AND type_of_training.name_type = ?
    ORDER BY avg_mark DESC
    LIMIT 5
    ''', name)
    for answer in cursor.fetchall():
        print(' | '.join(str(i).rjust(10) for i in answer))
    print_answer('')

    '''Сколько однофамильцев в данной базе?'''
    cursor.execute('SELECT last_name, COUNT(last_name) FROM students GROUP BY last_name HAVING COUNT(last_name) > 1')
    answer = cursor.fetchall()
    print_answer('\n'.join(f'Однофамильцев {name}: {cnt}' for name, cnt in answer))

    '''Есть ли среди обучающихся полные тезки (совпадают фамилии, имена, отчества)'''
    cursor.execute('''SELECT last_name, first_name, patronymic FROM students
    GROUP BY last_name, first_name, patronymic
    HAVING COUNT(*) > 1
    ''')
    answer = cursor.fetchall()
    print('Количество полных тезок: ', len(answer), '\n', '\n'.join(' '.join(line) for line in answer))