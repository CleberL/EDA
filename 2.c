#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listarAmigos(const int grafo[10][10], const char pessoas[10][10], int id);
void adicionarAmizade(int amigo1, int amigo2, int grafo[10][10], const char pessoas[10][10]);
void removerAmizade(int amigo1, int amigo2, int grafo[10][10], const char pessoas[10][10]);
void printAmizade(int amigo1, int amigo2, const int grafo[10][10], const char pessoas[10][10]);
void snapshot(const int grafo[10][10]);
void init(int grafo[10][10]);

void main(int argc, char *argv[]){

	char pessoas[10][10] = {"cleber","adriano","joedyson","geovanne","breno","thomas","matheus","morgana","brenno","filipe"};	
	int grafo[10][10];

	init(grafo);

	adicionarAmizade(0, 5, grafo, pessoas);
	adicionarAmizade(0, 4, grafo, pessoas);
	adicionarAmizade(0, 2, grafo, pessoas);
	adicionarAmizade(1, 5, grafo, pessoas);
	adicionarAmizade(2, 4, grafo, pessoas);
	adicionarAmizade(3, 8, grafo, pessoas);
	adicionarAmizade(7, 9, grafo, pessoas);
	adicionarAmizade(6, 2, grafo, pessoas);
	adicionarAmizade(7, 3, grafo, pessoas);
	adicionarAmizade(3, 9, grafo, pessoas);

	removerAmizade(1, 5, grafo, pessoas);
	listarAmigos(grafo,pessoas, 0);
	listarAmigos(grafo,pessoas, 1);
	listarAmigos(grafo,pessoas, 2);
	listarAmigos(grafo,pessoas, 3);
	
//	snapshot(grafo);
}

void init(int grafo[10][10]){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			grafo[i][j] = 0;	
		}
	}
}

void snapshot(const int grafo[10][10]){
	printf("\n");
	for (int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			printf("%d ", grafo[i][j]);
		}
		printf("\n");
	}
}

void printAmizade(int amigo1, int amigo2, const int grafo[10][10], const char pessoas[10][10]){
	if(grafo[amigo1][amigo2]==1)
		printf("%s e amigo de %s\n", pessoas[amigo1],pessoas[amigo2]);
	else
		printf("%s e %s nao sao amigos\n", pessoas[amigo1],pessoas[amigo2]);
}

void adicionarAmizade(int amigo1, int amigo2, int grafo[10][10], const char pessoas[10][10]){
	grafo[amigo1][amigo2] = 1;
	grafo[amigo2][amigo1] = 1;
	printAmizade(amigo1, amigo2, grafo, pessoas);
}

void removerAmizade(int amigo1, int amigo2, int grafo[10][10],const char pessoas[10][10]){
	grafo[amigo1][amigo2] = 0;
	grafo[amigo2][amigo1] = 0;
	printAmizade(amigo1, amigo2, grafo, pessoas);
}

void listarAmigos(const int grafo[10][10], const char pessoas[10][10], int id){

	printf("\n");
	printf("Amigos de %s: ", pessoas[id]);

	int j = 0;
	for (int i = 0; i < 10 ; i++){
		if(grafo[id][i] == 1){
			printf("| %s |", pessoas[i]);
			j++;
		}
	}

	if(j == 0)
		printf("Nao tem amigos");

	printf("\n");
}
