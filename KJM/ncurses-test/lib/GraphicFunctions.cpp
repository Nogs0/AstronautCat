#include "../includes/HeaderGraphic.h"


WINDOW *DesenharJanelaEntrada(int COLUNAS, int LINHAS)
{
    WINDOW *JanelaEntrada;
	JanelaEntrada = newwin(LINHAS, COLUNAS-COLUNAS/3 - 1, 0, COLUNAS/3 + 1);
	box(JanelaEntrada, 0,0);
	wrefresh(JanelaEntrada);
	return JanelaEntrada;
	
}

WINDOW *DesenharJanelaEmpresas(int COLUNAS, int LINHAS)
{
	//clearscr();
   
	WINDOW *JanelaEmpresas;
	JanelaEmpresas = newwin(LINHAS, COLUNAS/3, 0, 0);
	box(JanelaEmpresas, 0,0);
	wrefresh(JanelaEmpresas);
	return JanelaEmpresas;
}

WINDOW *DesenharJanelaOPT(int COLUNAS, int LINHAS)
{
	int WIDTH = 30;
	int HEIGHT = 10;
	int startx = (LINHAS - WIDTH);
	int starty = (COLUNAS - HEIGHT);
	
	WINDOW *JanelaOPT;
	JanelaOPT = newwin(HEIGHT, WIDTH, 0, 0);
	box(JanelaOPT, 0,0);
	wrefresh(JanelaOPT);
	return JanelaOPT;
		
}

int preencherJanelaOPT(WINDOW *JanelaOPT)
{
	char options[6][100] = {"ADICIONAR PRODUTOS A LISTA", 
							"REMOVER", 
							"MOSTRAR LISTA DE ALOCACAO", 
							"CONSULTAR VALIDADE", 
							"SALVAR LISTA", 
							"SAIR"};
		
	int c;
	int highlight = 1;
	int totalEscolha = 6;
	int choice = 0;
	keypad(JanelaOPT, TRUE);

	MostrarOPT(JanelaOPT, highlight, totalEscolha, options);
	while(1)
	{
		c = wgetch(JanelaOPT);
		switch(c){
			case KEY_UP:
			if(highlight == 1)
			highlight = totalEscolha;
			else
				--highlight;
			
			break;
		case KEY_DOWN:
			if(highlight == totalEscolha)
			highlight = 1;
			else
			++highlight;
			break;
		case 10:
			choice = highlight;
			return highlight;
			break;
		default:
			break;
		}
	MostrarOPT(JanelaOPT, highlight, totalEscolha, options);
	}
}

void MostrarOPT(WINDOW *win, int highlight, int tamanhoTotal, char choices[][100])
{
  int x, y, i;

  x = 1;
  y = 1;
	

  for(i = 0; i < tamanhoTotal; ++i){
    if(highlight == i + 1){ /* Destaca a escolha atual */
      wattron(win, A_REVERSE);
      mvwprintw(win, y, x,"%s", choices[i]);
      wattroff(win, A_REVERSE);
	 
    }else{
       mvwprintw(win, y, x,"%s", choices[i]);
    }
    ++y;
  }
  
  
}
int PreencherJanelaEmpresas(Lista *listaAlocacao, WINDOW* win2, char *empresaAtual, char empresas[][30], WINDOW* win, int COLUNAS, int LINHAS)
{
	int inicio = 0;
	int highlight = inicio + 1;
	int totalEscolha = 26;
	int voltar = 0;
	wrefresh(win);
	keypad(win, TRUE);

	MostrarEmpresas(win, totalEscolha, empresas, highlight, inicio);

	while(1)
	{
		int c = 0;
		c = wgetch(win);
		switch(c)
		{
			
			case KEY_F(2):
				if (inicio + totalEscolha < 78)
				{
					wclear(win);
					box(win, 0,0);
					inicio = inicio + totalEscolha;
					highlight = inicio + 1;
					MostrarEmpresas(win, totalEscolha, empresas, highlight, inicio);
					break;
				}
				else
				{
					wclear(win);
					box(win, 0,0);
					inicio = inicio + totalEscolha - 78;
					highlight = inicio + 1;
					MostrarEmpresas(win, totalEscolha, empresas, highlight, inicio);
					break;
				}
					
			case 10:
			{
			    char cod[14] = {};
   				char data[11] = {};

				Lista listaProdutos;
				CriaLista(&listaProdutos);

				strcpy(empresaAtual, empresas[highlight -1]);
				PreencherJanelaEntrada(win2, empresaAtual);
				InserirMemoria(empresaAtual, &listaProdutos, 1);
				AdicionandoProduto(&listaProdutos, listaAlocacao, win2,cod, data, empresaAtual);
				wrefresh(win2);
				break;
			}

			case KEY_UP:
				werase(win2);
				if(highlight == inicio + 1)
					highlight = totalEscolha + inicio; 
				else
					--highlight;
				break;

			case KEY_DOWN:
				werase(win2);
				if(highlight == totalEscolha + inicio)
					highlight = inicio + 1;
				else
					++highlight;
				break;
			default:
				break;
			case KEY_F(1):
				return 0;
		}
			MostrarEmpresas(win, totalEscolha, empresas, highlight, inicio);
		
	}

}

void DigitandoCodigo(WINDOW *win, char cod[14])

{
	
	memset(cod, '\0', 14);							//reseta o vetor 
	int tam = strlen("Codigo de barras: ") + 5;		//define a coluna onde o cursor vai se mover
	
	mvwprintw(win, 9, 5, "Codigo de barras: ");		//printa na tela 
	capturandoTeclado(win, cod, tam, 9, 14);		//função de capturar teclado
	

}

void DigitandoData( WINDOW *win, char data[11])
{
	memset(data, '\0', 11);	//reseto a string
	int tam = strlen("Digite a data de validade: ") + 5; //defino onde vai começar a aparecer as escritas
	mvwprintw(win, 15, 5, "Digite a data de validade: ");//printo na tela
	capturandoTeclado(win, data, tam, 15, 11);			//função
	
	wrefresh(win);
	
	
	
	//mvwprintw(win, 14,5, "data digitada foi %d/%d/%d", dia, mes, ano);
}

void capturandoTeclado(WINDOW* win, char *cod, int tam, int linha, int tamanhoTotal)
{
	
	keypad(win, true);			//ativa o teclado
	int i = 0, c = 0;			//inicializa as variaveis
	move(linha,tam);
	wclrtoeol(win);
	wrefresh(win);				//atualiza a tela
	while (i < tamanhoTotal -1)	//tamanhoTotal é o tamanho da string, 13 para codigo e 11 para data
	{
		c = getchar();			//captura um char

		if ( c == KEY_F(9))
			break;
		if (c == 127 || c == 8) //caso backspace
		{
			if(i > 0)			//ve se tem algo pra apagar
			{		
				i--;
				cod[i+1] = '\0';		
				cod[i] = ' ';	
				mvwprintw(win, linha, tam, "%s", cod);
				move(9,i);
				mvprintw(9, i, " "); //printa um espaço vazio
				wrefresh(win);
				
			}
		}
		else{
			if ((c >= 48 && c <= 57 || c == 47)) //se for numero ou '/'
			{
				cod [i] = c;				   //printa na tela a letra
				i++;						   //proxima posição
			}
			
			
		}
		mvwprintw(win, linha, tam, "%s", cod);
		wrefresh(win);
	}
}

void PreencherJanelaEntrada(WINDOW *win, char *empresaAtual)
{
		werase(win);
		box(win, 0,0);
		mvwprintw(win, 1, (getmaxx(win)/2) - (strlen(empresaAtual)/2), "%s", empresaAtual);

}

void MostrarEmpresas(WINDOW *win, int altura, char empresas[][30], int highlight, int inicio)
{
	int x,y,i;
	x = 2;
	y = 3;
	int j = 0;
	box(win, 0,0);
	wattron(win, A_BOLD);
	char text[35] = "(<F1)SELECIONE A EMPRESA: (F2>)";
	mvwprintw(win,1, (getmaxx(win)/2) - (strlen(text)/2), "%s", text);

	wattroff(win, A_BOLD);
	
	for(i = inicio; i - inicio < altura; ++i)
	{	if(highlight == i + 1) 		
		{	wattron(win, A_REVERSE);
			mvwprintw(win, y, x, "%s", empresas[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, y, x, "%s", empresas[i]);
		++y;
	}
	wrefresh(win);
}

void CriarVetorEmpresas(WINDOW *win, char empresas[][30])
{
	FILE *file; 
	int i = 0, j = 0;
	
	//int tamanho = verificarTotal(file);
	char cadaEmpresa[30];
	
	
	file = fopen("./EMP/Empresas.txt","r");
	if(file){
		while(fgets(cadaEmpresa, 30, file))
		{
			strcpy(empresas[i], cadaEmpresa);
			i++;
		}
	}
	
	
}




