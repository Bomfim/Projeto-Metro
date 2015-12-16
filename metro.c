#include "metro.h"

struct grafo {

    int NumVertices;
    int NumArestas;
    int *verticesDesativados;                               //vetor de estações desativadas
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

    Grafo->verticesDesativados =(int *) malloc(Nvertices * sizeof(int));
    if (Grafo->verticesDesativados == NULL) {
        free(Grafo);
        return NULL;
    }

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

    Grafo->NumVertices = Nvertices;
    Grafo->NumArestas = 0;

    for(i = 0; i < Grafo->NumVertices; i++){
        Grafo->verticesDesativados[i] = 1;
    }

    return Grafo;
}

int InsereAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2, TipoPeso peso) {

    if (Grafo == NULL)
        return -1;  //GRAFO NÃO EXISTE

    if ((Grafo->Mat[v1-1][v2-1].distancia != 0 && Grafo->Mat[v1-1][v2-1].preco != 0) || (peso.distancia == 0 && peso.preco == 0))
        return 0;   //JÁ EXISTE ARESTA ENTRE V1 E V2

    Grafo->Mat[v1-1][v2-1] = peso;
    Grafo->Mat[v2-1][v1-1] = peso;
    Grafo->NumArestas++;

    return 1;
}

int ExisteAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2) {

    if (Grafo == NULL)
        return -1;

    if (Grafo->Mat[v1-1][v2-1].distancia == 0 && Grafo->Mat[v1-1][v2-1].preco == 0)
        return 0; //NÃO EXISTE ARESTA LIGANDO V1 E V2

    return 1; //EXISTE ARESTA!
}

int RetiraAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2) {

    if (Grafo == NULL)
        return -1;

    if (Grafo->Mat[v1-1][v2-1].distancia == 0 && Grafo->Mat[v1-1][v2-1].preco == 0)
        return 0; // ARESTA NÃO EXISTE

    Grafo->Mat[v1-1][v2-1].distancia = 0; // REMOVENDO ARESTA
    Grafo->Mat[v1-1][v2-1].preco = 0;

    Grafo->Mat[v2-1][v1-1].distancia = 0; // REMOVENDO ARESTA
    Grafo->Mat[v2-1][v1-1].preco = 0;

    Grafo->NumArestas--;
    return 1;
}

int ConsultaAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2, TipoPeso *peso) {

    int i;

    if (Grafo == NULL)
        return -1;

    if (Grafo->Mat[v1-1][v2-1].distancia == 0 && Grafo->Mat[v1-1][v2-1].preco == 0)
        return 0;

    *peso = Grafo->Mat[v1-1][v2-1];
    return 1;
}

void MostraListaAdjacentes(TipoGrafo *Grafo, TipoVertice v) {

    int i, flag = 0;

    if (Grafo == NULL)
        return;

    else {
        printf("Lista de Adjacentes à %d :\n", v);
        for (i = 0; i < Grafo->NumVertices; i++) {

            if (Grafo->Mat[v-1][i].distancia != 0 && Grafo->Mat[v-1][i].preco != 0 ) {
                printf("Vertice: %d (Distancia: %0.2f; Preco: %0.2f)\n", i+1, Grafo->Mat[v-1][i].distancia, Grafo->Mat[v-1][i].preco);
                flag = 1;
            }
        }
        if (flag == 0)
            printf("Vertice %d nao possui vertices adjacentes\n", v);
    }
}

void MostraGrafo(TipoGrafo *Grafo) {


    int i, j, flag = 0;
    if (Grafo == NULL || Grafo->NumArestas == 0) {
        printf("Grafo nao existe ou nao possui arestas\n");
    }

    else {
        for (i = 0; i < Grafo->NumVertices; i++) {

            flag = 0;
            printf("Estacao : %d \n", i+1);

            for (j = 0; j < Grafo->NumVertices; j++) {
                if (Grafo->Mat[i][j].distancia != 0 && Grafo->Mat[i][j].preco != 0) {
                    printf("%d (Distancia: %0.2f; Preco: %0.2f)\n", j+1, Grafo->Mat[i][j].distancia,
                           Grafo->Mat[i][j].preco);
                    flag = 1;
                }
            }
            if (flag == 0)
                printf("Grafo nao possui vertices adjacentes\n");

            printf("-------------------------------------------\n");
        }
    }

}

TipoGrafo *LiberaGrafo(TipoGrafo *Grafo) {

    int i;
    if (Grafo == NULL)
        return NULL;

    for (i = 0; i < Grafo->NumVertices; i++) {
        free(Grafo->Mat[i]);
    }
    free(Grafo->Mat);
    free(Grafo);

    return NULL;
}

void Caminho_mais_Curto(TipoGrafo *Grafo, int origem, int destino) {
    origem--;
    destino--;

    int vert,i, k;
    float NovaDist,min;
    int *M = (int *) malloc(Grafo->NumVertices * sizeof(int));
    float *L = (float *) malloc(Grafo->NumVertices * sizeof(float));
    int *A = (int *) malloc(Grafo->NumVertices * sizeof(int));
    int *caminho = (int *) malloc(Grafo->NumVertices * 3 * sizeof(int));

    //INICIALIZANDO VARIÁVEIS
    for (int i = 0; i < Grafo->NumVertices; i++) {
        M[i] = 0;       //FALSE - DETERMINA SE UM VÉRTICE JÁ FOI VISITADO
        A[i] = -1;      // DETERMINA O CAMINHO MAIS CURTO ENTRE ORIGEM E DESTINO
        L[i] = FLT_MAX;
    }

    vert = origem;
    L[vert] = 0;

    while (vert != destino && vert != -1) {                         // NÃO TERMINOU OU CAMINHO INEXISTENTE

        for (i = 0; i < Grafo->NumVertices; i++) {              // PERCORRE VERTICES ADJACENTES DE VERT

            if (Grafo->Mat[vert][i].distancia != 0 && M[i] == 0) {  // SE ARESTA EXISTE E ELA NÃO FOI VISITADA

                NovaDist = (L[vert] + Grafo->Mat[vert][i].distancia);

                if (NovaDist < L[i]) {
                    L[i] = NovaDist;                                // ATUALIZA MENOR DISTANCIA
                    A[i] = vert;                                    // ATUALIZA CAMINHO
                }
            }
        }

        M[vert] = 1;    //TODA A LISTA DE ADJACENTES DE VERT JÁ FOI ANALISADA
        min = FLT_MAX;  //MAIOR FLOAT POSSIVEL
        vert = -1;      //VALOR INVÁLIDO

        for (i = 0; i < Grafo->NumVertices; i++) {  //ENCONTRA PRÓXIMO VERTICE DO CAMINHO

            if (M[i] == 0 && L[i] < min) {          // ESCOLHE O VERTICE CUJA ARESTA POSSUI O MENOR PESO

                min = L[i];
                vert = i;
            }
        }
    }

    //LISTAR O CAMINHO MAIS CURTO ENTRE ORIGEM E DESTINO

    if (vert == destino) {  //ENCONTROU UM CAMINHO

        printf("Caminho mais curto entre %d e %d tem comprimento %0.2f:\n", origem+1, destino+1, L[destino]);

        caminho[0] = destino;
        k = 1;

        while (vert != origem) {
            caminho[k] = A[vert];
            vert = A[vert];
            k++;
        }
        for (i = k - 1; i >= 0; --i) {
            if(i != 0)
                printf("%d->", caminho[i]+1);
            else
                printf("%d", caminho[i]+1);
        }
    }
    else
        printf("Nao existe caminho entre %d e %d\n", origem, destino);
}

int DesativaVertice(TipoGrafo* Grafo, TipoVertice v){
    if (Grafo == NULL)
        return -1;

    if (Grafo->verticesDesativados[v-1] == 0) // VERTICE JÁ ESTÁ DESATIVADO
        return 0;

    Grafo->verticesDesativados[v-1] = 0;

    return 1;
}


void VerticesDesativados(TipoGrafo* Grafo){
    int i, flag = 0;

    printf("\nEstações desativadas: ");

    for(i = 0; i < Grafo->NumVertices; i++){
        if(Grafo->verticesDesativados[i] == 0){
            flag = 1;
            printf("%d ", i+1);
        }
    }

    if(!flag)
        printf("nenhuma estação está desativada.");
}
