#include <stdio.h>
#include <stdlib.h>

//criação do tipo de dado Produto
typedef struct {
    int codigo; //código do prudto (entre 0 e 99)
    int quantidade; //quantiade do produto no estoque
    float preco; //preço do produto
} Produto;
 
int inserir_produto();

void aloca(char **v);

void aloca(char **v){
    
}

int main(int argc, char argv[]){
    aloca(&argv);

    char comando[2]; //array que vai receber o comando que o programa deve executar

    scanf(" %s", comando); //lendo o comando

    while (comando != "FE"){ //enquanto o comando não for "FE" o programa deve ficar rodando
        //switch para saber qual função rodar
        //ele será divido em duas partes para analisar o comando, formado por duas letras, por completo
        switch (comando[0]){
            case 'I': inserir_produto();
                break;  
            case 'A'  : 
        }
    }
}