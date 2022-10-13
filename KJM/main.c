#include <stdio.h>
#include <stdlib.h>
#include "Header1.h"
int main()
{
    Lista Estoque;
    CriaLista(&Estoque);
    int acao = 0;
    char option = ' ';

    printf("*********************************************************\n");
    printf("\tBem vindo ao KJM - Soluções em Armazenamento\n");

    do{
        printf("O que você deseja fazer?\n");
        printf("1 - ADICONAR PRODUTO\n2 - REMOVER PRODUTO\n3 - MOSTRAR ESTOQUE\n4 - CONSULTAR VALIDADE\n");
        scanf("%d", &acao);
        switch (acao){
            case 1:
                printf("\tAdicionando produtos...\n");
                AdicionandoProduto(&Estoque);
                break;
            case 2:
                printf("\tRemovendo Produtos...\n");
                RemovendoProduto(&Estoque);
                break;
            case 3:
                Mostra(Estoque);
                break;
        }
        printf("Desjea continuar no programa? [ y - n ]: ");
        scanf("%s", &option);
    }while(option == 'y');
    return 0;
}
