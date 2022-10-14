#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct{
    char Descricao[30];
    char CodigoB[30];
    int KJM;
    int Tipo;
    int Dia;
    int Mes;
    int Ano;
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

void CriaLista(Lista *);
int InsereFinal(Lista *, Produto);
int InsereOrdenado(Lista *, Produto);
int Tamanho(Lista);
void Mostra(Lista);
void AdicionandoProduto(Lista *);
int Remover(Lista*, Produto);
void RemovendoProduto(Lista*);
int DataValida(int, int, int);
struct tm DataAtual();
#endif // HEADER_H_INCLUDED
