#include "../includes/HeaderGraphic.h"

void clearscr(void) // Função fornecida pelo claudinho para limpar a tela
{
    printf("\033c");
    printf("\033[H\033[J");
    return;
}
void CriaLista(Lista *l) // Função que cria lista apontando seus dois ponteiros de início e fim para nulo NECESSÁRIA TODA VEZ QUE INICIAR UMA NOVA LISTA
{
    l->inicio = NULL;
    l->fim = NULL;
}

No Busca(Lista *l, char *cod) // Função utilizada para buscar um código de barras na lista em questão
{

    No *aux = l->inicio;
    No *p = NULL; // ponteiro P do tipo nó, utilizado para retornar o nó referente ao código de barras mencionado

    do // Do - While usado para percorrer a lista
    {
        if(strcmp(aux->p.CodigoB, cod) == 0)
        {
            p = aux;
            break;
        }
        aux = aux->prox;
    } while(aux != l->inicio);
    return *p;
}

int InsereFinal(Lista* l, Produto dado) // Função que insere um produto ao final da lista
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

int InsereOrdenado(Lista *l, Produto dado) // Funçã que insere ordenado na lista, ordem de código de barras
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
        InsereFinal(l, dado); // chama a insere final, caso o dado cujo queira inserir seja o maior de todos
    }
    return 1;
}
int Tamanho(Lista l) // Função que retorna o tamanho da lista
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
void MostraNCURSES(WINDOW *win, Lista *l)			//semelhante a função padrão MOSTRA para listas, porém com saída em NCURSES.
{
int i = 3;
    No *aux;
    if(l->inicio == NULL) mvwprintw(win, i, 3, "Lista vazia!\n");
    else
    {
        aux = l->inicio;
        do
        {
            mvwprintw(win, i, 3, "%s\n", aux->p.Descricao);
            mvwprintw(win, i+1, 3, "%s\n", aux->p.CodigoB);
			wrefresh(win);
            aux = aux->prox;
            i = i + 1;
        }
        while(aux != l->inicio);
    }
    while(1);
}

void Mostra(Lista l) // Função que mostra a lista
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
            //printf("%s\n", aux->p.Data); // Serve apenas no caso de mostrar o estoque, a lista de alocação possui o campo 'Data' vazio, tornando-a inoperante
            printf("%d/%d/%d\n", aux->p.Dia, aux->p.Mes, aux->p.Ano);
            //printf("\n%d",aux->p.Validade);
            printf("--------------------------------------\n");
            aux = aux->prox;
        }
        while(aux != l.inicio);
    }
}

void AdicionandoProduto(Lista *l, WINDOW* win, char cod[13], int *tela, char data[11], char empresa[30])
{
    

        Produto aux;
        DigitandoCodigo(win, cod);
        strcpy(aux.CodigoB, cod);

        memset(aux.Descricao, '\0', 200);
        if(ConfereCod(empresa, &aux, l))
        {
            
        }

        
        mvwprintw(win, 10,5 , "%s", aux.Descricao);
        DigitandoData(win, data);
        mvwprintw(win, 1, 1, "%s", data);
        mvwprintw(win, 2, 2, "%s", cod);
        wrefresh(win);
        while(1);

   
}

/*void AdicionandoProduto(Lista *l, Lista *l2) // Função destinada a receber os dados de um item, transformando-o em um Produto para a função InsereOrdenado
{
    char Fornecedor[30];
    printf("Entre com o fornecedor do produto: ");
    scanf(" %30[^\n]", Fornecedor); // o scanf está desse jeito por receber apenas 30 caracteres e não dividir a palavra quando receber um espaço, apenas ao pressionar 'enter'
    for(int i = 0; i<= strlen(Fornecedor); i++) //Laço utilizado para passar todos os caracteres da string 'Fornecedor' para maiúsculo
        Fornecedor[i] = toupper(Fornecedor[i]);
    if(InserirMemoria(Fornecedor, l2, 1) == 0) return; // Chamada da função InserirMemória, onde pegamos os dados do arquivo.txt e o transferimos para uma lista na memória principal
    printf("Você deseja adicionar quantos produtos?\n");
    int n;
    scanf("%d", &n);
    if(n <= 0) // Função que confere a quantidade de produtos adicionados
    {
        printf("A quantidade de produtos adicionados precisa ser maior do que 0.\n");
    }
    else // Executa a partir de uma quantidade válida de produtos
    {
        for(int i =0; i<n; i++) // Laço para quantos produtos existirem
        {
            Produto aux;
            strcpy(aux.Fornecedor, Fornecedor);
            printf("Entre com o código de barras: ");
            scanf(" %25[^\n]", aux.CodigoB);
            if(ConfereCod(Fornecedor, &aux, l2)) // verifica se a função ConfereCod retorna 1, indicando que o código de barras existe na base de dados do fornecedor citado
            {
                printf("Entre com a data de validade do produto [dd mm aaaa]: ");
                scanf("%d %d %d", &aux.Dia, &aux.Mes, &aux.Ano);
                while(DataValida(aux.Dia, aux.Mes, aux.Ano) == 0) // Enquanto a função retornar 0, executa, indicando que a data inserida não é válida Ex: '32/14/1990'
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
}*/

int Remover(Lista *l, char dado[]) // Função que remove um  nó da lista, não está funcionando, estamos trabalhando para resolver
{
    No *aux;
    if(l->inicio == NULL)
        return 0;
    aux = l->inicio;
    strcat(dado, "\n");
    do
    {
        if(strcmp(aux->p.CodigoB, dado) == 0){
            if(aux == l->inicio && aux == l->fim){
                free(aux);
                l->inicio = l->fim = NULL;
                return 1;
            }

            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;

            if(aux == l->inicio)
                l->inicio = aux->prox;
            if(aux == l->fim)
                l->fim = aux->ant;
            free(aux);
            return 1;
        }
        aux = aux->prox;
    }
    while (aux != l->inicio);
    printf("Produto não encontrado\n");
    // se chegou aqui, não achou d
    return 0;
}

void RemovendoProduto(Lista *l)  // Função que recebe o produto que será removido, tornando viável sua localização e remoção
{
    char cod[30];
    printf("\nDigite o código de barras: ");
    scanf(" %25[^\n]", cod);
    Remover(l, cod);
    clearscr();
}

int DataValida(Produto prod)  // Função que verifica se as datas de vencimento inseridas são válidas
{

    struct tm atual;
    atual = DataAtual();
    if(prod.Ano == atual.tm_year) // verifica se o ano inserido é igual ao ano atual
        if(prod.Mes >= atual.tm_mon && prod.Mes <=12){ //se o mês for maior ou igual ao atual  && menor ou igual a 12 é válida
            if(prod.Dia>= atual.tm_mday && prod.Dia <=30) // se o dia for maior ou igual ao atual && menor ou igual a 30 é válida
                return 1;
            else return 0;
        }
        else return 0;

    if(prod.Ano > atual.tm_year) // se o ano for maior que o atual e os dias e meses válidos, aceita
        if(prod.Dia <= 30 && prod.Mes <=12)
            return 1;

    return 0;
}

struct tm DataAtual()  // Função que verifica o ano atual, utilizando a biblioteca time.h
{
    struct tm aux;
    time_t seconds;
    time(&seconds);
    aux = *localtime(&seconds);
    aux.tm_year += 1900; /* soma realizada pelo fato da variável conter os valores a partir do ano de 1900
    Exemplo: o ano de 2022, retornará apenas 122*/
    aux.tm_mon += 1; /* soma realizada pelo fato da variável conter os valores dos meses de 0 a 11*/
    return aux;
}

void ConferirValidade(Lista *l) // Função que confere a validade dos itens já em estoque
{
    clearscr();
    int i = 0;
    char est[8] = {"estoque"}; // Passa o nome do arquivo txt há ser aberto
    InserirMemoria(est, l, 0); // Salvando os itens do txt na memória principal

    if(l->inicio == NULL){
        printf("\nEstoque vazio!\n");
        return;
    }
    No *aux;
    aux = l->inicio;
    do // Enquanto existirem produtos na lista
    {
        if(DataValida(aux->p) == 0 && aux->p.Validade != 1) // if que verifica se os produtos estão vencidos
        {
            char opt;
            aux->p.Validade = 1;
            printf("%s", aux->p.Descricao);
            printf("%s", aux->p.CodigoB);
            printf("%d/%d/%d", aux->p.Dia, aux->p.Mes, aux->p.Ano);
            printf("\nEste item está vencido!\n\n");
            printf("Você gostaria de remover este item do estoque?\n");
            scanf(" %c", &opt);
            if(opt == 'y'){
                Remover(l, aux->p.CodigoB);
                Salvar(*l);
                if(l->inicio == NULL)   return;
            }
            i++;
        }
        aux = aux->prox;
    }
    while(aux != l->inicio);
    if(i == 0){
        printf("Todos os itens do estoque estão dentro da data de validade...\n");
        return;
    }
}

void Salvar(Lista l)
{
    char data[12];
    FILE *estoque;
    if((estoque = fopen("./EMP/estoque.txt","w+"))) // se conseguir abrir o arquivo do estoque
    {
        if(l.inicio == NULL){
                fprintf(estoque, "%c", ' ');
                fclose(estoque);
                return;
        }
        No *aux;
        aux = l.inicio;
        do
        {
            
            //do-while que serve para percorrer a lista em questão e salvar seus dados no txt
            fprintf(estoque, "%s", aux->p.Descricao); // Função que escreve em um arquivo de texto, passa-se(arquivo, máscara do tipo, variavel a ser inserida)
            fprintf(estoque, "%s", aux->p.CodigoB);
            fprintf(estoque, "%c", '*');
            if(aux->p.Dia < 10) // fez se necessário este if para regular as entradas de meses e/ou dias que possuiam apenas um algarismo
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
        fclose(estoque);
    }
    else printf("Não foi possível abrir o arquivo!\n");

    return; // função necessária sempre ao abrir um arquivo, serve para fecha-lo
}

void SalvandoProdutos(Lista *l) // Função que verifica o chamado para salvar os itens no txt do estoque
{
    if(l->inicio != NULL)
    {
        printf("Você gostaria de atualizar estes itens no estoque?\n");
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
int ConfereEmp(char *dado) // Função para verificar a existência da empresa
{
    FILE *Arquivo;
    char emp[70];
    strcat(dado, "\n");
    if((Arquivo = fopen("Empresas.txt", "r")))
    {
        while(fgets(emp, 30, Arquivo)) // Enquanto fgets for diferente de nulo
        {
            if(strcmp(dado, emp) == 0) // compara as empresas existentes com a string inserida
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



int ConfereCod(char *dado, Produto *produto, Lista *l2) // Função que verifica a existência do código de barras na base da empresa e retorna sua descrição para o produto
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
            if(strcmp(produto->CodigoB, codigo) == 0) // Verifica se o código existe na base de dados da empresa
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
    printf("\nCodigo não encontrado na base de dados da empresa!\n");
    return 0;
}

int InserirMemoria(char *Empresa, Lista *l, int tipo)  // Função que passa todos os itens de um Fornecedor para a memória
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
        if(tipo == 1) // primeiro uso da função, utilizada pra salvar itens na lista das empresas 
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
        else if (tipo == 0) // segundo iso, utilizada para salva itens do estoque.txt na lista do estoque
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

void PassaInteiro(Produto *p) // função utilizada para transferir a data, capturada em string, para inteiros, tornadno útil a função de conferir data
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

void ConsultarEstoque(Lista l){
    char est[8] = {"estoque"};
    InserirMemoria(est ,&l, 0);
    //InserirMemoria("estoque" ,&l, 0);
    printf("\t\t\t\nA organização possui, dentro do seu estoque: %d itens\n", Tamanho(l));
    if(Tamanho(l) == 0) return;
    printf("\t\nSendo eles:\n");
    Mostra(l);
    return;
}
