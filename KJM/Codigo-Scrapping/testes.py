#https://selenium-python.readthedocs.io/
import requests
from selenium import webdriver
from selenium.webdriver.common.by import By
from time import sleep
from bs4 import BeautifulSoup
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import NoSuchElementException, ElementClickInterceptedException, StaleElementReferenceException
import pandas as pd
from func import corrigirUrl, totPag, pegarNome
import os

#ctrl alt i
options = Options()
navegador = webdriver.Chrome()
navegador.maximize_window()
acabou = False
with open("links.txt", 'r', encoding='utf-8-sig') as f:

        print(os.getcwd())
        urls = f.readlines()
        for url in urls:
                navegador.get(url.strip())
                site = BeautifulSoup(navegador.page_source, 'html.parser')
                navegador.execute_script("window.scrollTo(0, 600);") #desce a tela ate onde o botao é clicável
                #next = navegador.find_element(By.LINK_TEXT, 'Próxima') #procura o elemento próximo

                for i in range(totPag(navegador, url)):
                        #navegador.find_element(By.XPATH, '//*[contains(concat( " ", @class, " " ), concat( " ", "disabled", " " ))]//a')
                        site = BeautifulSoup(navegador.page_source, 'html.parser') #site atual
                        url = navegador.current_url #url atual
                        produtos = site.findAll('li', attrs={'class': 'product-list-item col-xs-12 col-lg-3 col-md-4'})
                        for produto in produtos:
                                try:
                                        descricao = produto.find('h5', attrs={'class': 'description'}).find('a').text
                                        cod_bar = produto.find('span', attrs={'class': 'barcode'}).find('a').text
                                except:
                                        continue
                                with open(f'output/{pegarNome(url)}.txt', 'a') as file:

                                        file.write(f'{descricao}\n')
                                        file.write(f'{cod_bar}\n')

                        navegador.execute_script("window.scrollTo(0, 600);")

                        try:
                                next = navegador.find_element(By.LINK_TEXT, 'Próxima')
                        except NoSuchElementException:
                                break
                        if url[-1] == '#':
                                navegador.get(corrigirUrl(url))
                        else:
                                try:
                                        next.click()
                                except ElementClickInterceptedException or StaleElementReferenceException:
                                        acabou = True
                                        break
                                sleep(1.2)
                f.close()



