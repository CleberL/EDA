#include<stdio.h>
#include<stdlib.h>

int particiona(int *v, int inicio, int final){
	int esq, dir, pivo, aux;
	esq = inicio;
	dir = final;
	pivo = v[inicio];
	while(esq <= dir){
		while(v[esq] <= pivo)
			esq++;
		while(v[dir] > pivo)
			dir--;
		if(esq<dir){
			aux=v[esq];
			v[esq] = v[dir];
			v[dir] = aux; 
		}
	}
	v[inicio] = v[dir];
	v[dir] = pivo;
	return dir;
}

void quickFind(int *v, int inicio, int final, int k){
	int pivo;
	if(final>=inicio){
		pivo=particiona(v, inicio, final);

		if(pivo == k-1){
			printf("%d", v[pivo]);
			return;
		}
		
		else if(pivo < k)
			quickFind(v,pivo+1,final,k);
		else
			quickFind(v,inicio,pivo-1,k);	
	}
}

void main(){
	int v[] = {7, 1, 3, 10, 17, 2, 21, 9};
	int i;
	int n = sizeof(v)/sizeof(int) -1;
	
	quickFind(v, 0, n, 8);

	printf("\n");
}
