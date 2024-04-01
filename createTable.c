#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * escrever_cabecario(char *arquivo, int status, long int topo, long int proxByteOffset, int nroRegArq, int nroRegRem){
    FILE *arquivo_bin;

    arquivo_bin = fopen(arquivo, "r+b");

    if (arquivo_bin == NULL) {
        arquivo_bin = fopen(arquivo, "wb");

        if (arquivo_bin == NULL) printf("Não foi possível abrir o arquivo");
    }

    fwrite(&status, 4, 1, arquivo_bin); //escrever o status (4 bytes)
    fwrite(&topo, 8, 1, arquivo_bin); //escrever o topo (8 bytes)
    fwrite(&proxByteOffset, 8, 1, arquivo_bin); //escrever o proxByteOffset (8 bytes)
    fwrite(&nroRegArq, 4, 1, arquivo_bin); //escrever o nroRegArq (4 bytes)
    fwrite(&nroRegRem, 4, 1, arquivo_bin); //escrever o nroRegRem (4 bytes)
    
    return arquivo_bin; //retornar o ponteiro para o arquivo
}

int ler_arquivo(char *arquivo_entrada, FILE *arquivo_bin){
    /*Essa função le os registros do arquivo de entrada (csv) e coloca eles no arquivo de saida(bin)
    Ela retorna o número de registros que foram lidos
    */
    FILE *arquivo_csv;

    char linha[1024];

    arquivo_csv = fopen(arquivo_entrada, "r"); //abrir o arquivo csv em modo de leitura
    if (arquivo_csv == NULL) printf("Não foi possível abrir o arquivo");

    fgets(linha, 1024, arquivo_csv); //ler a primeira linha e ignora-la (cabecalho)

    int qtd_registros = 0;

    //declarar as variaveis necessárias para cada registro
    int id;
    int idade;
    char *nomeJogador;
    char *nacionalidade;
    char *nomeClube;

    while (fgets(linha, 1024, arquivo_csv)){ //ler todas as linhas restantes do arquivo
        qtd_registros ++; //aumentar a quantidade de registros

        id = atoi(strtok(linha, ",")); //ler o id
        idade = atoi(strtok(NULL, ",")); //ler a idade
        nomeJogador = strtok(NULL, ","); //ler o nome do jogador
        nacionalidade = strtok(NULL, ","); //ler a nacionalidade do jogador
        nomeClube = strtok(NULL, ","); //ler o nome do clube do jogador

        //contem o tamanho do registro
        int tamanho_registro = 1 + 4 + 8 + 4 + 4 + 4 + (sizeof(nomeJogador) - 1) + 4 + (sizeof(nacionalidade) - 1) + 4 + (sizeof(nomeClube) - 1);

        int temporario; //para poder colocar valores como 0 e -1 no arquivo binario

        temporario = 0; fwrite(&temporario, 1, 1, arquivo_bin); //se está removido ou nao (1 byte)

        fwrite(&tamanho_registro, 4, 1, arquivo_bin); //tamanho do registro (4 bytes)

        temporario = -1; fwrite(&temporario, 8, 1, arquivo_bin); //proximo byte offset (8 bytes)

        fwrite(&id, sizeof(int), 1, arquivo_bin); //escrever o id (4 bytes)

        fwrite(&idade, sizeof(int), 1, arquivo_bin); //escrever a idade (4 bytes)

        temporario = strlen(nomeJogador); fwrite(&temporario, 4, 1, arquivo_bin); //tamNomeJog (4 bytes)
        fwrite(nomeJogador, sizeof(char), sizeof(nomeJogador) - 1, arquivo_bin); //escrever o nome do jogador (n bytes)

        temporario = strlen(nacionalidade); fwrite(&temporario, 4, 1, arquivo_bin); //tamNacionalidade (4 bytes)
        fwrite(nacionalidade, sizeof(char), sizeof(nacionalidade) - 1, arquivo_bin); //escrever a nacionalidade (n bytes)

        temporario = strlen(nomeClube); fwrite(&temporario, 4, 1, arquivo_bin); //tamNomeClube
        fwrite(nomeClube, sizeof(char), sizeof(nomeClube) - 1, arquivo_bin); //escrever o nome do clube (n bytes)
    }

    //fechar o arquivo csv
    fclose(arquivo_csv);

    return qtd_registros;
}

void createTable(char *arquivo_entrada, char *arquivo_saida){
    FILE *arquivo_bin = escrever_cabecario(arquivo_saida, 0, -1, 0, 0, 0); //escreve o cabecalho

    int qtd_registros = ler_arquivo(arquivo_entrada, arquivo_bin);

    fclose(arquivo_bin); //fecha o arquivo binário que foi aberto na função escrever_cabecario

    fclose(escrever_cabecario(arquivo_saida, 1, -1, 25, qtd_registros, 0));
    /*Ao ler o arquivo csv sabemos que todos os registros lidos nele não foram removidos
    Logo, a quantidade de registros removidos é 0.
    Como todos os registros lidos não estão removidos o primeiro byte Ofsset está logo após o csabecario (byte 25)*/
}   

void main(){
    createTable("dado1.csv", "saida.bin");
}