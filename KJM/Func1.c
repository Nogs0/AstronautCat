#include "Header1.h"

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

    if(l->inicio == NULL)
    {
        aux->p = dado;
        l->inicio = l->fim = aux;
        aux->prox = l->inicio;
        aux->ant = l->fim;
        return 1;
    }
    aux->p = dado;
    aux->ant = l->fim;
    l->fim->prox = aux;
    aux->prox = l->inicio;
    l->inicio->ant = aux;
    l->fim = aux;
    return 1;
}

int InsereOrdenado(Lista *l, Produto dado)
{
    No *aux, *novo;
    if(l->inicio == NULL)
        return InsereFinal(l, dado);
    else
    {
        aux = l->inicio;
        do
        {
            if(strcmp(aux->p.Descricao, dado.Descricao) > 0)
            {
                novo = (No*)malloc(sizeof(No));
                if(novo)
                {
                    novo->p = dado;
                    novo->prox = aux;
                    novo->ant = aux->ant;
                    aux->ant->prox = novo;
                    aux->ant = novo;

                    if(strcmp(l->inicio->p.Descricao, aux->p.Descricao) > 0)
                        l->inicio = novo;
                    return 1;
                }
                else return 0;
            }
            aux = aux->prox;
        }
        while(aux != l->inicio);
        InsereFinal(l, dado);
    }
    return 1;
}
int Tamanho(Lista l) // Função que retorna o tamanho da lista, tornando possível o preenchimento automático do código KJM
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
    else
    {
        aux = l.inicio;
        do
        {
            printf("%s\n", aux->p.Descricao);
            printf("%s\n", aux->p.CodigoB);
            printf("%d\n", aux->p.KJM);
            printf("%d/%d/%d\n", aux->p.Dia, aux->p.Mes, aux->p.Ano);
            printf("--------------------------------------\n");
            aux = aux->prox;
        }
        while(aux != l.inicio);
    }
}

void AdicionandoProduto(Lista *l) // Função destinada a receber o produto que será adicionado, transformando-o em um Produto para a função InsereOrdenado
{
    Produto aux;
    printf("Qual o tipo do produto?\n1 - ALIMENTICIO\n2 - LIMPEZA\n");
    scanf("%d", &aux.Tipo);
    aux.KJM = Tamanho(*l);
    printf("Entre com a descrição do produto: ");
    scanf(" %30[^\n]", aux.Descricao);
    printf("Entre com o código de barras: ");
    scanf(" %25[^\n]", aux.CodigoB);
    printf("Entre com a data de validade do produto [dd mm aaaa]: ");
    scanf("%d %d %d", &aux.Dia, &aux.Mes, &aux.Ano);

    while(DataValida(aux.Dia, aux.Mes, aux.Ano) == 0)
    {
        printf("\nEntre com uma data real e possível!\n");
        printf("Entre com a data de validade do produto [dd mm aaaa]: ");
        scanf("%d %d %d", &aux.Dia, &aux.Mes, &aux.Ano);
    }
    InsereOrdenado(l, aux);
}

int Remover(Lista *l,Produto dado)
{
    No *aux = NULL;

    if(l->inicio == NULL) return 0;

    aux = l->inicio;

    do
    {
        if(aux->p.Descricao == dado.Descricao || aux->p.CodigoB == dado.CodigoB || aux->p.KJM == dado.KJM)
        {
            if(aux == l->inicio && aux == l->fim)
            {
                l->inicio = l->fim = NULL;
            }
            aux->prox->ant = aux->ant;
            aux->ant->prox = aux->prox;

            if(aux == l->inicio)
                l->inicio = aux->prox;
            if(aux == l->fim)
                l->fim = aux->ant;
            free(aux);
            return 1;
        }
        aux = aux->prox;
    }
    while(aux != l->inicio);
    return 0;
}

void RemovendoProduto(Lista *l)  // Função que recebe o produto que será removido, tornando viável sua localização e remoção
{

    Produto aux;
    int option;
    printf("\nDe qual maneira gostaria de localizar o produto?");
    printf("\n1 - Descricao\n2 - Codigo de Barras\n3 - Codigo KJM\n");
    scanf("%d", &option);
    switch(option)
    {
    case 1:
        printf("\nDigite a descricao do Produto: ");
        scanf(" %30[^\n]", aux.Descricao);
        Remover(l, aux);
        break;
    case 2:
        printf("\nDigite o codigo de barras: ");
        scanf(" %25[^\n]", aux.CodigoB);
        Remover(l, aux);
        break;
    case 3:
        printf("\nDigite o KJM: ");
        scanf("%d", &aux.KJM);
        Remover(l, aux);
        break;
    default:
        printf("\nDigite uma opção válida!\n");
    }
}

int DataValida(int dia, int mes, int ano)  // Função que verifica se as datas de vencimento inseridas são válidas
{
    struct tm atual;
    atual = DataAtual();
    if(ano == atual.tm_year)
        if(mes >= atual.tm_mon)
            if(dia >= atual.tm_mday)
                return 1;
    if(ano > atual.tm_year)
        return 1;

    return 0;
}

struct tm DataAtual()  // Função que verifica o ano atual
{
    struct tm aux;
    time_t seconds;
    time(&seconds);
    aux = *localtime(&seconds);
    aux.tm_year += 1900;
    aux.tm_mon += 1;
    return aux;
}

void ConferirValidade(Lista l){
    No *aux;
    Lista fila;

    if(l.inicio == NULL)    printf("O estoque está vazio!\n");
    else{
        aux = l.inicio;
        do{
            if(DataValida(aux->p.Dia,aux->p.Mes, aux->p.Ano) == 0)
                InsereFinal( &fila, aux->p);
            aux = aux->prox;
        }while(aux != l.inicio);
    }


}
