#include<stdio.h>
#include<stdlib.h>

struct No {
	int valor;
	struct No *prox;
};

void init(int grafo[13][13]);
void inserirLigacao(int vertice1, int vertice2, int grafo[13][13]);
void buscaLargura(int grafo[13][13], struct No **fila, struct No **verificados);
int verificarMarcados(int num, struct No **fila);
void inserir(int numero, struct No **fila);
int remover(struct No **fila);
void snapshot(const int grafo[13][13]);
void profundidade(int grafo[13][13], int inicio, struct No **verificados);
void buscaProfundidade(int grafo[13][13], struct No **verificados);

void main(){
    struct No *fila = NULL;
	struct No *verificados = NULL;
	int grafo[13][13];
    init(grafo);

    inserirLigacao(0,1, grafo);
    inserirLigacao(0,2, grafo);
    inserirLigacao(0,3, grafo);
    inserirLigacao(1,2, grafo);
    inserirLigacao(2,4, grafo);
    inserirLigacao(2,5, grafo);
    inserirLigacao(4,5, grafo);
    inserirLigacao(5,6, grafo);
    inserirLigacao(6,7, grafo);
    inserirLigacao(3,7, grafo);
    inserirLigacao(6,8, grafo);
    inserirLigacao(7,8, grafo);
    inserirLigacao(8,9, grafo);
    inserirLigacao(8,11, grafo);
    inserirLigacao(9,11, grafo);
    inserirLigacao(9,10, grafo);
    inserirLigacao(11,12, grafo);
    inserirLigacao(10,12, grafo);

   //snapshot(grafo);
	
	buscaProfundidade(grafo, &verificados);
	
	buscaLargura(grafo,&fila, &verificados);


}

void init(int grafo[13][13]){
	for(int i = 0; i < 13; i++){
		for(int j = 0; j < 13; j++){
			grafo[i][j] = 0;	
		}
	}
}

int verificarMarcados(int num, struct No **fila){
	int retorno = 0;
	struct No *tmp = *(fila);

	while(tmp != NULL){
		if(tmp->valor == num){
			retorno = 2;
			break;
		}
		tmp = tmp->prox;
	}

	return retorno;
}

void inserirLigacao(int vertice1, int vertice2, int grafo[13][13]){
	grafo[vertice1][vertice2] = 1;
	grafo[vertice2][vertice1] = 1;
}

void inserir(int numero, struct No **fila){

	if((*fila) == NULL){
		struct No *tmp = malloc(sizeof(struct No));
		tmp->valor = numero;
		tmp->prox = NULL;
		(*fila) = tmp;
	}else{
		inserir(numero, &((*fila)->prox));
	}

}

int remover(struct No **fila){
	int aux;
	if(*fila == NULL){
		printf("Fila Vazia\n");
	}else{
		aux = (*fila)->valor;
		*fila = (*fila)->prox;
		return aux;
	}
}

void snapshot(const int grafo[13][13]){
	for (int i = 0; i < 13; i++){
		for(int j = 0; j < 13; j++){
			printf("%d ", grafo[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void buscaLargura(int grafo[13][13], struct No **fila, struct No **verificados){
	
	printf("Largura: ");
	inserir(0,fila);
	inserir(0,verificados);
	
	do{
		for(int i = 0; i < 13; i++){
			if(grafo[(*fila)->valor][i] == 1){
				if(verificarMarcados(i,verificados) == 0){
					inserir(i,fila);
					inserir(i,verificados);
				}
			}
		}
		printf("%d ", remover(fila));	
	}while(*fila != NULL);

	printf("\n");
}

void profundidade(int grafo[13][13], int inicio, struct No **verificados){
	inserir(inicio,verificados);
	int i;
	for(i = 0; i < 13; i++){
		if(grafo[inicio][i] == 1){
			if(verificarMarcados(i, verificados) == 0)
				profundidade(grafo, i, verificados);
		}
	}	
}

void buscaProfundidade(int grafo[13][13], struct No **verificados){

	profundidade(grafo, 0, verificados);

	printf("Profundidade: ");

	while ((*verificados)!=NULL){
		printf("%d ", remover(verificados));
	}
	printf("\n");
}
