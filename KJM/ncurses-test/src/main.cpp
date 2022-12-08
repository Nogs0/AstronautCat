#include "../includes/HeaderGraphic.h"

#define COLUNAS     100
#define LINHAS      30  

WINDOW *JanelaEntrada;


int main()
{
    
    WINDOW *JanelaEntrada;
    WINDOW *JanelaEmpresas;
    int posCod, posData;
    int tela = 0;
    char cod[14] = {};
    char data[11] = {};
   
    char empresaAtual[30];
    memset(empresaAtual, '\0', 30);
    char empresas[100][30] = {};

    Lista listaProdutos;
    CriaLista(&listaProdutos);

    setlocale(LC_ALL, "Portuguese");
    initscr();
    noecho();
    clear();
    cbreak();

    JanelaEmpresas = DesenharJanelaEmpresas(COLUNAS, LINHAS);
    JanelaEntrada = DesenharJanelaEntrada(COLUNAS, LINHAS);
    
    CriarVetorEmpresas(JanelaEmpresas, empresas);
    PreencherJanelaEmpresas(JanelaEntrada, empresaAtual, &tela, empresas, JanelaEmpresas, getmaxy(JanelaEmpresas), getmaxx(JanelaEmpresas) );
    //Ao chegar aqui, a variavel empresaAtual possui a empresa escolhida.
    InserirMemoria(empresaAtual, &listaProdutos, 0);
    //a Lista "listaProdutos" agora possui todos os produtos da empresa selecionada.
    
    //MostraNCURSES(JanelaEntrada, &listaProdutos);
    AdicionandoProduto(&listaProdutos, JanelaEntrada, cod, &tela, data, empresaAtual);
    
    //RemovendoProduto(&listaProdutos, JanelaEmpresas);
    mvwprintw(JanelaEntrada, 1, 1, "cheguei");
    while(1);
   
   
    //wrefresh(JanelaEmpresas);
    //while(1);

}