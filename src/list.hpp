#ifndef LIST_HPP
#define LIST_HPP

// Estrutura para criar uma corrente de palavras
template <typename T>
struct Block{
    T dado;      // Dados da palavra
    Block<T> *prox;    // Ponteiro para próxima palavra
};

// Estrutura que armazena a cabeça e a cauda da corrente de palavras
template <typename T>
struct List{
    Block<T>* cabeca;  // Início da corrente
    Block<T>* cauda;   // Fim da corrente
    int qtd;           // Quantidade de elementos
};

// Esvazia uma lista de palavras
template <typename T>
void FLVazia(List<T> *lista){
    lista->cabeca = new Block<T>;
    lista->cauda = lista->cabeca;
    lista->cauda->prox = nullptr;
    lista->qtd = 0;
};

#endif