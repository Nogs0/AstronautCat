count = 0
count2 = 0
all = []
with open('./todos.txt', 'r') as todos:
    for linha in todos:
        count += 1
        all.append(linha)
        if count % 2 == 0:
            if linha[0] not in '70' and linha[1:4] != '789':
                print(linha, end='')
                print(all[count -2])
                count2 += 1
todos.close()
print(count2)
print(type(linha))

