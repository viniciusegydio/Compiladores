#ifndef NEANDER_H
#define NEANDER_H
#define TAM_MEM 256 //Padrão do Neander

#include <stdint.h> //Necessário para utilizarmos variáveis com 8 bits                                                                              

typedef struct{
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
    uint32_t acessosMem;                                                                                                                                                    ;
    uint32_t instrucoesExecutadas;
}neander;

//Definição das funções:   
void iniciarNeander(neander *n);
void executarPrograma(neander *programa);
void printEstado(neander *n, int modoHex); 
void printMemoria(uint8_t *mem, int modoHex);
int carregarPrograma(neander *n, const char *file);

#endif