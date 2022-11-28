#include "../includes/Head.h"

void clearscr(void)
{
    printf("\033c");
    printf("\033[H\033[J");
    return;
}
void CriaLista(Lista *l)
{
    l->inicio = NULL;
    l->fim = NULL;
}

No Busca(Lista *l, char *cod)
{

    No *aux = l->inicio;
    No *p = NULL;

    while(aux != NULL)
    {

        if(strcmp(aux->p.CodigoB, cod) == 0)
        {
            p = aux;
            break;
        }
        aux = aux->prox;
    }
    return *p;
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
            if(strcmp(aux->p.CodigoB, dado.CodigoB) > 0)
            {
                novo = (No*)malloc(sizeof(No));
                if(novo)
                {
                    novo->p = dado;
                    novo->prox = aux;
                    novo->ant = aux->ant;
                    aux->ant->prox = novo;
                    aux->ant = novo;

                    if(strcmp(l->inicio->p.CodigoB, novo->p.CodigoB) > 0)
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
int Tamanho(Lista l) // Função que retorna o tamanho da lista, tornando possível o preenchimento automático do
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
    if(l.inicio == NULL) printf("Lista vazia!\n");
    else
    {
        aux = l.inicio;
        do
        {
            printf("%s\n", aux->p.Descricao);
            printf("%s\n", aux->p.CodigoB);
            //printf("%s\n", aux->p.Data);
            printf("%d/%d/%d\n", aux->p.Dia, aux->p.Mes, aux->p.Ano);
            printf("--------------------------------------\n");
            aux = aux->prox;
        }
        while(aux != l.inicio);
    }
}

void AdicionandoProduto(Lista *l, Lista *l2) // Função destinada a receber o produto que será adicionado, transformando-o em um Produto para a função InsereOrdenado
{
    char Fornecedor[30];
    printf("Entre com o fornecedor do produto: ");
    scanf(" %30[^\n]", Fornecedor);
    if(InserirMemoria(Fornecedor, l2, 1) == 0) return;
    printf("Você deseja adicionar quantos produtos?\n");
    int n;
    scanf("%d", &n);
    if(n <= 0)
    {
        printf("A quantidade de produtos adicionados precisa ser maior do que 0.\n");
    }
    else
    {
        for(int i =0; i<n; i++)
        {
            Produto aux;
            strcpy(aux.Fornecedor, Fornecedor);
            printf("Entre com o código de barras: ");
            scanf(" %25[^\n]", aux.CodigoB);
            if(ConfereCod(Fornecedor, &aux, l2))
            {
                /* Criar função para encontrar o codigo de barras no estoque
                Se existir, printar uma nova data */
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
            else printf("Código não encontrado\n");

        }
        clearscr();
    }
}

int Remover(Lista *l, char *dado)
{
    No *aux;

    if(l->inicio == NULL)
        return 0;

    aux = l->inicio;
    do
    {
        if (strcmp(aux->p.CodigoB, dado) == 0)
        {
            if (aux == l->inicio && aux == l->fim)   // só tem um
            {
                free(aux);   // libera memória
                l->inicio = l->fim = NULL;  // reinicializa a lista
            }

            aux->prox->ant = aux->ant;   // anterior do próximo recebe o anterior de aux
            aux->ant->prox = aux->prox;  // próximo do anterior recebe o próximo de aux

            if (aux == l->inicio) l->inicio = aux->prox;
            if (aux == l->fim) l->fim = aux->ant;
            free(aux);
            return 1;
        }
        aux = aux->prox;
    }
    while (aux != l->inicio);

    // se chegou aqui, não achou d
    return 0;
}

void RemovendoProduto(Lista *l)  // Função que recebe o produto que será removido, tornando viável sua localização e remoção
{
    char cod[30];
    int option;
    printf("\nDigite o código de barras: ");
    scanf(" %25[^\n]", cod);
    Remover(l, cod);
    clearscr();
}

int DataValida(int dia, int mes, int ano)  // Função que verifica se as datas de vencimento inseridas são válidas
{
    struct tm atual;
    atual = DataAtual();
    if(ano == atual.tm_year)
        if(mes >= atual.tm_mon && mes <=12)
            if(dia >= atual.tm_mday && dia <=30)
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

void ConferirValidade(Lista *l)
{
    clearscr();
    char est[8] = {"estoque"};
    if(InserirMemoria(est, l, 0) == 0) return;
    if(l->inicio == NULL) return;
    No *aux;
    No f;
    aux = l->inicio;
    do
    {
        if(DataValida(aux->p.Dia, aux->p.Mes, aux->p.Ano) == 0)
        {
            char opt;
            printf("%s", aux->p.Descricao);
            printf("%s", aux->p.CodigoB);
            printf("%d/%d/%d", aux->p.Dia, aux->p.Mes, aux->p.Ano);
            printf("\nEste item está vencido!\n\n");
            printf("Você deseja remover este item do estoque? [ y - n ]\n");
            scanf(" %c", &opt);
            opt = tolower(opt);
            if(opt == 'y')
            {
                Remover(l, aux->p.CodigoB);
            }
        }
        aux = aux->prox;
    }
    while(aux != l->inicio);
}

void Salvar(Lista l)
{
    char *data;
    memset(data, '\0', 11);
    if(l.inicio == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }
    FILE *estoque;
    if((estoque = fopen("./EMP/estoque.txt","a")))
    {
        No *aux;
        aux = l.inicio;
        do
        {
            fprintf(estoque, "%s", aux->p.Descricao);
            fprintf(estoque, "%s", aux->p.CodigoB);
            fprintf(estoque, "%c", '*');
            if(aux->p.Dia < 10)
                fprintf(estoque, "%c", '0');
            fprintf(estoque, "%d", aux->p.Dia);
            fprintf(estoque, "%c", '/');
            if(aux->p.Mes < 10)
                fprintf(estoque, "%c", '0');
            fprintf(estoque, "%d", aux->p.Mes);
            fprintf(estoque, "%c", '/');
            fprintf(estoque, "%d", aux->p.Ano);
            fprintf(estoque, "%c", '\n');

            aux = aux->prox;
        }
        while(aux != l.inicio);
    }
    else printf("Não foi possível abrir o arquivo!\n");

    fclose(estoque);
}

void SalvandoProdutos(Lista *l)
{
    if(l->inicio != NULL)
    {
        printf("Você gostaria de alocar estes itens no estoque?\n");
        Mostra(*l);
        printf("[y - n]\n");
        char opt;
        scanf(" %c", &opt);
        opt = tolower(opt);
        if(opt == 'y')
        {
            Salvar(*l);
            CriaLista(l);
            clearscr();
        }
    }
    else
        return;

}
int ConfereEmp(char *dado)
{
    FILE *Arquivo;
    char emp[70];
    strcat(dado, "\n");
    if((Arquivo = fopen("Empresas.txt", "r")))
    {
        while(fgets(emp, 30, Arquivo))
        {
            if(strcmp(dado, emp) == 0)
            {
                fclose(Arquivo);
                return 1;
            }
        }
    }
    fclose(Arquivo);
    printf("Empresa não existente\n");
    return 0;
}

int ConfereCod(char *dado, Produto *produto, Lista *l2)
{
    int i = 0;
    char aux[20] = {"./EMP/"};
    char codigo[70];
    while(dado[i] != '\n')
        i++;
    strncat(aux, dado, i);
    strcat(aux, ".txt");
    strcat(produto->CodigoB, "\n");
    FILE *ArquivoEmpresa;
    i = 0;
    if((ArquivoEmpresa = fopen(aux, "r")) != NULL)
    {
        while(fgets(codigo, 20, ArquivoEmpresa))
        {
            i++;
            if(strcmp(produto->CodigoB, codigo) == 0)
            {
                No a;
                a = Busca(l2, codigo);
                strcpy(produto->Descricao, a.p.Descricao);
                fclose(ArquivoEmpresa);
                return 1;
            }
        }
    }
    fclose(ArquivoEmpresa);
    printf("Codigo não encontrado na base de dados da empresa!\n");
    return 0;
}

int InserirMemoria(char *Empresa, Lista *l, int tipo)  // Função que passa todos os itens de um Fornecedor para a memória
{

    if(ConfereEmp(Empresa))
    {
        FILE *Arq;
        int i = 0;
        Produto prod;
        char aux[30] = {"./EMP/"};
        char codigo[200];
        char data[13];
        while(Empresa[i] != '\n')
            i++;
        strncat(aux, Empresa, i);
        strcat(aux, ".txt");
        if((Arq = fopen(aux, "r")) == NULL) return 0;
        if(tipo == 1)
        {
            do
            {
                fgets(codigo, 200, Arq);
                strcpy(prod.Descricao, codigo);
                memset(codigo, '\0', 200);
                fgets(codigo, 200, Arq);
                strcpy(prod.CodigoB, codigo);
                if(prod.Descricao[0] != '\0' && prod.CodigoB[0] != '\0')
                    InsereFinal(l, prod);

            }
            while(codigo[0] != '\0');
        }
        else
        {
            do
            {
                fgets(codigo, 200, Arq);
                strcpy(prod.Descricao, codigo);
                memset(codigo, '\0', 200);
                fgets(codigo, 200, Arq);
                strcpy(prod.CodigoB, codigo);
                fgets(codigo, 200, Arq);
                strcpy(prod.Data, codigo);
                PassaInteiro(&prod);
                if(prod.Descricao[0] != '\0' && prod.CodigoB[0] != '\0')
                    InsereFinal(l, prod);

            }
            while(codigo[0] != '\0');

        }
        fclose(Arq);
        return 1;
    }
    return 0;
}

void PassaInteiro(Produto *p)
{
    if(p->Data)
    {
        char auxdia[3], auxmes[3], auxano[5], a;
        int i = 1, j=0;

        while(i<3)
        {
            auxdia[j] = p->Data[i];
            i++;
            j++;
        }
        i = 4;
        j = 0;
        while(i<6)
        {
            auxmes[j] = p->Data[i];
            i++;
            j++;
        }
        i = 7;
        j = 0;
        while(i<11)
        {
            auxano[j] = p->Data[i];
            i++;
            j++;
        }

        p->Dia = atoi(auxdia);
        p->Mes = atoi(auxmes);
        p->Ano = atoi(auxano);
    }
}
