#include <stdio.h>
#include <stdlib.h>
#include "Head.h"
#include <ctype.h>
#include "Func.c"

int main()
{
    Lista ListadeAlocacao, ListaEmpresa;
    CriaLista(&ListadeAlocacao);
    CriaLista(&ListaEmpresa);
    int acao = 0;
    char option = ' ';

    printf("********************************************************************************\n");
    printf("\t\tBem vindo ao KJM - Soluções em Armazenamento\n");
    printf("********************************************************************************\n");
    do{
        printf("O que você deseja fazer?\n");
        printf("1 - ADICIONAR PRODUTOS À LISTA\n2 - REMOVER PRODUTO DA LISTA\n3 - MOSTRAR LISTA DE ALOCAÇÃO\n4 - CONSULTAR VALIDADE\n5 - SALVAR LISTA\n");
        scanf("%d", &acao);
        switch (acao){
            case 1:
                printf("\tAdicionando produtos...\n");
                AdicionandoProduto(&ListadeAlocacao, &ListaEmpresa);
                break;
            case 2:
                if(ListadeAlocacao.inicio){
                printf("\tRemovendo Produtos...\n");
                RemovendoProduto(&ListadeAlocacao);
                }
                else printf("Estoque vazio\n");
                break;
            case 3:
                Mostra(ListadeAlocacao);
                break;
            case 4:
                ConferirValidade(ListadeAlocacao);
                break;
            case 5:
                SalvandoProdutos(&ListadeAlocacao);
                break;
        }
        printf("\n\nDeseja continuar no programa? [ y - n ]: ");
        scanf(" %c", &option);
        option = tolower(option);
        if(option == 'n'){
        if(ListadeAlocacao.inicio){
            printf("Você possui itens em sua lista de alocação, gostaria de deixar o programa mesmo assim?\nSeus dados serão perdidos!\n");
            printf("[y - n]");
            scanf(" %c", &option);
            option = tolower(option);
            if(option == 'n'){
                option = 'y';
                printf("\n\nVocê será redirecionado para a aba principal do programa...\n\n");
                }
        }
        }

    }while(option == 'y');
    return 0;

}
