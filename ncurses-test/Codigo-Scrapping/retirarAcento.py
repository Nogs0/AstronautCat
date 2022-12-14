import os
import unidecode

all_files = os.listdir('./output/')
tudo = []
for i in all_files:
    with open(f'./output/{i}', 'r', encoding='utf-8-sig') as empresaAtual:
        for produto in empresaAtual:
            f = i.split('.', 2)
            g = f[0].upper() + '.' + f[1]
            with open(f'./outputUnidecode/{g}', 'a', encoding='utf-8-sig') as new:
                 new.write(unidecode.unidecode(produto))




