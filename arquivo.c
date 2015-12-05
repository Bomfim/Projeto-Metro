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

int GravaArestaArquivo(FILE *fp, TipoVertice v1, TipoVertice v2, TipoPeso peso){

	if(peso.distancia == 0 && peso.distancia == 0)
		return 0;

	fp = fopen("insere_aresta.txt","a+");
	if(fp == NULL)
		return 0;

	fprintf(fp, "%d", v1);
	fprintf(fp, "%d", v2);
	fprintf(fp, "%0.2f", peso.distancia);
	fprintf(fp, "%0.2f", peso.preco);

	fclose(fp);

	return 1;
}