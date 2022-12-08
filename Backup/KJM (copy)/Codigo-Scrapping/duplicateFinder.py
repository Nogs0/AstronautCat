import os

all_files = os.listdir('./output/')
tudo = []
for i in all_files:
    with open(f'./output/{i}', 'r') as each:
        for linha in each:
            tudo.append(linha)
for i in tudo:
    with open(f'./todos.txt', 'a') as file:
        file.write(i)