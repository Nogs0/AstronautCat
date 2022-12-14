#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct{
    char Descricao[200];
    char CodigoB[200];
    char Fornecedor[50];
    int Dia;
    int Mes;
    int Ano;
    char Data[13];
    int Validade;
}Produto;

typedef struct no{
    struct no *ant;
    Produto p;
    struct no *prox;
}No;

typedef struct{
    No *inicio;
    No *fim;
}Lista;


void clearscr(void);
void CriaLista(Lista *);
int  InsereFinal(Lista *, Produto);
int  InsereOrdenado(Lista *, Produto);
int  Tamanho(Lista);
void Mostra(Lista);
//void AdicionandoProduto(Lista *, Lista *);
int Remover(Lista*, char *);
//void RemovendoProduto(Lista*);
int DataValida(Produto *prod);
struct tm DataAtual(void);
void ConferirValidade(WINDOW*, Lista* );
void Salvar(Lista, char[2]);
void SalvandoProdutos(Lista*);
int ConfereEmp(char*);
int ConfereCod(char*, Produto*, Lista *);
int InserirMemoria(char *Empresa, Lista *l, int tipo);
void PassaInteiro(Produto*);
int RemoverEstoque(Lista *);

void MostrarOPT(WINDOW *, int , int , char[][100]);
int preencherJanelaOPT(WINDOW *);
void RemovendoProduto(Lista*, WINDOW *);
void MostraNCURSES(WINDOW *win, Lista *l, char *);
void AdicionandoProduto(Lista *l, Lista *l2, WINDOW* win, char cod[13], char data[11], char empresa[30]);
void DigitandoData(WINDOW *, char[11]);
void capturandoTeclado(WINDOW*, char *, int, int,int);
void DigitandoCodigo(WINDOW*, char[14]);
void MostrarEmpresas(WINDOW*, int, char[][30],int,int);
void CriarVetorEmpresas(WINDOW *, char [][30]);
int PreencherJanelaEmpresas(Lista *listaAlocacao, WINDOW* win2, char *empresaAtual, char empresas[][30], WINDOW* win, int COLUNAS, int LINHAS);
void PreencherJanelaEntrada(WINDOW *, char *);
WINDOW *DesenharJanelaOPT(int, int);
WINDOW *DesenharJanelaEmpresas(int, int);
WINDOW *DesenharJanelaEntrada(int, int );


#endif // HEADER_H_INCLUDED
