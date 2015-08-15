#include <stdio.h>
#include <stdlib.h>
#include "379948_380385_ED2_T02.h"


int main()
{
  int tam = 0; // tamanho da arvore B primeiro input do usuario;
  int opc = 0;
  int rrn = 0;
  arvoreB *arv=NULL;
  scanf("%d%*c",&tam);

  //le banco de dados e cria arvore B
  arv = inicia_arvore(arv,&rrn,tam);



  do{
  printf("Qual a opcao ?");
   scanf("%d%*c",&opc);    
	switch(opc){            
	case 1: busca_registro(arv);
	break;
	case 2: arv = insere_reg(&rrn,arv,tam);
	break;
	case 3: altera(arv);

	break;
	case 4: //Finaliza

	break; 
	default:
			printf("Opcao Invalida");
	break; 
   } 
  }while(opc!=4);

  return 0;
}