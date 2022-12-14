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

void MostraNCURSES(WINDOW *win, Lista *l, char *titulo)			//semelhante a função padrão MOSTRA para listas, porém com saída em NCURSES.
{
    
    box(win, 1, 0);
    int i = 2;
    int n = 0;
    int lenght = 0;
    char aux2[150] = {}; 
    No *aux;
    wattron(win, A_DIM);
    mvwprintw(win,1, (getmaxx(win)/2) - (strlen(titulo)/2), "%s",titulo);
    wattroff(win, A_DIM);
    if(l->inicio == NULL) {
        char text[50] = "** LISTA VAZIA **";
        wattron(win, A_BOLD);
        mvwprintw(win,2, (getmaxx(win)/2) - (strlen(text)/2), "%s", text);
        wattroff(win, A_BOLD);
        wrefresh(win);
    }
    else
    {
        aux = l->inicio;
        do
        {
            if (n % 2 == 0)
                wattron(win, A_DIM);
            if (strlen(aux->p.Descricao) > getmaxx(win) - 10){
                int i = 0;
                for (i = 0; i < getmaxx(win) - 10; i++)
                {
                    aux2[i] = aux->p.Descricao[i];
                }
            for (i = getmaxx(win) - 10; i < getmaxx(win) - 7; i++)
                aux2[i-1] = '.';
            aux2[i] = '\0';
            }
            else
                strcpy(aux2, aux->p.Descricao);
            
            int j = 3;
            mvwprintw(win, ++i, j, "%s", aux2);
            mvwprintw(win, ++i, j, "%s", aux->p.CodigoB);
            mvwprintw(win, ++i, j, "%s\n", aux->p.Data);
			wrefresh(win);
            aux = aux->prox;
            i = i + 1;
            n++;
            wattroff(win, A_DIM);
        }
        while(aux != l->inicio);
    }
    
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

void AdicionandoProduto(Lista *l, Lista *l2, WINDOW* win, char cod[13], char data[11], char empresa[30])
{
    

        Produto aux;
        char aux2[150] = {};
        DigitandoCodigo(win, cod);
        strcpy(aux.CodigoB, cod);
        memset(aux.Descricao, '\0', 200);
        while(ConfereCod(win, empresa, &aux, l) == 0)
        {
            DigitandoCodigo(win, cod);
            strcpy(aux.CodigoB, cod);
            memset(aux.Descricao, '\0', 200);
        }
        wmove(win, 7,0);
        wclrtoeol(win);
        
        wrefresh(win);
        if (strlen(aux.Descricao) > getmaxx(win) - 10){
                int i = 0;
                for (i = 0; i < getmaxx(win) - 10; i++)
                {
                    aux2[i] = aux.Descricao[i];
                }
            for (i = getmaxx(win) - 10; i < getmaxx(win) - 7; i++)
                aux2[i-1] = '.';
            aux2[i] = '\0';
            }
            else
                strcpy(aux2, aux.Descricao);
            
        mvwprintw(win, 10,5 , "%s", aux2);
        DigitandoData(win, data);
        strcpy(aux.Data, data);
        PassaInteiro(&aux);


        while(DataValida(win, &aux) == 0){
            DigitandoData(win, data);
            strcpy(aux.Data, data);
            PassaInteiro(&aux);
        }
        wmove(win, 12,0);
        wclrtoeol(win);

        InsereOrdenado(l2, aux);
        mvwprintw(win, 17,5, "Tudo ok, produto adicionado a lista de alocacao !");
        wrefresh(win);
        keypad(win, FALSE);
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

// void RemovendoProduto(Lista *l)  // Função que recebe o produto que será removido, tornando viável sua localização e remoção
// {
//     char cod[30];
//     printf("\nDigite o código de barras: ");
//     scanf(" %25[^\n]", cod);
//     Remover(l, cod);
//     clearscr();
// }

void RemovendoProduto(Lista *l, WINDOW *win){
    refresh();
    box(stdscr, 0, 0);
    refresh();
    char cod[20];
    DigitandoCodigo(win, cod);
    Remover(l, cod);
    wrefresh(win);
}

int DataValida(WINDOW *win, Produto *prod)  // Função que verifica se as datas de vencimento inseridas são válidas
{

    struct tm atual;
    atual = DataAtual();
    if(prod->Ano == atual.tm_year) // verifica se o ano inserido é igual ao ano atual
        if(prod->Mes >= atual.tm_mon && prod->Mes <=12){ //se o mês for maior ou igual ao atual  && menor ou igual a 12 é válida
            if(prod->Dia>= atual.tm_mday && prod->Dia <=30) // se o dia for maior ou igual ao atual && menor ou igual a 30 é válida
                return 1;
            else return 0;
            
        }
        else return 0;
        

    if(prod->Ano > atual.tm_year) // se o ano for maior que o atual e os dias e meses válidos, aceita
        if(prod->Dia <= 30 && prod->Mes <=12)
        
            return 1;
    wattron(win, A_BLINK);
    wattron(win, A_BOLD); 
    mvwprintw(win, 13, 5, "*Digite uma data valida !*");
    wattroff(win, A_BOLD); 
    wattroff(win, A_BLINK);
    wrefresh(win);
            
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

void ConferirValidade(WINDOW* win, Lista *l) // Função que confere a validade dos itens já em estoque
{

    int i = 0;
    char est[8] = {"estoque"}; // Passa o nome do arquivo txt há ser aberto
    InserirMemoria(est, l, 0); // Salvando os itens do txt na memória principal

    if(l->inicio == NULL){
        mvwprintw(win, 1, 1, "\nEstoque vazio!\n");
        return;
    }
    No *aux;
    aux = l->inicio;
    do // Enquanto existirem produtos na lista
    {
        if(DataValida(win, &aux->p) == 0 && aux->p.Validade != 1) // if que verifica se os produtos estão vencidos
        {
            
                char opt;
                aux->p.Validade = 1;
                int j = 2;
                mvwprintw(win, ++j, 3, "%s", aux->p.Descricao);
                mvwprintw(win, ++j, 3,"%s", aux->p.CodigoB);
                mvwprintw(win, ++j, 3,"%d/%d/%d", aux->p.Dia, aux->p.Mes, aux->p.Ano);
                mvwprintw(win, ++j, 3,"Este item está vencido!");
                mvwprintw(win, ++j, 3,"Você gostaria de remover este item do estoque?");
                wrefresh(win);
                scanf(" %c", &opt);
                if(opt == 'y'){
                    Remover(l, aux->p.CodigoB);
                    char opt2[3] = "w+";
                    Salvar(win, *l, opt2);
                    if(l->inicio == NULL)   return;
                }
                i++;
            
        }
        aux = aux->prox;
    }
    while(aux != l->inicio);
    if(i == 0){
        wattron(win, A_BOLD);
        char text[50] = "** O ESTOQUE NAO POSSUI ITENS VENCIDOS **";
        mvwprintw(win,2, (getmaxx(win)/2) - (strlen(text)/2), "%s", text);
        wattroff(win, A_BOLD);
        wrefresh(win);
        return;
    }
    wrefresh(win);
}

void Salvar(WINDOW* win, Lista l, char opt[2])
{
    char data[12];
    FILE *estoque;

    //if (opt == 1)
    if((estoque = fopen("./EMP/estoque.txt",opt))) {// se conseguir abrir o arquivo do estoque

        if(l.inicio == NULL){
                wclear(win);
                box(win, 1, 0);
                char text[80] = "** NAO E POSSIVEL SALVAR UMA LISTA VAZIA **";
                wattron(win, A_BOLD);
                 wattron(win, A_BLINK);
                mvwprintw(win,1, (getmaxx(win)/2) - (strlen(text)/2), "%s", text);
                wattroff(win, A_BOLD);
                wattroff(win, A_BLINK);
                wrefresh(win);
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


    wclear(win);
    box(win, 1,0);
    char text[50] = "LISTA SALVA NA MEMORIA !!!";
    wattron(win, A_BOLD);
    mvwprintw(win,1, (getmaxx(win)/2) - (strlen(text)/2), "%s", text);
    wattroff(win, A_BOLD);
    wrefresh(win);
    return; // função necessária sempre ao abrir um arquivo, serve para fecha-lo
}

/*void SalvandoProdutos(Lista *l) // Função que verifica o chamado para salvar os itens no txt do estoque
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
            char opt2[2] = "a";
            Salvar(*l, opt2);
            CriaLista(l);
            clearscr();
        }
    }
    else
        return;

}*/

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

int ConfereCod(WINDOW *win, char *dado, Produto *produto, Lista *l2) // Função que verifica a existência do código de barras na base da empresa e retorna sua descrição para o produto
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
    wattron(win, A_BLINK);
    wattron(win, A_BOLD);   
    mvwprintw(win, 7, 5, "*Codigo não encontrado na base de dados da empresa!*");
    wattroff(win, A_BLINK);
    wattroff(win, A_BOLD); 
    return 0;
}

int InserirMemoria(char *Empresa, Lista *l, int tipo)  // Função que passa todos os itens de um Fornecedor para a memória
{

    
        FILE *Arq;
        int i = 0;
        Produto prod;
        char aux[30] = {"./EMP/"};
        char codigo[300];
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
                fgets(codigo, 300, Arq);
                strcpy(prod.Descricao, codigo);
                memset(codigo, '\0', 300);

                fgets(codigo, 300, Arq);
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
        int i = 0, j=0;
        
        //0123456789  10
        //18/05/2046  \0
        if (p->Data[0] == '*')
            i = 1;
        int k = i;
        while(i < k+2)
        {
            auxdia[j] = p->Data[i];
            i++;
            j++;
        }
        i = k+3;
        k = i;
        j = 0;
        while(i<k+2)
        {
            auxmes[j] = p->Data[i];
            i++;
            j++;
        }
        i = k+3;
        k = i;
        j = 0;
        while(i<k+5)
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
