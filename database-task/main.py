import sqlite3 as sql
import pandas as pd
from datetime import datetime

# sell_df = pd.read_excel('test.xls', sheet_name='Движение_товаров')
# product_df = pd.read_excel('test.xls', sheet_name='Товар')
# shop = pd.read_excel('test.xls', sheet_name='Магазин')
#
# req_sell = ['ID операции', 'Дата', 'ID магазина', 'Артикул', 'Количество упаковок', 'Тип операции']
# req_product = ['Артикул', 'Отдел' 'Наименование товара', 'Ед_изм', 'Количество в упаковке', 'Цена за упаковку']
# req_shop = ['ID', 'магазина', 'Район', 'Адрес']
#
# sell_df['Дата'] = pd.to_datetime(sell_df['Дата']).dt.strftime('%Y-%m-%d')
#
# conn = sql.connect('task.db')
# sell_df.to_sql('sell', conn, index=False)
# product_df.to_sql('product', conn, index=0)
# shop.to_sql('shop', conn, index=False)

conn = sql.connect('task.db')
cursor = conn.cursor()

cursor.execute('''drop table if exists answer''')
cursor.execute("""
create table answer as 
SELECT 
    data1.*, 
    data2.[Наименование товара], data2.Отдел, data2.[Цена за упаковку],
    data3.Район, data3.Адрес
FROM 
    sell data1
JOIN 
    product data2 ON data1.Артикул = data2.Артикул
JOIN 
    shop data3 ON data1.[ID магазина] = data3.[ID магазина]
""")

conn.commit()
answer = cursor.execute("""
SELECT 
    SUM(CASE WHEN [Тип операции] == 'Поступление' THEN [Количество упаковок, шт] ELSE 0 END) -
    SUM(CASE WHEN [Тип операции] == 'Продажа' THEN [Количество упаковок, шт] ELSE 0 END)
FROM answer
WHERE [Наименование товара] == 'Суфле в шоколаде' AND Район == 'Промышленный' AND Дата BETWEEN '2021-08-02' AND '2021-08-14'
""").fetchone()[0]

print(answer)
conn.close()