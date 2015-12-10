#include <stdio.h>
#include <stdlib.h>
#include <float.h>


typedef struct {
    float distancia;
    float preco;
} TipoPeso;

typedef int TipoVertice;
typedef struct grafo TipoGrafo;

TipoGrafo *Cria_grafo(int Nvertices);

int InsereAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2, TipoPeso peso);

int ExisteAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2);

int RetiraAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2);

int ConsultaAresta(TipoGrafo *Grafo, TipoVertice v1, TipoVertice v2, TipoPeso *peso);

void MostraListaAdjacentes(TipoGrafo *Grafo, TipoVertice v);

void MostraGrafo(TipoGrafo *Grafo);

TipoGrafo *LiberaGrafo(TipoGrafo *Grafo);

int InsereArestaArquivo(FILE *fp, TipoGrafo *Grafo);

int GravaArestaArquivo(FILE *fp, TipoVertice v1, TipoVertice v2, TipoPeso peso);

void Caminho_mais_Curto(TipoGrafo *grafo, int origem, int destino);
