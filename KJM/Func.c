#include "Header.h"

void CriaLista(Lista *l)
{
    l->inicio = NULL;
    l->fim = NULL;
}
int InsereFinal(Lista* l, Produto dado)
{
    No *aux;
    aux = (No*)malloc(sizeof(No));

    if(aux == NULL) return 0;
        aux->p = dado;
    if(l->inicio == NULL)
    {
        l->inicio = l->fim = aux;
        aux->prox = l->inicio;
        aux->ant = l->fim;
        return 1;
    }

    aux->prox = l->inicio;
    aux->ant = l->fim;
    l->fim->prox = aux;
    l->fim = aux;
    l->inicio->ant = aux;
    return 1;
}

int InsereOrdenado(Lista *l, Produto dado)
{
    No *aux;
    if(l->inicio == NULL)
        return InsereFinal(l, dado);
    aux = l->inicio;
    do
    {
        if(strcmp(aux->p.Descricao, dado.Descricao) > 0)
        {
            No *novo;
            novo = (No*)malloc(sizeof(No));
            if(novo == NULL) return 0;

            novo->p = dado;

            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
            if(strcmp(l->inicio->p.Descricao, novo->p.Descricao) > 0)
                        l->inicio = novo;
            return 1;
        }
        aux = aux->prox;
    }
    while(aux != l->inicio);
    InsereFinal(l, dado);
    return 1;
}
int Tamanho(Lista l)
{
    No *aux = NULL;
    if(l.inicio == NULL) return 0;
    int tam = 0;
    aux = l.inicio;
    do
    {
        tam++;
        aux = aux->prox;
    }
    while(aux != l.inicio);
    return tam;
}
void Mostra(Lista l)
{
    No *aux;
    if(l.inicio == NULL) printf("Estoque vazio!\n");
    else{
    aux = l.inicio;
    do
    {
        printf("%s\n", aux->p.Descricao);
        printf("%s\n", aux->p.CodigoB);
        printf("%d\n", aux->p.KJM);
        printf("%d/%d/%d\n", aux->p.Dia, aux->p.Mes, aux->p.Ano);
        printf("--------------------------------------\n");
        aux = aux->prox;
    }while(aux != l.inicio);
    }
}

void AdicionandoProduto(Lista *l)
{
    Produto aux;
    printf("Qual o tipo do produto?\n1 - ALIMENTICIO\n2-LIMPEZA\n");
    scanf("%d", &aux.Tipo);
    aux.KJM = Tamanho(*l);
    printf("Entre com a descrição do produto: ");
    scanf(" %30[^\n]", aux.Descricao);
    printf("Entre com o código de barras: ");
    scanf(" %25[^\n]", aux.CodigoB);
    printf("Entre com a data de validade do produto [dd mm aaaa]: ");
    scanf("%d %d %d", &aux.Dia, &aux.Mes, &aux.Ano);

    InsereOrdenado(l, aux);
}
