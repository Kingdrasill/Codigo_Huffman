#ifndef LIST_HPP
#define LIST_HPP

template <typename T>
struct Block{
    T dado;   
    Block<T> *prox;   
};

template <typename T>
struct List{
    Block<T>* cabeca;  
    Block<T>* cauda;  
    int qtd;         
};

template <typename T>
void FLVazia(List<T> *lista){
    lista->cabeca = new Block<T>;
    lista->cauda = lista->cabeca;
    lista->cauda->prox = nullptr;
    lista->qtd = 0;
};

#endif
