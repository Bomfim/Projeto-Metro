#include "metro.h"

struct grafo {

    int NumVertices;
    int numArestas;
    TipoPeso **Mat;
};

TipoGrafo *Cria_grafo(int Nvertices) {

    int i, k;
    TipoGrafo *Grafo;

    if (Nvertices <= 0)
        return NULL;
    Grafo = (TipoGrafo *) malloc(sizeof(TipoGrafo));
    if (Grafo == NULL)
        return NULL;
    Grafo->Mat = (TipoPeso **) malloc(Nvertices * sizeof(TipoPeso *));
    if (Grafo->Mat == NULL) {
        free(Grafo);
        return NULL;
    }
    for (i = 0; i < Nvertices; i++) {
        Grafo->Mat[i] = (TipoPeso *) calloc(Nvertices, sizeof(TipoPeso));
        if (Grafo->Mat[i] == NULL) {
            for (k = 0; k < i; k++)
                free(Grafo->Mat[k]);
        }
    }
    return Grafo;
}

int InsereAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2, TipoPeso peso) {

    if (Grafo == NULL)
        return -1;  //GRAFO NÃO EXISTE

    if ((Grafo->Mat[v1][v2].distancia != 0 && Grafo->Mat[v1][v2].preco != 0) || (peso.distancia == 0 && peso.distancia == 0))
        return 0;   //JÁ EXISTE ARESTA ENTRE V1 E V2

    Grafo->Mat[v1][v2] = peso;
    Grafo->numArestas++;
    return 1;
}

int ExisteAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2) {

    if (Grafo == NULL)
        return -1;

    if (Grafo->Mat[v1][v2].distancia == 0 && Grafo->Mat[v1][v2].preco == 0)
        return 0;

    return 1;
}

int RetiraAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2) {

    if (Grafo == NULL)
        return -1;

    if (Grafo->Mat[v1][v2].distancia == 0 && Grafo->Mat[v1][v2].preco == 0)
        return 0;

    Grafo->Mat[v1][v2].distancia = 0;
    Grafo->Mat[v1][v2].preco = 0;

    Grafo->numArestas--;
    return 1;
}

int ConsultaAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2, TipoPeso *peso) {

    if (Grafo == NULL)
        return -1;

    if (Grafo->Mat[v1][v2].distancia == 0 && Grafo->Mat[v1][v2].preco == 0)
        return 0;

    *peso = Grafo->Mat[v1][v2];
    return 1;
}

void MostraListaAdjacentes(TipoGrafo *Grafo, TipoVertice v) {

    int i, flag = 0;

    if (Grafo == NULL)
        return;

    else {
        printf("Lista de Adjacentes à %d :\n", v);
        for (i = 0; i < Grafo->NumVertices; i++) {

            if (Grafo->Mat[i] != 0) {
                printf("%d (distancia: %0.2f; preco: %0.2f)\n", i, Grafo->Mat[v][i].distancia, Grafo->Mat[v][i].preco);
                flag = 1;
            }
        }
        if (flag == 0)
            printf("Vertice %d nao possui vertices adjacentes\n", v);
    }
}

void MostraGrafo(TipoGrafo *Grafo) {


    int i,j,flag=0;
    if (Grafo == NULL || Grafo->numArestas == 0) {
        printf("Grafo nao existe ou nao possui arestas\n");
    }

    else {
        for (i = 0; i < Grafo->NumVertices; i++) {
            printf("%d -> ", i);
            for (j = 0; j < Grafo->numArestas; j++) {
                if (Grafo->Mat[i][j].distancia != 0 && Grafo->Mat[i][j].preco != 0) {
                    printf("%d (distancia: %0.2f; preco: %0.2f)\n", j, Grafo->Mat[i][j].distancia, Grafo->Mat[i][j].preco);
                    flag = 1;
                }
            }
            if(flag==0)
                printf("Grafo nao possui vertices adjacentes\n");
        }
    }
}

TipoGrafo *LiberaGrafo(TipoGrafo *Grafo) {

    int i;
    if(Grafo == NULL)
        return NULL;

    for (i = 0; i < Grafo->NumVertices; i++) {
        free(Grafo->Mat[i]);
    }
    free(Grafo->Mat);
    free(Grafo);

    return NULL;
}
