#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

/*

        FUNCOES COMUNS:

        attron(atribs):                //Ativa os atributos de texto
        attroff(atribs):               //Desativa os atributos de texto
                    A_NORMAL           //Exibicao normal do texto
                    A_STANDOUT         //Melhor modo de destaque no terminal
                    A_UNDERLINE        //Sublinhado
                    A_REVERSE          //Inverte a cor do fundo
                    A_BLINK            //Piscando
                    A_DIM              //Meio Brilhante
                    A_BOLD             //Extra brilho ou negrito
                    A_ALTCHARSET       //Conjunto de caracteres alternativos
                    COLOR_PAIR(n)      //Par de cores n que foi pre-definido
*/


int main(){
    int c;

    initscr();                          //Inicializa o terminal em modo curses
    start_color();                      //Inicializa as cores
    raw();                              //Desativa o buffer de linha, CTRL-Z e CTRL-C Nao fazem nada
    noecho();                           //Teclado nao ecoa no display
    keypad(stdscr, TRUE);               //Permite leitura de teclas de funcao

    printw("Escreva na posicao 0,0");   //EScreve na coordenada atual(0,0)
    refresh();                          //Atualiza a tela com as partes modificadas


    printw(" DIGITE F1 OU F2 OU F3: ");
    do{
        c = getch();                    //Espera uma tecla
        attron(A_REVERSE);              //Ativa um modo de texto que vai ser aplicado a todo texto ate a funcao attroff
        switch(c){
            case KEY_F(1): printw("F1 foi pressionado");
                           break;
            case KEY_F(2): printw("F2 foi pressionado");
                           break;
            case KEY_F(3): printw("F3 foi pressionado");
                           break;
            default:

        }
        attroff(A_REVERSE);
        refresh();
    }while(c != KEY_F(1) && c != KEY_F(2) && c != KEY_F(3));

    //Testa conjuntos de caracteres alternativos
    move(3,0);
    printw("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    move(4,0);
    attron(A_ALTCHARSET);
    printw("abcdefhhijklmnopqrstuvwxyz");
    attroff(A_ALTCHARSET);
    refresh();

    //Movimentacao do cursor
    move(LINES-3, COLS-25);
    printw("Ultima linha na direita");
    move(LINES-2, COLS-25);
    printw("nLinhas=%d,nColunas=%d", LINES, COLS);
    refresh();

    init_pair(1, COLOR_RED, COLOR_BLUE);           //Defino um par de cores
    attron(COLOR_PAIR(1));                          //Ativo o par de cores definido

    mvprintw(LINES-1,0,"Tecle qualquer coisa para terminar %.4f", 123.456);
    refresh();
    getch();

    keypad(stdscr, FALSE);
    noraw();
    echo();

    endwin();
    }

