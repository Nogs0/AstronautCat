#include <stdio.h>
#include <string.h>

int main(){
    char nome[50] = {};

    FILE *arquivo;
    arquivo = fopen("./EMP/YOKI.txt", "r");
    if (arquivo){
        //for (int kj = 0; kj <= 14; kj++)
        do {
        fgets(nome, 50, arquivo);

        printf("%s", nome);
        memset(nome, '\0', 50);
        } while (arquivo != EOF);

    }

}
