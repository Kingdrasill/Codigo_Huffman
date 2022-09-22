#include "tree.hpp"

Tree* CreateTree(){
	return nullptr;
}

void insertTree(Tree **t, Record r){

    if(*t == nullptr){
        *t = (Tree*)malloc(sizeof(Tree));
        (*t)->esq = nullptr; 
        (*t)->dir = nullptr; 
        (*t)->reg = r; 

    } else {
    
        if(r.RP < (*t)->reg.RP) {
            insertTree(&(*t)->dir, r);
        }
    
        if(r.RP > (*t)->reg.RP) {
            insertTree(&(*t)->esq, r);
        }

        if(r.RP == (*t)->reg.RP) {

            if(r.lenght < (*t)->reg.lenght) {
                insertTree(&(*t)->dir, r);
            }
            
            if(r.lenght > (*t)->reg.lenght) {
                insertTree(&(*t)->esq, r);
            }

            if(r.lenght == (*t)->reg.lenght) {

                if(r.value < (*t)->reg.value) {
                    insertTree(&(*t)->dir, r);
                }
                
                if(r.value > (*t)->reg.value) {
                    insertTree(&(*t)->esq, r);
                }
            }
        }
  
    }

}

void pesquisa(Tree **t, Tree **aux, Record r){

    if(*t == nullptr){
        printf("[ERROR]: Node not found!");
        return;
    }

    if(r.RP < (*t)->reg.RP) { pesquisa(&(*t)->dir, aux, r); return; }
    if(r.RP > (*t)->reg.RP) { pesquisa(&(*t)->esq, aux, r); return; }

    if(r.RP == (*t)->reg.RP) {

        if(r.lenght < (*t)->reg.lenght) { pesquisa(&(*t)->dir, aux, r); return; }
        if(r.lenght > (*t)->reg.lenght) { pesquisa(&(*t)->esq, aux, r); return; }

        if(r.lenght == (*t)->reg.lenght) {

            if(r.value < (*t)->reg.value) { pesquisa(&(*t)->dir, aux, r); return; }
            if(r.value > (*t)->reg.value) { pesquisa(&(*t)->esq, aux, r); return; }    
        }
    }

    *aux = *t;
}

void antecessor(Tree **t, Tree *aux){ 

    if ((*t)->dir != nullptr){ 
        antecessor(&(*t)->dir, aux);
        return;
    }
        
    aux->reg = (*t)->reg;
    aux = *t; 
    *t = (*t)->esq;
    free(aux);
} 


void removeTree(Tree **t, Record r){
	Tree *aux;
  	
  	if (*t == nullptr){ 
  		printf("[ERROR]: Record not found!!!\n");
    	return;
  	}

  	if(r.RP < (*t)->reg.RP) { removeTree(&(*t)->dir, r); return; }
    if(r.RP > (*t)->reg.RP) { removeTree(&(*t)->esq, r); return; }

    if(r.RP == (*t)->reg.RP) {

        if(r.lenght < (*t)->reg.lenght) { removeTree(&(*t)->dir, r); return; }
        if(r.lenght > (*t)->reg.lenght) { removeTree(&(*t)->esq, r); return; }

        if(r.lenght == (*t)->reg.lenght) {

            if(r.value < (*t)->reg.value) { removeTree(&(*t)->dir, r); return; }
            if(r.value > (*t)->reg.value) { removeTree(&(*t)->esq, r); return; }    
        }
    }

  	if ((*t)->dir == nullptr){ 
  		aux = *t;  
  		*t = (*t)->esq;
    	free(aux);
    	return;
  	}

  	if ((*t)->esq != nullptr){ antecessor(&(*t)->esq, *t); return; }

  	aux = *t;  
  	*t = (*t)->dir;
  	free(aux);
}

void preordem(Tree *t) {
  if(!(t == nullptr)){
    printf("%s ", t->reg.palavra.c_str());
    preordem(t->esq); 
    preordem(t->dir); 
  }
}


void central(Tree *t) {
  if(!(t == nullptr)){
    central(t->esq); 
    printf("%s ", t->reg.palavra.c_str());
    central(t->dir); 
  }
}

void posordem(Tree *t) {
  if(!(t == nullptr)){
    posordem(t->esq); 
    posordem(t->dir); 
    printf("%s ", t->reg.palavra.c_str());
  }
}

int altura(Tree *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = altura(raiz->esq);
        int dir = altura(raiz->dir);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}
