from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.common.by import By




def corrigirUrl(url):
#https://cosmos.bluesoft.com.br/marcas/nestle-392/produtos?page=9#
    if url[-1] == '#':
        final = url.split('=', 2)
        corpoUrl = final[0] + '='
        num = final[-1]
        numAtt = num.replace('#', '')
        numInt = int(numAtt)
        numInt+=1
        print(url)
        return corpoUrl + str(numInt)
    else:
        return url

def totPag(navegador, url):
            navegador.get(url.strip())
            try:
                next = navegador.find_element(By.LINK_TEXT, 'Próxima')  # procura o elemento próximo
            except NoSuchElementException:
                return 1
            num = navegador.find_elements(By.CSS_SELECTOR, 'ul > li')[-11]
            return (int(num.text))

def pegarNome(url):
    separado = url.split('/', 5)[4]
    nome = separado.split('-', -1)
    nome.pop()
    resultado = str(['-'.join(nome)]).strip('[]').strip("''")
    return resultado



