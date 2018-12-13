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

void inserir(struct Contato **arvore, const char *nome, const char *telefone);
struct Contato *remover(struct Contato **arvore, const char *nome);
void listar(struct Contato *arvore);
void buscar(struct Contato *arvore, const char *nome);
void balancear(struct Contato **arvore);
void rotacionar_D(struct Contato **arvore);
void rotacionar_DE(struct Contato **arvore);
void rotacionar_E(struct Contato **arvore);
void rotacionar_ED(struct Contato **arvore);
void calc_fb(struct Contato **arvore);
int altura(struct Contato *arvore);


void main(){
    struct Contato *arvore = NULL;
    
    inserir(&arvore, "jonatan", "4984816");
    inserir(&arvore, "joedyson", "87461531");
    inserir(&arvore, "matheus", "0800125426");
	inserir(&arvore, "eddie", "9813226");
    inserir(&arvore, "breno", "87461531");
    inserir(&arvore, "thomas", "454658816");
    inserir(&arvore, "geovanne", "87461531");
    inserir(&arvore, "cleber", "94513565");

	buscar(arvore, "thomas");

	remover(&arvore, "joedyson");
	remover(&arvore, "cleber");

	listar(arvore);
}


void calc_fb(struct Contato **arvore){
	if ((*arvore) != NULL){

		calc_fb(&(*arvore)->esq);
		calc_fb(&(*arvore)->dir);

		(*arvore)->fb = altura((*arvore)->dir) - altura((*arvore)->esq);
	}
}

int altura(struct Contato *arvore){
	int ld = 0;
	int le = 0;
	if (arvore == NULL){
		return 0;	
	}
	if(arvore->esq){
		le = altura(arvore->esq);
	}
	if(arvore->dir){
		ld = altura(arvore->dir);
	}
	if(le > ld){
		return le + 1;
	}else{
		return ld + 1;
	}
}

void balancear(struct Contato **arvore){

	if (((*arvore)->fb < -1)){

		if ((*arvore)->esq->fb > 0){
			printf("rotacao dir-esq\n");
			rotacionar_DE(&(*arvore));
			calc_fb(&(*arvore));
		}else{
			printf("rotacao dir\n");
			rotacionar_D(&(*arvore));
			calc_fb(&(*arvore));
		}
	}

	if (((*arvore)->fb) > 1){
		if(((*arvore)->dir->fb) < 0){
			printf("rotacao esq-dir\n");
			rotacionar_ED(&(*arvore));
			calc_fb(&(*arvore));
		}else{
			printf("rotacao esq\n");
			rotacionar_E(&(*arvore));
			calc_fb(&(*arvore));
		}
	}

}

void rotacionar_D(struct Contato **arvore){
	struct Contato **b = (struct Contato**)malloc(sizeof(struct Contato));
	(*b) = (*arvore)->esq;

	(*arvore)->esq = (*b)->dir;
	(*b)->dir = (*arvore);
	(*arvore) = (*b);
	free(b);
}

void rotacionar_DE(struct Contato **arvore){
	struct Contato **b = (struct Contato**)malloc(sizeof(struct Contato));
	struct Contato **c = (struct Contato**)malloc(sizeof(struct Contato));
	(*b) = (*arvore)->esq;
	(*c) = (*arvore)->esq->dir;

	(*arvore)->esq = (*c)->dir;
	(*b)->dir = (*c)->esq;
	(*c)->esq = (*b);
	(*c)->dir = (*arvore);
	(*arvore) = (*c); 
	free(b);
	free(c);
}

void rotacionar_E(struct Contato **arvore){
	struct Contato **b = (struct Contato**)malloc(sizeof(struct Contato));
	(*b) = (*arvore)->dir;

	(*arvore)->dir = (*b)->esq;
	(*b)->esq = (*arvore);
	(*arvore) = (*b);
	free(b);
}

void rotacionar_ED(struct Contato **arvore){
	struct Contato **b = (struct Contato**)malloc(sizeof(struct Contato));
	struct Contato **c = (struct Contato**)malloc(sizeof(struct Contato));
	(*b) = (*arvore)->dir;
	(*c) = (*arvore)->dir->esq;

	(*arvore)->dir = (*c)->esq;
	(*b)->esq = (*c)->dir;
	(*c)->dir = (*b);
	(*c)->esq = (*arvore);
	(*arvore) = (*c);
	free(b);
	free(c);

}


void buscar(struct Contato *arvore, const char* nome){
	if(strcmp(arvore->nome,nome) == 0){
		printf("nome: %s	telefone: %s\n", arvore->nome, arvore->telefone);
	} else {
		if(strcmp(nome, arvore->nome) > 0)
			buscar(arvore->dir,nome);
		else
			buscar(arvore->esq,nome);
	}
}

void listar(struct Contato *arvore){
	
	if(arvore != NULL){
		
		listar(arvore->esq);
		printf("nome: %s    Telefone: %s\n",arvore->nome, arvore->telefone);
		listar(arvore->dir);
	}
}

void inserir(struct Contato **arvore, const char *nome, const char *telefone){
 	
    if((*arvore)==NULL){
        (*arvore) = (struct Contato *)malloc (sizeof(struct Contato));
        (*arvore)->nome = (char *) malloc(10*sizeof(char));
        (*arvore)->telefone = (char *) malloc(15*sizeof(char));

        strcpy((*arvore)->nome, nome);
        strcpy((*arvore)->telefone, telefone);
        (*arvore)->esq = NULL;
        (*arvore)->dir = NULL;
    }else{
        if(strcmp((*arvore)->nome, nome) >= 0)
            inserir(&((*arvore)->esq),nome,telefone);
        else
            inserir(&((*arvore)->dir),nome,telefone);
    }

    (*arvore)->fb = altura((*arvore)->dir) - altura((*arvore)->esq);

    balancear(&(*arvore));

}

struct Contato* remover(struct Contato **arvore, const char *nome){

	struct Contato *aux = (struct Contato *)malloc (sizeof(struct Contato));
	struct Contato *pai = NULL;
				
	if ((!(*arvore))){
		return NULL;
	}

	if(strcmp((*arvore)->nome,nome) == 0){

		if ((*arvore)->esq !=NULL){
			
			aux = (*arvore)->esq;
			while(aux->dir != NULL){
				pai = aux;
				aux = aux->dir;
			}
			if (pai != NULL){
				pai->dir = aux->esq;
				aux->esq = (*arvore)->esq;
			}
			aux->dir = (*arvore)->dir;
			(*arvore) = aux;

		}else if ((*arvore)->dir != NULL){
			(*arvore) = (*arvore)->dir; 
		}else{
			(*arvore) = NULL;
		}
		return (*arvore);

	}else if(strcmp((*arvore)->nome,nome) > 0){
		(*arvore)->esq = remover(&(*arvore)->esq,nome);
	}else{
		(*arvore)->dir = remover(&(*arvore)->dir,nome);
	}

	(*arvore)->fb = altura((*arvore)->dir) - altura((*arvore)->esq);

	balancear(&(*arvore));

    return (*arvore);
}