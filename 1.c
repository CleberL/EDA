#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Contato{
    char *nome;
    char *telefone;
    int fb;
    struct Contato *esq;
    struct Contato *dir;
};

void inserir(struct Contato **avl, const char *nome, const char *telefone);
struct Contato *remover(struct Contato **avl, const char *nome);
void listar(struct Contato *avl);
void buscar(struct Contato *avl, const char *nome);
void balancear(struct Contato **avl);
void rotacionar_D(struct Contato **avl);
void rotacionar_DE(struct Contato **avl);
void rotacionar_E(struct Contato **avl);
void rotacionar_ED(struct Contato **avl);
void calc_fb(struct Contato **avl);
int altura(struct Contato *avl);


void main(){
    struct Contato *avl = NULL;
    
    inserir(&avl, "1", "4984816");
    inserir(&avl, "2", "87461531");
    inserir(&avl, "3", "846513");
	inserir(&avl, "4", "9813226");
    inserir(&avl, "5", "87461531");
    inserir(&avl, "6", "454658816");
    inserir(&avl, "7", "87461531");
    inserir(&avl, "8", "94513565");
	
	printf("\n");
	remover(&avl, "1");
	listar(avl);

	printf("\n");
	remover(&avl, "3");
	listar(avl);
}

void calc_fb(struct Contato **avl){
	if ((*avl) != NULL){

		calc_fb(&(*avl)->esq);
		calc_fb(&(*avl)->dir);

		(*avl)->fb = altura((*avl)->dir) - altura((*avl)->esq);
	}
}

int altura(struct Contato *avl){
	int ld = 0;
	int le = 0;
	if (avl == NULL){
		return 0;	
	}
	if(avl->esq){
		le = altura(avl->esq);
	}
	if(avl->dir){
		ld = altura(avl->dir);
	}
	if(le > ld){
		return le + 1;
	}else{
		return ld + 1;
	}
}

void balancear(struct Contato **avl){

	if (((*avl)->fb < -1)){

		if ((*avl)->esq->fb > 0){
			printf("rotacao dir-esq\n");
			rotacionar_DE(&(*avl));
			calc_fb(&(*avl));
		}else{
			printf("rotacao dir\n");
			rotacionar_D(&(*avl));
			calc_fb(&(*avl));
		}
	}

	if (((*avl)->fb) > 1){
		if(((*avl)->dir->fb) < 0){
			printf("rotacao esq-dir\n");
			rotacionar_ED(&(*avl));
			calc_fb(&(*avl));
		}else{
			printf("rotacao esq\n");
			rotacionar_E(&(*avl));
			calc_fb(&(*avl));
		}
	}

}

void rotacionar_D(struct Contato **avl){
	struct Contato **b = (struct Contato**)malloc(sizeof(struct Contato));
	(*b) = (*avl)->esq;

	(*avl)->esq = (*b)->dir;
	(*b)->dir = (*avl);
	(*avl) = (*b);
	free(b);
}

void rotacionar_DE(struct Contato **avl){
	struct Contato **b = (struct Contato**)malloc(sizeof(struct Contato));
	struct Contato **c = (struct Contato**)malloc(sizeof(struct Contato));
	(*b) = (*avl)->esq;
	(*c) = (*avl)->esq->dir;

	(*avl)->esq = (*c)->dir;
	(*b)->dir = (*c)->esq;
	(*c)->esq = (*b);
	(*c)->dir = (*avl);
	(*avl) = (*c); 
	free(b);
	free(c);
}

void rotacionar_E(struct Contato **avl){
	struct Contato **b = (struct Contato**)malloc(sizeof(struct Contato));
	(*b) = (*avl)->dir;

	(*avl)->dir = (*b)->esq;
	(*b)->esq = (*avl);
	(*avl) = (*b);
	free(b);
}

void rotacionar_ED(struct Contato **avl){
	struct Contato **b = (struct Contato**)malloc(sizeof(struct Contato));
	struct Contato **c = (struct Contato**)malloc(sizeof(struct Contato));
	(*b) = (*avl)->dir;
	(*c) = (*avl)->dir->esq;

	(*avl)->dir = (*c)->esq;
	(*b)->esq = (*c)->dir;
	(*c)->dir = (*b);
	(*c)->esq = (*avl);
	(*avl) = (*c);
	free(b);
	free(c);

}

void buscar(struct Contato *avl, const char* nome){
	if(strcmp(avl->nome,nome) == 0){
		printf("nome: %s	telefone: %s", avl->nome, avl->telefone);
	} else {
		if(strcmp(nome, avl->nome) > 0)
			buscar(avl->dir,nome);
		else
			buscar(avl->esq,nome);
	}
}

void listar(struct Contato *avl){
	
	if(avl != NULL){
		listar(avl->esq);
		printf("nome: %s    Telefone: %s\n",avl->nome, avl->telefone);
       	listar(avl->dir);
	}
}

void inserir(struct Contato **avl, const char *nome, const char *telefone){
 	
    if((*avl)==NULL){
        (*avl) = (struct Contato *)malloc (sizeof(struct Contato));
        (*avl)->nome = (char *) malloc(10*sizeof(char));
        (*avl)->telefone = (char *) malloc(15*sizeof(char));

        strcpy((*avl)->nome, nome);
        strcpy((*avl)->telefone, telefone);
        (*avl)->esq = NULL;
        (*avl)->dir = NULL;
    }else{
        if(strcmp((*avl)->nome, nome) >= 0)
            inserir(&((*avl)->esq),nome,telefone);
        else
            inserir(&((*avl)->dir),nome,telefone);
    }

    (*avl)->fb = altura((*avl)->dir) - altura((*avl)->esq);

    balancear(&(*avl));
}

struct Contato* remover(struct Contato **avl, const char *nome){

	struct Contato *aux = (struct Contato *)malloc (sizeof(struct Contato));
	struct Contato *pai = NULL;
				
	if ((!(*avl))){
		return NULL;
	}

	if(strcmp((*avl)->nome,nome) == 0){

		if ((*avl)->esq !=NULL){
			
			aux = (*avl)->esq;
			while(aux->dir != NULL){
				pai = aux;
				aux = aux->dir;
			}
			if (pai != NULL){
				pai->dir = aux->esq;
				aux->esq = (*avl)->esq;
			}
			aux->dir = (*avl)->dir;
			(*avl) = aux;

		}else if ((*avl)->dir != NULL){
			(*avl) = (*avl)->dir; 
		}else{
			(*avl) = NULL;
		}
		return (*avl);

	}else if(strcmp((*avl)->nome,nome) > 0){
		(*avl)->esq = remover(&(*avl)->esq,nome);
	}else{
		(*avl)->dir = remover(&(*avl)->dir,nome);
	}

	(*avl)->fb = altura((*avl)->dir) - altura((*avl)->esq);

	balancear(&(*avl));

    return (*avl);
}