import sqlite3 as sql
from all_data.data import levels, directions, types, students_data

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
    print_answer('')

    '''Добавление новой колонки "Статус ученика"'''
    cursor.execute('''
    SELECT
        last_name,
        first_name,
        avg_mark,
        CASE
            WHEN avg_mark > 80 THEN 'A'
            WHEN avg_mark > 60 AND avg_mark <= 80 THEN 'B'
            ELSE 'C'
        END status
    FROM students;
    ''')
    for row in cursor.fetchall():
        print(*row, sep=' | '.rjust(10))
    print_answer('')

    '''Получение количества студентов на каждом направлении, балл которых больше заданного'''
    min_mark = (80, )
    cursor.execute('''
    SELECT name_direction, COUNT(*) as total_students,
    SUM(CASE WHEN students.avg_mark > ? THEN 1 ELSE 0 END) as high_achievers
    FROM students
    JOIN direction ON students.id_direction = direction.id_direction
    GROUP BY name_direction;
    ''', min_mark)
    for row in cursor.fetchall():
        print(row)
    print_answer('')

    '''Вывести список студентов, которые учатся лучше, чем в среднем по всему университету'''
    cursor.execute('''
    SELECT last_name, first_name, avg_mark
    FROM students
    WHERE avg_mark > (SELECT AVG(avg_mark) FROM students);
    ''')
    for row in cursor.fetchall():
        print(*row, sep=' | '.rjust(10))
    print_answer('')

    '''Вывод названия направлений, на которых учится больше 3 студентов'''
    cursor.execute('''
    SELECT name_direction
    FROM direction
    WHERE (SELECT COUNT(*) FROM students WHERE students.id_direction = direction.id_direction) > 3
    ''')
    print(cursor.fetchall())
    print_answer('')

    '''Вывод студентов, лучших по баллу на своем направлении'''
    cursor.execute('''
    SELECT name_direction, last_name, first_name, avg_mark
    FROM students
    JOIN direction ON students.id_direction = direction.id_direction
    WHERE students.avg_mark = (SELECT MAX(avg_mark) FROM students WHERE id_direction = direction.id_direction)
    ''')
    for row in cursor.fetchall():
        print(*row, sep=' | '.rjust(3))
    print_answer('')

    '''Вывод направлений, где средний балл учащихся больше заданного'''
    min_mark = (70, )
    cursor.execute('''
    WITH direction_avg AS (
    SELECT name_direction, AVG(avg_mark) a
    FROM direction
    JOIN students ON direction.id_direction = students.id_direction
    GROUP BY direction.name_direction
    )
    SELECT * FROM direction_avg
    WHERE direction_avg.a > ?
    ''', min_mark)
    for row in cursor.fetchall():
        print(*row, sep=' | '.rjust(3))
    print_answer('')

    '''Сравнение каждого студента со средним по его группе'''
    cursor.execute('''
    WITH dir_averages AS (
    SELECT direction.name_direction, students.id_direction, AVG(students.avg_mark) as avg_value
    FROM students
    JOIN direction ON students.id_direction = direction.id_direction
    GROUP BY students.id_direction
    )
    SELECT dir_averages.name_direction, students.last_name, students.first_name, students.avg_mark FROM students
    JOIN dir_averages ON dir_averages.id_direction = students.id_direction
    WHERE students.avg_mark > dir_averages.avg_value
    ''')
    for row in cursor.fetchall():
        print(*row, sep=' | '.rjust(3))
    print_answer('')