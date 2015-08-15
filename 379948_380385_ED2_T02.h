//prototipos da struct e das funcoes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct piloto{
	char nome[30];
	int RRN;
}piloto;

typedef struct no_arvoreB arvoreB;

struct no_arvoreB {
   int num_chaves; //Quantidades de chaves contida no nó
   piloto *chaves; //Chaves armazenadas no nó
   arvoreB **filhos; //Ponteiro para os filhos
};


//funcao para ler textos sem numero
void ler_letra(char string[],int n);

//funcao para ler os numeros sem letras
void ler_numero(char string[],int n);

//funcao que inicializa a arvore e adiciona os pilotos nela
arvoreB * inicia_arvore(arvoreB * arv, int * rrn, int ordemarv);

//funcao que percorre os nos um a um fazendo busca binaria nos vetores de cada um para encontrar o piloto
int buscaVetor(arvoreB *no, char *piloto, int op);

//funcao que busca um piloto no arquivo e retorna seu RRN
int busca(arvoreB *raiz, char *piloto);

//funcao que adiciona uma struct piloto na arvore e cria seu filho da direita
void insereChave(arvoreB *raiz, piloto info, arvoreB *filhodir);

//funcao que altera alguns valores do piloto diretamente no arquivo
void altera(arvoreB *arv);

//funcao que localiza a folha na qual o piloto deve ser inserido
arvoreB *insereNo(arvoreB *raiz, piloto info, int *h, piloto *info_retorno, int ordemarv);

//funcao que comanda a inserção na arvore B
arvoreB *inserir(arvoreB *raiz, piloto info, int ordemarv);

//funcao que busca um piloto
void busca_registro(arvoreB *arv);

//funcao que insere um novo piloto no arquivo e na arvore
arvoreB * insere_reg(int *rrn, arvoreB *arv,int ordemarv);

//funcao para desalocar a memoria
void encerrar(arvoreB *arv);