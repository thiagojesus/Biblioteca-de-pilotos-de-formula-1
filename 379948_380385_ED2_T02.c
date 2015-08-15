#include "379948_380385_ED2_T02.h"


//busca no vetor do no selecionado o nome do piloto

int buscaVetor(arvoreB *no, char *piloto, int op) {
    int meio, i, f;
    i = 0;
    f = no->num_chaves - 1;

    while (i <= f) {
        meio = (i + f) / 2;
        if (op == 1) printf("%s\n", no->chaves[meio].nome);
        if (strcmp(no->chaves[meio].nome, piloto) == 0)
            return (meio); //Encontrou. Retorna a posíção em que a chave está.
        else if (strcmp(no->chaves[meio].nome, piloto) > 0)
            f = meio - 1;
        else i = meio + 1;
    }
    return (i); //Não encontrou. Retorna a posição do ponteiro para o filho.
}

//busca para encontrar o nó onde o piloto está

int busca(arvoreB *raiz, char *piloto) {
    arvoreB *no;
    int pos; //posição retornada pelo buscaVetor
    no = raiz;
    while (no != NULL) {
        pos = buscaVetor(no, piloto, 1);
        if (pos < no->num_chaves && strcmp(no->chaves[pos].nome, piloto) == 0)
            return (no->chaves[pos].RRN - 1);
        else no = no->filhos[pos];
    }
    return (0);
}

//Insere uma chave no nó indicado pela funcao insere, e o ponteiro para o filho da direita do nó

void insereChave(arvoreB *raiz, piloto info, arvoreB *filhodir) {
    int k, pos;
    //busca para obter a posição ideal para inserir a nova chave
    pos = buscaVetor(raiz, info.nome, 0);
    k = raiz->num_chaves;
    //realiza o remanejamento para manter as chaves ordenadas
    while (k > pos && strcmp(info.nome, raiz->chaves[k - 1].nome) < 0) {
        raiz->chaves[k] = raiz->chaves[k - 1];
        raiz->filhos[k + 1] = raiz->filhos[k];
        k--;
    }
    //insere a chave na posição ideal
    raiz->chaves[pos] = info;
    raiz->filhos[pos + 1] = filhodir;
    raiz->num_chaves++;
}

//busca o no para inserir a chave e faz o split se precisar

arvoreB *insereNo(arvoreB *raiz, piloto info, int *h, piloto *info_retorno, int ordemarv) {
    int i, pos; //auxiliar para armazenar a chave que irá subir para o pai
    piloto info_mediano;
    arvoreB *temp, *filho_dir; //ponteiro para o filho à direita da chave 
    if (raiz == NULL) {
        //O nó anterior é o ideal para inserir a nova chave (chegou em um nó folha)
        *h = 1;
        *info_retorno = info;
        return (NULL);
    } else {
        pos = buscaVetor(raiz, info.nome, 0);
        if (raiz->num_chaves > pos && strcmp(raiz->chaves[pos].nome, info.nome) == 0) {
            printf("Chave já contida na Árvore");
            *h = 0;
        } else {
            //desce na árvore até encontrar o nó folha para inserir a chave.
            filho_dir = insereNo(raiz->filhos[pos], info, h, info_retorno, ordemarv);
            if (*h == 1) //Se true deve inserir a info_retorno no nó.
            {
                if (raiz->num_chaves < ordemarv - 1) //Tem espaço na página
                {
                    insereChave(raiz, *info_retorno, filho_dir);
                    *h = 0;
                } else { //Overflow. Precisa fazer split
                    temp = (arvoreB *) malloc(sizeof (arvoreB));
                    temp->chaves = (piloto*) malloc(ordemarv * sizeof (piloto));
                    temp->filhos = (arvoreB**) malloc(ordemarv * sizeof (arvoreB));
                    //fazer os mallocs da ordemarv
                    temp->num_chaves = 0;
                    //NULL para os novos filhos
                    for (i = 0; i < ordemarv; i++)
                        temp->filhos[i] = NULL;
                    //pega o elemento do meio para subir ao no pai
                    info_mediano = raiz->chaves[(ordemarv / 2) - 1];
                    //insere metade do nó raiz no temp (efetua split)
                    temp->filhos[0] = raiz->filhos[(ordemarv / 2) - 1 + 1];
                    for (i = (ordemarv / 2) - 1 + 1; i < ordemarv - 1; i++)
                        insereChave(temp, raiz->chaves[i], raiz->filhos[i + 1]);
                    //atualiza nó raiz. 
                    for (i = (ordemarv / 2) - 1; i < ordemarv - 1; i++) {
                        memset(raiz->chaves[i].nome, 0, 29);
                        raiz->chaves[i].RRN = 0;
                        raiz->filhos[i + 1] = NULL;
                    }
                    raiz->num_chaves = (ordemarv / 2) - 1;
                    //Verifica em qual nó será inserida a nova chave
                    if (pos <= (ordemarv / 2) - 1)
                        insereChave(raiz, *info_retorno, filho_dir);
                    else insereChave(temp, *info_retorno, filho_dir);
                    //retorna o no do meio para inserir no pai e o temp como filho direito do meio.
                    *info_retorno = info_mediano;
                    return (temp);
                }
            }
        }
    }
    return NULL;
}

//funcao que comanda a inserção na arvore B

arvoreB *inserir(arvoreB *raiz, piloto info, int ordemarv) {
    piloto info_retorno;
    int i, h;
    arvoreB *filho_dir, *nova_raiz;
    filho_dir = insereNo(raiz, info, &h, &info_retorno, ordemarv);
    if (h == 1) { //Aumetará a altura da árvore
        nova_raiz = (arvoreB *) malloc(sizeof (arvoreB));
        nova_raiz->chaves = (piloto*) malloc(ordemarv * sizeof (piloto));
        nova_raiz->filhos = (arvoreB**) malloc(ordemarv * sizeof (arvoreB));
        nova_raiz->num_chaves = 1;
        nova_raiz->chaves[0] = info_retorno;
        nova_raiz->filhos[0] = raiz;
        nova_raiz->filhos[1] = filho_dir;
        for (i = 2; i <= ordemarv - 1; i++)
            nova_raiz->filhos[i] = NULL;
        return (nova_raiz);
    } else return (raiz);
}

//funcao que busca um piloto na arvore B e retorna os dados referentes a ele que estão no arquivo de dados

void busca_registro(arvoreB *arv) {
    char nome[30];
    int pos = 0;
    FILE *arq = NULL;
    int i = 0;
    char string[57];
    char c;
    int rrn = 0;
    char *token = NULL;
    char string_id[5];
    char string_nome[30];
    char string_pais[16];
    char string_tit[2];
    char string_corrida[4];
    char string_poles[3];
    char string_vitorias[3];
    int j = 0;

    arq = fopen("automobilismo.dat", "r");
    if (!arq) {
        exit(-1);
    }
    ler_letra(nome, 29);
    printf("Nome do piloto : %s\n", nome);
    rrn = busca(arv, nome); // a partir do nome echa na arvore o registro e devolve o rrn */
    pos = rrn * 56;
    fseek(arq, pos, SEEK_SET);
    while (i < 56) {
        fscanf(arq, "%c", &c);
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    printf("Dados do piloto procurado:\n");
    j = 0;
    i = 0;
    while (i < 4) {
        string_id[j] = string[i];
        j++;
        i++;
    }
    string_id[5] = '\0';
    printf("ID = %s\n", string_id);
    j = 0;
    while (i < 33) {
        string_nome[j] = string[i];
        j++;
        i++;
    }
    string_nome[30] = '\0';
    token = strtok(string_nome, "#");
    strcpy(token, string_nome);
    printf("Nome = %s\n", string_nome);
    j = 0;
    while (i < 48) {
        string_pais[j] = string[i];
        j++;
        i++;
    }
    string_pais[16] = '\0';
    token = strtok(string_pais, "#");
    strcpy(token, string_pais);
    printf("Pais = %s\n", string_pais);
    j = 0;
    string_tit[j] = string[i];
    string_tit[j + 1] = '\0';
    printf("Qtde Titulos = %s\n", string_tit);
    j = 0;
    i++;
    while (i < 52) {
        string_corrida[j] = string[i];
        i++;
        j++;
    }
    string_corrida[j + 1] = '\0';
    token = strtok(string_corrida, "#");
    strcpy(token, string_corrida);
    printf("Qtde Corridas = %s\n", string_corrida);
    j = 0;
    while (i < 54) {
        string_poles[j] = string[i];
        i++;
        j++;
    }
    string_poles[j + 1] = '\0';
    token = strtok(string_poles, "#");
    strcpy(token, string_poles);
    printf("Qtde Poles = %s\n", string_poles);
    j = 0;
    while (i < 56) {
        string_vitorias[j] = string[i];
        i++;
        j++;
    }
    string_vitorias[j + 1] = '\0';
    token = strtok(string_vitorias, "#");
    strcpy(token, string_vitorias);
    printf("Qtde Vitorias = %s\n", string_vitorias);
}

//funcao que abre o arquivo de dados, coleta os dados e insere cada piloto na arvore B

arvoreB * inicia_arvore(arvoreB * arv, int * rrn, int ordemarv) {
    FILE * arq = NULL;
    char c;
    piloto *p;
    char string[30];
    int i = 0;
    int j = 0;
    int pos = 0;
    int cont = 0;
    char * token;
    arq = fopen("automobilismo.dat", "r");
    if (!arq) {
        exit(-1);
    }
    while (!feof(arq)) {
        i = 0;
        j = 0;
        cont = 0;
        pos = *rrn * 56;
        fseek(arq, pos, SEEK_SET);
        while (!feof(arq) && i < 57) {
            fscanf(arq, "%c", &c);
            if (i < 33) {
                string[i] = c;
            }
            i++;
        }
        string[i] = '\0';
        *rrn = *rrn + 1;

        while (string[cont] != '\0') {
            if (cont >= 4) {
                string[j] = string[cont];
                j++;
            }
            cont++;
        }
        token = strtok(string, "#");
        strcpy(token, string);
        p = (piloto*) malloc(sizeof (piloto));
        strcpy(p->nome, string);
        p->RRN = *rrn;
        arv = inserir(arv, *p, ordemarv);
    }
    fclose(arq);
    *rrn = *rrn + 1;
    return (arv);
}

//funcao que altera alguns dados de um piloto no arquivo de dados

void altera(arvoreB *arv) {
    FILE * arq = NULL;
    char string_piloto[30];
    char string_tit[2];
    char string_corrida[4];
    char string_pole[3];
    char string_vitoria[3];
    int rrn = 0;
    int pos = 0;
    int complete = 0;
    int number = 0;
    int i = 0;
    arq = fopen("automobilismo.dat", "r+");
    if (!arq) {
        exit(-1);
    }
    ler_letra(string_piloto, 29);
    rrn = busca(arv, string_piloto); //funcao pra procurar na arvore B pelo nome e retorar o RRN
    pos = rrn * 56; //Calculo da posicao que o fseek vai ir
    pos = pos + 48; // soma mais 40 para parar na posicao correta
    fseek(arq, pos, SEEK_SET);
    ler_numero(string_tit, 1);
    ler_numero(string_corrida, 3);
    ler_numero(string_pole, 2);
    ler_numero(string_vitoria, 2);
    fprintf(arq, "%s", string_tit); //apenas 1 nao precisa completar
    number = 0;
    complete = 0;
    number = strlen(string_corrida);
    complete = 3 - number;
    fprintf(arq, "%s", string_corrida);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    number = 0;
    complete = 0;
    number = strlen(string_pole);
    complete = 2 - number;
    fprintf(arq, "%s", string_pole);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    number = 0;
    complete = 0;
    number = strlen(string_vitoria);
    complete = 2 - number;
    fprintf(arq, "%s", string_vitoria);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    fclose(arq);
}

//funcao que insere um novo piloto ao fim do arquivo de dados

arvoreB * insere_reg(int *rrn, arvoreB *arv, int ordemarv) {
    char string_id[5];
    char string_piloto[30];
    char string_pais[16];
    char string_tit[2];
    char string_corrida[4];
    char string_pole[3];
    char string_vitoria[3];
    int i = 0;
    int complete = 0;
    int number = 0;
    piloto *p;
    FILE * arq = NULL;
    arq = fopen("automobilismo.dat", "a+");
    if (!arq) {
        exit(-1);
    }
    ler_numero(string_id, 4);
    ler_letra(string_piloto, 29);
    ler_letra(string_pais, 15);
    ler_numero(string_tit, 1);
    ler_numero(string_corrida, 3);
    ler_numero(string_pole, 2);
    ler_numero(string_vitoria, 2);
    number = strlen(string_id);
    complete = 4 - number;
    fprintf(arq, "%s", string_id);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    number = 0;
    complete = 0;
    number = strlen(string_piloto);
    complete = 29 - number;
    fprintf(arq, "%s", string_piloto);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    number = 0;
    complete = 0;
    number = strlen(string_pais);
    complete = 15 - number;
    fprintf(arq, "%s", string_pais);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    fprintf(arq, "%s", string_tit); //apenas 1 nao precisa completar
    number = 0;
    complete = 0;
    number = strlen(string_corrida);
    complete = 3 - number;
    fprintf(arq, "%s", string_corrida);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    number = 0;
    complete = 0;
    number = strlen(string_pole);
    complete = 2 - number;
    fprintf(arq, "%s", string_pole);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    number = 0;
    complete = 0;
    number = strlen(string_vitoria);
    complete = 2 - number;
    fprintf(arq, "%s", string_vitoria);
    for (i = 0; i < complete; i++) {
        fprintf(arq, "%c", '#');
    }
    p = (piloto *) malloc(sizeof (piloto));
    strcpy(p->nome, string_piloto);
    p->RRN = *rrn;
    arv = inserir(arv, *p, ordemarv);
    *rrn = *rrn + 1;
    fclose(arq);
    return (arv);
}

//funcao que le somente numeros

void ler_numero(char string[], int n) {
    int resp = 0;
    int i = 0;
    while ((resp = getchar()) != '\n')
        if (i < n) {
            if (resp != '#' && resp != 'a' && resp != 'b' && resp != 'c' && resp != 'd' && resp != 'e' && resp != 'f' && resp != 'g' && resp != 'h' && resp != 'i' && resp != 'j'
                    && resp != 'k' && resp != 'l' && resp != 'm' && resp != 'n' && resp != 'o' && resp != 'p' && resp != 'q' && resp != 'r' && resp != 's'
                    && resp != 't' && resp != 'u' && resp != 'v' && resp != 'x' && resp != 'w' && resp != 'y' && resp != 'z' && resp != 'A' && resp != 'B' && resp != 'C' && resp != 'D' && resp != 'E'
                    && resp != 'F' && resp != 'G' && resp != 'H' && resp != 'I' && resp != 'J'
                    && resp != 'K' && resp != 'L' && resp != 'M' && resp != 'N' && resp != 'O' && resp != 'P' && resp != 'Q' && resp != 'R' && resp != 'S'
                    && resp != 'T' && resp != 'U' && resp != 'V' && resp != 'X' && resp != 'W' && resp != 'Y' && resp != 'Z') {
                string[i++] = resp;
            }
        }
    string[i] = '\0';
}

//funcao que le somente letras

void ler_letra(char string[], int n) {
    int resp, i = 0;
    while ((resp = getchar()) != '\n')
        if (i < n) {
            if (resp != '#' && resp != '0' && resp != '1' && resp != '2' && resp != '3' && resp != '4' && resp != '5' && resp != '6' && resp != '7' && resp != '8' && resp != '9') {
                string[i++] = resp;
            }
        }
    string[i] = '\0';
}