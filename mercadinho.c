#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//criação do tipo de dado Produto
typedef struct {
    int quantidade; //quantiade do produto no estoque
    double preco; //preço do produto
    char nome[100]; //nome do produto
} Produto;
 
void inserir_produto(Produto *estoque, int *n);

void aumentar_estoque(Produto *estoque);

void modificar_preco(Produto *estoque);

void venda(Produto *estoque, double *saldo);

void consultar_estoque(Produto *estoque, int n);

void consultar_saldo(double saldo);

void aloca(Produto **v, int n);

void aloca(Produto **v, int n){
    *v = (Produto *) malloc(sizeof(Produto) * n); //alocar memória para o número de produtos que pode ter no estoque
}

void inserir_produto(Produto *estoque, int *n){
    printf("akjsvdaksvkajs\n");
    printf("%d\n", *n);
    Produto produto_tmp; //criar o nosso produto

    scanf(" %s %d %lf", produto_tmp.nome, &produto_tmp.quantidade, &produto_tmp.preco); //ler as informações do produto

    estoque[*n] = produto_tmp; //inserir o nosso produto no estoque no index n 
    
    *n = *n + 1; //aumentar o número de produtos no estoque atual por 1

    for (int i = 0; i < *n; i++){
        printf("%s %d %lf\n", estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
    }
}

void aumentar_estoque(Produto *estoque){
    int codigo, quantidade;

    scanf(" %d %d", &codigo, &quantidade); //ler o código do produto a ter a quantidade alterada e o valor a ser somado

    estoque[codigo].quantidade += quantidade; //aumentar a quantidade no estoque
}

void modificar_preco(Produto *estoque){
    int codigo;
    double preco;

    scanf(" %d %lf", &codigo, &preco); //ler o código do produto a ter o preço alterado e o preço

    estoque[codigo].preco = preco; //alterar o preço
}

void venda(Produto *estoque, double *saldo){
    int codigo;
    double total = 0.0;

    scanf(" %d", &codigo);

    while (codigo != -1){
        estoque[codigo].quantidade --; //diminuir a quantidade do produto no estoque por 1

        printf("%s %.2lf\n", estoque[codigo].nome, estoque[codigo].preco);

        total += estoque[codigo].preco;

        scanf(" %d", &codigo);
    }

    printf("Total: %.2lf", total);

    printf("--------------------------------------------------\n");

    *saldo += total;
}

void consultar_estoque(Produto *estoque, int n){
    for (int i = 0; i < n; i++){
        printf("%d %s %d\n", i, estoque[i].nome, estoque[i].quantidade);
    }

    printf("--------------------------------------------------\n");
}

void consultar_saldo(double saldo){
    printf("Saldo: %lf\n", saldo);

    printf("--------------------------------------------------\n");
}

int main(int argc, char argv[]){
    Produto * estoque; //o estoque vai ser um vetir de produtos

    double saldo = 100.0;

    int quantidade_de_produtos_no_estoque_atual = 0;

    //a função atoi passa o argumento que inicialmente é uma string para inteiro
    aloca(&estoque, atoi(argv)); //chamar a função para alocar memória

    char comando[2]; //array que vai receber o comando que o programa deve executar

    scanf(" %s", comando); //lendo o comando

    while (comando != "FE"){ //enquanto o comando não for "FE" o programa deve ficar rodando
        //switch para saber qual função rodar
        //ele será divido em duas partes para analisar o comando, formado por duas letras, por completo
        switch (comando[0]){
            case 'I': inserir_produto(estoque, &quantidade_de_produtos_no_estoque_atual);
                break;  
            case 'A': aumentar_estoque(estoque);
                break;
            case 'M': modificar_preco(estoque);
                break;
            case 'V': venda(estoque, &saldo);
                break;
            case 'C': 
                switch (comando[1]){
                    case 'E': consultar_estoque(estoque, quantidade_de_produtos_no_estoque_atual);
                        break;
                    case 'S': consultar_saldo(saldo);
                        break;
                }
        }

        scanf(" %s", comando);
    }
}