#include <iostream>
#include <ncurses.h>
#include <vector>

#define WIDTH 30 
#define HEIGHT 10

int startx = 0;
int starty = 0;

std::vector<std::string> choices = {"ADICIONAR PRODUTOS A LISTA",
				    "REMOVER PRODUTO DA LISTA",
				    "MOSTRAR LISTA DE ALOCACAO",
				    "CONSULTAR VALIDADE",
				    "SALVAR LISTA",
				    "SAIR"};

int n_choices = choices.size();
void print_menu(WINDOW *menu_win, int highlight);


int main(){
  WINDOW *menu_win;
  int highlight = 1;
  int choice = 0;
  int c;
   initscr();
  clear();
  noecho();
  cbreak();       
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  keypad(menu_win, TRUE);
  mvprintw(1,0, "**************************************");
  mvprintw(2,0, "BEM VINDO AO ESTOQUE DE MERCADORIA JM");
  mvprintw(3,0, "***************************************");
  refresh();
  print_menu(menu_win, highlight);
  while( true ){
    c = wgetch(menu_win);
    switch(c){
      case KEY_UP:
        if(highlight == 1){
          highlight = n_choices;
        }else{
          --highlight;
        }
        break;
      case KEY_DOWN:
        if(highlight == n_choices)
          highlight = 1;
        else
          ++highlight;
        break;
      case 10:
        choice = highlight;
        break;
      default:
        mvprintw(24, 0, "                                                                       ");
        refresh();
        mvprintw(24, 0, "O número do caractere que você digitou é = %3d e corresponde à: '%c'", c, c);
        refresh();
        break;
    }
	print_menu(menu_win, highlight);
	if (choice == 6){
	break;
	}
}
	clrtoeol();
	refresh();
	endwin();
	return 0;
  }
void print_menu(WINDOW *menu_win, int highlight){
  int x, y, i;

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for(i = 0; i < n_choices; ++i){
    if(highlight == i + 1){ /* Destaca a escolha atual */
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", &choices[i][0]);
      wattroff(menu_win, A_REVERSE);
    }else{
      mvwprintw(menu_win, y, x, "%s", &choices[i][0]);
    }
    ++y;
  }
  wrefresh(menu_win);
}
