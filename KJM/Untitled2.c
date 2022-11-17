#include <stdio.h>
#include <string.h>

int main(){

    FILE *file;
    file = fopen("./EMP/YOKI.txt", "r");
    char string[100], cod[30] = {"57891095300377\n"}, desc[100];
    int i = 0;
    if(file)
        while(fgets(string, 100, file)){
            i++;
            if(strcmp(string, cod) == 0){
                fgets(desc, 100, file);
                printf("%s\n", desc);
            }

        }
    fclose(file);
    return 0;
}
