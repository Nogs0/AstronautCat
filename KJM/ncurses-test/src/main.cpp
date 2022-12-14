#include "../includes/HeaderGraphic.h"

#define COLUNAS     100
#define LINHAS      30  


int main()
{
    
    WINDOW *JanelaEntrada;
    WINDOW *JanelaEmpresas;
    WINDOW *JanelaOPT;

    char empresaAtual[30];
    memset(empresaAtual, '\0', 30);
    char empresas[100][30] = {};

    Lista listaValidade;
    CriaLista(&listaValidade);
    Lista listaAlocacao;
    CriaLista (&listaAlocacao);
    
  

 
    initscr();
    noecho();
    clear();
    cbreak();

    
    


    while (1)
    {
        int c = 0;
        
        JanelaOPT = DesenharJanelaOPT(COLUNAS, LINHAS);
        wrefresh(JanelaOPT);
        int opt = preencherJanelaOPT(JanelaOPT);
            switch(opt)
            {
                case 1: //ADICIONANDO PRODUTO
                    JanelaEmpresas = DesenharJanelaEmpresas(COLUNAS, LINHAS);
                    JanelaEntrada = DesenharJanelaEntrada(COLUNAS, LINHAS);
                    CriarVetorEmpresas(JanelaEmpresas, empresas);
                    PreencherJanelaEmpresas(&listaAlocacao, JanelaEntrada, empresaAtual, empresas, JanelaEmpresas, getmaxy(JanelaEmpresas), getmaxx(JanelaEmpresas));
                    werase(JanelaEmpresas);
                    werase(JanelaEntrada);
                    wrefresh(JanelaEmpresas);
                    wrefresh(JanelaEntrada);
                    break;
                case 2:
                    delwin(JanelaOPT);
                    //refresh();
                    break;
                case 3:
                {
                    werase(JanelaEntrada);
                    wrefresh(JanelaEntrada);
                    char phrase[12] = "LISTA ATUAL";
                    MostraNCURSES(JanelaEntrada, &listaAlocacao, phrase);
                    break;
                }
                case 4:
                     werase(JanelaEntrada);
                    wrefresh(JanelaEntrada);
                    JanelaEntrada = DesenharJanelaEntrada(COLUNAS, LINHAS);
                   
                    ConferirValidade(JanelaEntrada, &listaValidade);
                    CriaLista(&listaValidade);
                    wrefresh(JanelaEntrada);
                    break;
                case 5:
                {
                    char opt2[2] = "a";
                    Salvar(JanelaEntrada, listaAlocacao, opt2);
                    CriaLista(&listaAlocacao);
                    
                    
                    break;
                }
                case 6:
                    refresh();
                    endwin();
                    return 0;
            }
            JanelaOPT = DesenharJanelaOPT(COLUNAS, LINHAS);
             wrefresh(JanelaOPT);
        
    }
  
    mvwprintw(JanelaEntrada, 1, 1, "cheguei");
    while(1);
   
   
    //wrefresh(JanelaEmpresas);
    //while(1);

}