def get_data(name_file: str) -> list[tuple]:
    array = list()
    with open(name_file, encoding='utf-8') as file:
        for line in file.readlines():
            line = line.split(',')
            temp = tuple()
            for el in line:
                try:
                    temp += (int(el),)
                except:
                    temp += (el.strip(),)
            array += [temp]
    return array

levels = get_data(name_file="all_data/levels.txt")
directions = get_data(name_file="all_data/directions.txt")
types = get_data(name_file="all_data/types.txt")
students_data = get_data(name_file="all_data/students_data.txt")