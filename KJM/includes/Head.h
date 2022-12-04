#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
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
void AdicionandoProduto(Lista *, Lista *);
int  Remover(Lista*, char *);
void RemovendoProduto(Lista*);
int  DataValida(int, int, int);
struct tm DataAtual(void);
void ConferirValidade(Lista*);
void Salvar(Lista);
void SalvandoProdutos(Lista*);
int ConfereEmp(char*);
int ConfereCod(char*, Produto*, Lista *);
int InserirMemoria(char *Empresa, Lista *l, int tipo);
void PassaInteiro(Produto*);
void ConsultarEstoque(Lista);
#endif // HEAD_H_INCLUDED
