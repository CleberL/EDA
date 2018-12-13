#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dado{
    char nome[10];
    int dado;
    int data; // data é ano+mes+dia, ex.: 20150507
};

void merge(struct dado *sensores, const int esq, const int dir);
void intercala(struct dado *sensores, int esq, int meio, int dir);
void insertion(struct dado *sensores, const int n);
void preencher(struct dado *aux,char newNome[10], int valor, int newData);

void main(int argc, char const *argv[]){
    struct dado *a = NULL;
    a = malloc(sizeof(struct dado)*5);
    
    preencher(&a[0], "distancia", 6, 20181105);
    preencher(&a[1], "temp.", 25, 20180225);
    preencher(&a[2], "umidade", 70, 20180614);
    preencher(&a[3], "luz", 20, 20180512);
    preencher(&a[4], "presenca", 4, 20181004);

    merge(a, 0, 4);
 //   insertion(a,5);

    for(int i = 0; i < 5; i++){
        printf("nome: %s    ", a[i].nome);
        printf("valor: %d    ", a[i].dado);
        printf("data de entrada: %d    \n", a[i].data);
    }

}

void preencher(struct dado *aux,char newNome[10], int valor, int newData){
    aux->dado = valor;
    strcpy(aux->nome, newNome);
    aux->data = newData;
}

void insertion(struct dado *sensores, const int n){
    int i, j;
    struct dado aux;
    for(i = 0; i < n ; i++){
        aux = sensores[i];
        for(j = i; (j > 0) && (aux.data < sensores[j-1].data); j--){
            sensores[j] = sensores[j-1];
        }
        sensores[j] = aux;
    }
}

void intercala(struct dado *sensores, int esq, int meio, int dir){
    int i, j, k;
    int tam_a = meio - esq + 1;
    int tam_b = dir-meio;

    struct dado *a = (struct dado *) malloc(sizeof(struct dado)*tam_a);
    struct dado *b = (struct dado *) malloc(sizeof(struct dado)*tam_b);

    for (i = 0; i < tam_a; i++)         //copia lado esquerdo
        a[i] = sensores[i+esq];
    for (i = 0; i < tam_b; i++)         //copia lado direito
        b[i] = sensores[i+meio+1];
    
    for (i = 0, j = 0, k = esq; k <= dir; k++) {     
        if (i == tam_a){    //copia o elementos de direita restantes
            sensores[k] = b[j++];
        }else if (j == tam_b){      //copia o elementos de esquerda restantes
             sensores[k] = a[i++];
        }else if (a[i].data < b[j].data){   //intercala
             sensores[k] = a[i++];
        }else{
            sensores[k] = b[j++];
        }
    }

free(a);
free(b);
}

void merge(struct dado *sensores, const int esq, const int dir){
    if(esq==dir)
        return;

    int meio = esq + (dir-esq)/2;
    merge(sensores, esq, meio);
    merge(sensores, meio+1, dir);
    intercala(sensores, esq, meio, dir);
    return;
}