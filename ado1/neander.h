#ifndef NEANDER_H
#define NEANDER_H
#define TAM_MEM 256 //Padrão do Neander

#include <stdint.h> //Necessário para utilizarmos variáveis com 8 bits

typedef{
    //Memória:
    uint8_t memoria[TAM_MEM]; 
    uint8_t memoriaOrig[TAM_MEM]; 

    //AC e PC:
    uint8_t acc;
    uint8_t pc;

    //Flags:
    uint8_t flagNegativa;
    uint8_t flagZero;

    //Acessos e instruções:
    uint32_t acessosMem;
    uint32_t instruçõesExecutadas;
}neander;

//Definição das funções:
void iniciarNeander(neander *arg);
void executarPrograma(neander *programa);
void printEstado(neander *arg, int modo); //"modo" deve ser hexa ou dec
void printMemoria(uint8_t *mem, int modo);
int carregarPrograma(neander *programa, const char *file);

#endif
