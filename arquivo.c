#include "metro.h"

int InsereArestaArquivo(FILE *fp, TipoGrafo *Grafo){
	
	int v1, v2;
	TipoPeso peso;

	fp = fopen("insere_aresta.txt","r");
	if(fp == NULL)
		return 0;

	while(!feof(fp)){
  	fscanf(fp, "%d", &v1);
		fscanf(fp, "%d", &v2);
		fscanf(fp, "%f", &peso.distancia);
   	fscanf(fp, "%f", &peso.preco);

   	if(!InsereAresta(Grafo,v1,v2,peso))
   		printf("A aresta dos vertices %d e %d nao foi inserida.\n", v1, v2);
  }

  fclose(fp);
	
	return 1;
}