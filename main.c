#include "metro.h"

int main(){
	FILE *fp;
	TipoGrafo* grafo;
	TipoVertice v1, v2;
	TipoPeso peso;
	int op, res, num;

	printf("1- Cria grafo.\n");
	printf("2- Insere Aresta.\n");
	printf("3- Existe Aresta.\n");
	printf("4- Retira Aresta\n");
	printf("5- Consulta Aresta\n");
	printf("6- Mostra Lista de Adjacentes.\n");
	printf("7- Mostra Grafo\n");
	printf("8- Libera Grafo\n");
	printf("9- Caminho mais curto.\n");
	printf("10- Insere Arestas Arquivo.\n");
	printf("11- Desativa Estação.\n");
	printf("12- Mostrar Estações Desativadas.\n");
	printf("13- Caminho mais barato.\n");
	printf("0- Sair.");

	do{
		printf("\nEscolha uma opcao:\n");
		scanf("%d",&op);

		switch(op){

			case 1:{

				printf("\nEscolha o numero de estações:\n");
				scanf("%d",&num);

				grafo = Cria_grafo(num);

				break;
			}

			case 2:{

				printf("\nPrimeira estação:\n");
				scanf("%d",&v1);

				printf("\nSegunda estação:\n");
				scanf("%d",&v2);

				printf("\nDistancia:\n");
				scanf("%f",&peso.distancia);

				printf("\nPreco:\n");
				scanf("%f",&peso.preco);

				res = InsereAresta(grafo, v1, v2, peso);

				if(res == 1){
					printf("\nAresta foi inserida.\n");
					GravaArestaArquivo(fp, v1, v2, peso);
				}
				else{
					if(res == 0)
						printf("\nAresta nao existe.\n");
					else
						printf("\nGrafo nao existe.\n");
				}

				break;
			}

			case 3:{

				printf("\nEscolha a primeira estação:\n");
				scanf("%d",&v1);

				printf("\nEscolha a segunda estação:\n");
				scanf("%d",&v2);

				res = ExisteAresta(grafo, v1, v2);

				if(res == 1)
					printf("\nAresta existe.\n");
				else{
					if(res == 0)
						printf("\nAresta nao existe.\n");
					else
						printf("\nGrafo nao existe.\n");
				}

				break;
			}

			case 4:{

				printf("\nEscolha a primeira estação:\n");
				scanf("%d",&v1);

				printf("\nEscolha a segunda estação:\n");
				scanf("%d",&v2);

				res = RetiraAresta(grafo, v1, v2);

				if(res == 1)
					printf("\nAresta foi retirada.\n");
				else{
					if(res == 0)
						printf("\nAresta nao existe.\n");
					else
						printf("\nGrafo nao existe.\n");
				}

				break;
			}

			case 5:{

				printf("\nEscolha a primeira estação:\n");
				scanf("%d",&v1);

				printf("\nEscolha a segunda estação:\n");
				scanf("%d",&v2);

				res = ConsultaAresta(grafo, v1, v2, &peso);

				if(res == 1)
					printf("O peso da aresta (%d,%d) = Distancia: %0.2f; Preco: %0.2f\n", v1, v2, peso.distancia, peso.preco);
				else{
					if(res == 0)
						printf("\nAresta nao existe.\n");
					else
						printf("\nGrafo nao existe.\n");
				}

				break;
			}

			case 6:{

				printf("\nEscolha a estação:\n");
				scanf("%d",&v1);

				MostraListaAdjacentes(grafo, v1);

				break;
			}

			case 7:{

				MostraGrafo(grafo);

				break;
			}

			case 8:{

				grafo = LiberaGrafo(grafo);

				break;
			}

			case 9:{

				printf("\nEscolha a estação de origem:\n");
				scanf("%d",&v1);

				printf("\nEscolha a estação de destino:\n");
				scanf("%d",&v2);

				Caminho_mais_Curto(grafo, v1, v2);

				break;
			}

			case 10:{

				if(InsereArestaArquivo(fp, grafo))
					printf("Arestas inseridas");

				break;
			}

			case 11:{

				printf("\nEscolha a estação:\n");
				scanf("%d",&v1);

				res = DesativaVertice(grafo, v1);

				if(res == 1)
					printf("Estação %d desativada\n", v1);
				else{
					if(res == 0)
						printf("\nEstação já estava desativada.\n");
					else
						printf("\nGrafo nao existe.\n");
				}

				break;
			}

			case 12:{
				VerticesDesativados(grafo);

				break;
			}

			case 13:{
				printf("\nEscolha a estação de origem:\n");
				scanf("%d",&v1);

				printf("\nEscolha a estação de destino:\n");
				scanf("%d",&v2);

				Caminho_mais_Barato(grafo, v1, v2);
			}

			default:
				;
		}
	}
	while(op != 0);

	return 0;
}
