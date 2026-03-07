#include <stdio.h>
#include <string.h>
#include <neander.h>

static uint8_t lerMem(neander *n, uint8_t posMem){  
    n -> acessosMem++;
    return n -> memoria[posMem];
}

static void escreverMem(neander *n, uint8_t posMem, uint8_t val){
    n -> acessosMem++;
    n -> memoria[posMem] = val;
}

static void atualizarFlags(neander *n){
    n -> flagZero = (n -> acc == 0); //Verifica se o acumulador é igual a 0
    n -> flagNegativa = (n -> acc & 0x80) != 0; //Faz uma comparação bit a bit com o MSB(0x80)
}

void iniciarNeander(neander *n){
    memset(n->memoria, 0, TAM_MEM); //Zera a memória devido ao lixo
    memset(n->memoriaOrig, 0, TAM_MEM);

    n -> acc = 0;
    n -> pc = 0;
    n -> flagNegativa = 0;
    n -> flagZero = 0;
    n -> acessosMem = 0;
    n -> instrucoesExecutadas = 0;
}

int carregarPrograma(neander *n, const char *file){
    FILE *f = fopen(file, "rb");
    if(!f){
        printf("Erro ao abrir o arquivo");
        return 0;
    }

    fread(n -> memoria, sizeof(uint8_t), TAM_MEM, f);
    fclose(f);

    memcpy(n -> memoriaOrig, n -> memoria, TAM_MEM);

    return 1;
}

void executarPrograma(neander *n){

    int rodando = 1;

    while(rodando){
        uint8_t instrucao = lerMem(n, n -> pc++); //Passa o computador com o PC atual e avança o mesmo em 1
        n -> instrucoesExecutadas++;

        switch(instrucao){ //Baseado nos mnemônicos do Neander
            case 0: //NOP 
                break;
            case 32: //LDA
                uint8_t address = lerMem(n, n -> pc++);
                n -> acc = lerMem(n, address);
                atualizarFlags(n);
                break;
            case 16: //STA
                uint8_t address = lerMem(n, n -> pc++);
                escreverMem(n, address);
                break;
            case 48: //ADD
                uint8_t address = lerMem(n, n -> pc++);
                n -> acc = lerMem(n, address);
                atualizarFlags(n);
                break;
            case 64: //OR
                uint8_t adress = lerMem(n, n -> pc++);
                n -> acc |= lerMem(n, address);
                atualizarFlags(n);
                break;
            case 80: //AND
                uint8_t adress = lerMem(n, n -> pc++);
                n -> acc &= lerMem(n, address);
                atualizarFlags(n);
                break;
            case 96: //NOT
                n -> acc = ~n ->acc; //"~": bitwise operator para negar os bits
                atualizarFlags(n);
                break;
            case 128: //JMP(sem condições)
                uint8_t adress = lerMem(n, n -> pc++);
                n -> pc = address;
                break;
            case 144: //JN(condicional negativo)
                int8_t adress = lerMem(n, n -> pc++);
                if(n -> flagNegativa){
                    n -> pc = adress;
                }
                break;
            case 160: //JZ(condicional zero)
                int8_t adress = lerMem(n, n -> pc++);
                if(n -> flagZero){
                    n -> pc = adress;
                }
                break;
            case 240: //HLT
                rodando = 0;
                break;
            default:
                printf("Instrução não reconhecida: %u", instrucao); //"%u": unsigned
                rodando = 0;
        }   
    }
}

void printEstado(neander *n, int modoHex){
    printf("Estado final da máquina:\n");

    if(modoHex){ //Imprime com um mínimo de 2 digitos em hexadecimal
        printf("Acumulador: 0x%02X\n", n -> acc); 
        printf("Program counter: 0x%02X\n", n -> pc);
    }else{
        printf("Acumulador: %d\n", (int8_t)n -> acc);
        printf("Program counter: %d\n", n -> pc);
    }
}