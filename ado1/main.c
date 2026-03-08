#include <stdio.h>
#include <stdbool.h>
#include "neander.h"

int main(int argc, char *argv[]){
    if(argc < 2){ //Checa se recebeu o arquivo do programa
        printf("Sintaxe incorreta. Deve-se seguir o modelo: %s programa.bin [--hex | --dec]\n", argv[0]);
        return 1;
    }

    int modoHex = 0;

    if(argc >= 3 && strcmp(argv[2], "--hex") == 0){ //Ativa o modo hexadecimal se forem = 0
        modoHex = 1;
    }

    neander n;
    iniciarNeander(&n);

    if(!carregarPrograma(&n, argv[1])){
        printf("Erro ao carregar o arquivo\n");
        return 1;
    }

    printf("Memória antes: \n");
    printMemoria(n.memoriaOrig, modoHex);

    printf("Memória depois: \n");
    printMemoria(n.memoria, modoHex);

    printEstado(&n, modoHex);

    return 0;


}