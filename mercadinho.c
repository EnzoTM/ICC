/*
Projeto final: Mercadinho
Alunos:
*Enzo Tonon Morente - 14568476
*Thales Sena - 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "estoque.dat"

//criação do tipo de dado Produto
typedef struct {
    int quantidade; //quantidade do produto no estoque
    double preco; //preço do produto
    char nome[100]; //nome do produto
} Produto;

//---------------Prototipos begin
void inserir_produto(Produto **estoque, int *n, int total_de_produtos);

void aumentar_estoque(Produto *estoque);

void modificar_preco(Produto *estoque);

void venda(Produto *estoque, double *saldo);

void consultar_estoque(Produto *estoque, int n);

void consultar_saldo(double saldo);

void aloca(Produto **v, int n);

void ler_arquivo(Produto **estoque, FILE *fp, int *total_de_produtos, int *quantidade_de_produtos_no_estoque_atual, double *saldo);

void salvar(FILE *fp, int *quantidade_de_produtos_no_estoque_atual, double *saldo, Produto **estoque);
//-----------------Prototipos end

void aloca(Produto **v, int n){
    *v = (Produto *) malloc((sizeof(Produto) * n) + (sizeof(Produto) * 10)); //alocar memória para o número de produtos que pode ter no estoque + 10
}

void inserir_produto(Produto **estoque, int *n, int total_de_produtos){
    Produto produto_tmp; //produto auxiliar

    scanf(" %s %d %lf", produto_tmp.nome, &produto_tmp.quantidade, &produto_tmp.preco); //ler as informações do produto

    if (*n + 1 >= total_de_produtos){ //se a quantidade de produtos atualmente no estoque for maior do que a quantidade de produtos inicilamente alocada
        *estoque = realloc(*estoque, (*n + 1)*sizeof(Produto));
    }

    (*estoque)[*n] = produto_tmp; //inserir o nosso produto no estoque no index n 
    
    *n +=  1; //aumentar o número de produtos no estoque atual por 1
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
        if (estoque[codigo].quantidade > 0){ //so pode realizar a venda se existir produto no estoque
            estoque[codigo].quantidade --; //diminuir a quantidade do produto no estoque por 1

            printf("%s %.2lf\n", estoque[codigo].nome, estoque[codigo].preco);

            total += estoque[codigo].preco; //agregar o valor do produto vendido no total da compra
        }

        scanf(" %d", &codigo);
    }

    printf("Total: %.2lf\n", total);

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
    printf("Saldo: %.2lf\n", saldo);

    printf("--------------------------------------------------\n");
}

void ler_arquivo(Produto **estoque, FILE *fp, int *total_de_produtos, int *quantidade_de_produtos_no_estoque_atual, double *saldo){
    //ler o arquivo conforme sua organização
    fread(total_de_produtos, sizeof(int), 1, fp); //ler a primeira parte do arquivo, que será a quantidade de produtos presente no mesmo

    *quantidade_de_produtos_no_estoque_atual = *total_de_produtos; //como iremos receber todos os produtos no estoque do arquivo, no fim de sua leitura, a quantidade de produtos contidos no estoque atualmente vai ser a quantidade máxima de prodtuos no estoque

    fread(saldo, sizeof(double), 1, fp); //ler a segunda parte do arquivo, quer será o saldo 

    aloca(estoque, *total_de_produtos); //alocar dinamicamente o número total de produtos que se tem no estoque

    //o resto do arquivo será cada item do vetor estoque de tamanho total_de_produtos
    fread(*estoque, sizeof(Produto), *total_de_produtos, fp);

    fclose(fp); //fechar o arquivo
}

void salvar(FILE *fp, int *quantidade_de_produtos_no_estoque_atual, double *saldo, Produto **estoque){
    fp = fopen(ARQUIVO, "wb"); //abrir o arquivo em modo de escrita

    fwrite(quantidade_de_produtos_no_estoque_atual, sizeof(int), 1, fp); //escrever a quantidade total de produtos que se tem no estoque, que neste caso, é o número de produtos no estoque

    fwrite(saldo, sizeof(double), 1, fp); //escrever o salário

    fwrite(*estoque, sizeof(Produto), *quantidade_de_produtos_no_estoque_atual, fp); //escrever todos os produtos do estoue no arquivo
}

int main(void){
    FILE *fp; //declarar o ponteiro que irá apontar para o arquivo referente ao estoque

    double saldo; //declarar a variavel do saldo

    int total_de_produtos; //declarar a variavel para saber a quantidade de produtos que se tem no total no estoque

    int quantidade_de_produtos_no_estoque_atual; //declarar a variavel referente a quantidade de produtos no estoque no momento atual da execução do programa

    fp = fopen(ARQUIVO, "rb"); //tentar abrir o arquivo de estoque

    Produto *estoque; //o estoque vai ser um vetor de produtos
    
    if (fp == NULL){ //se o arquivo nao existir
        //fp = fopen(ARQUIVO, "wb"); //abrir (criar) o arquivo em modo de escrita
        
        scanf("%d", &total_de_produtos); //ler a quantidade de produtos iformadas pelo usuário já que não se tem um arquivo com as informações necessárias

        scanf("%lf", &saldo); //ler o saldo informado pelo usuário já que não se tem um arquivo com as informações necessárias

        aloca(&estoque, total_de_produtos); //alocar dinamicamente o número total de produtos que se tem no estoque

        quantidade_de_produtos_no_estoque_atual = 0; //como nenhum produto foi informado, a quantidade de produtos no estoque atual é 0
    }else {
        //se tiver um arquivo, le-lo
        ler_arquivo(&estoque, fp, &total_de_produtos, &quantidade_de_produtos_no_estoque_atual, &saldo);
    }

    char comando[2]; //array que vai receber o comando que o programa deve executar

    scanf(" %s", comando); //lendo o comando

    while (comando[0] != 'F'){ //enquanto o comando não for "FE" o programa deve ficar rodando
        //dependendo da prmeira letra do comando informado executar a devida função
        switch (comando[0]){
            case 'I': inserir_produto(&estoque, &quantidade_de_produtos_no_estoque_atual, total_de_produtos);
                break;  
            case 'A': aumentar_estoque(estoque);
                break;
            case 'M': modificar_preco(estoque);
                break;
            case 'V': venda(estoque, &saldo);
                break;
            case 'C':  //caso a primeira letra do comando seja C, é necessário realizer outro switch, com a segunda letra, para descobrir realmente qual comando devemos executar
                switch (comando[1]){
                    case 'E': consultar_estoque(estoque, quantidade_de_produtos_no_estoque_atual);
                        break;
                    case 'S': consultar_saldo(saldo);
                        break;
                }
        }

        scanf(" %s", comando);
    }

    salvar(fp, &quantidade_de_produtos_no_estoque_atual, &saldo, &estoque);

    free(estoque); //liberar a memoria alocada para o vetor estoque

    return 0;
}
