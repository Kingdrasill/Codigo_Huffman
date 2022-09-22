# include "listaPals.hpp"

// Função para inserir uma palavra em uma lista de palavras de tamanho n
void insertLPTamanho(List<Palavras> *lista, std::string palavra) {
    Palavras palavras;
    int tam = static_cast<int> (palavra.size());
    palavras.tam = tam;

    if(lista->cabeca == lista->cauda)   // Caso a lista esteja vazia
    {
        palavras.qtd = 1;
        FLVazia(&palavras.listPal);
        insertListaPalavra(&palavras.listPal, palavra);  // Inseri a palavra na lista de palavra de tamanha n

        lista->cauda->prox = new Block<Palavras>;
        lista->cauda = lista->cauda->prox;
        lista->cauda->dado = palavras;
        lista->cauda->prox=nullptr;
    }
    else {
        Block<Palavras>* tmp = new Block<Palavras>; // Caso necessário um novo elemento na lista
        Block<Palavras>* aux;                                 // Variável auxiliar para andar na lista

        aux = lista->cabeca;
        while (aux->prox != nullptr && aux->prox->dado.tam < tam) {
            aux = aux->prox;
        }

        if(aux->prox != nullptr && aux->prox->dado.tam == tam)
        {
            aux->prox->dado.qtd++;
            insertListaPalavra(&aux->prox->dado.listPal, palavra);
        }
        else {
            palavras.qtd = 1;
            palavras.tam = tam;
            FLVazia(&palavras.listPal);
            insertListaPalavra(&palavras.listPal, palavra);  // Inseri a palavra na lista de palavra de tamanha n

            tmp->dado = palavras;
            tmp->prox = aux->prox;
            aux->prox = tmp;
            if(tmp->prox == nullptr)
                lista->cauda = tmp;
        }
    }
    lista->qtd++;
}

// Função para remover uma uma palavra em uma lista de palavras de tamanho n
int removeLPTamanho(List<Palavras> *lista, std::string palavra) {
    Block<Palavras>* aux;
    int tam = static_cast<int> (palavra.size());
    int removed = 0;
    
    aux = lista->cabeca;
    while(aux->prox != nullptr) {
        if(aux->prox->dado.tam == tam) {
            removed = removeListaPalavra(&aux->prox->dado.listPal, palavra);
            aux->prox->dado.qtd = aux->prox->dado.qtd - removed;
            if(aux->prox != nullptr && aux->prox->dado.qtd == 0) {
                aux->prox = aux->prox->prox;
            } else if(aux->prox == nullptr && aux->prox->dado.qtd == 0) {
                aux->prox = nullptr;
                lista->cauda = aux;
            }
            return removed;
        }
        aux = aux->prox;
    }

    return removed;
}

// Função para printar uma lista de lista de palavras de tamanho n
void printLPTamanho(List<Palavras> *lista) {
    Block<Palavras>* aux;
    aux = lista->cabeca;
    while (aux->prox != nullptr)
    {
        printf("Palavras de tamanho %d - Quantidade %d :\n", aux->prox->dado.tam, aux->prox->dado.qtd);
        printListaPalavra(&aux->prox->dado.listPal);
        aux=aux->prox;
    }
}

bool buscaLPTamanho(List<Palavras> *lista, std::string palavra) {
    Block<Palavras>* aux;
    int tam = static_cast<int> (palavra.size());

    aux = lista->cabeca;
    while(aux->prox != nullptr) {
        if(aux->prox->dado.tam == tam) 
            return pesquisaPalavra(&aux->prox->dado.listPal, palavra);

        aux = aux->prox;
    }
    return false;
}

void setTreeLPTamanho(List<Palavras> *lista, std::string palavra, Tree* t) {
    Block<Palavras>* aux;
    int tam = static_cast<int> (palavra.size());

    aux = lista->cabeca;
    while(aux->prox != nullptr) {
        if(aux->prox->dado.tam == tam) 
            return setTreePalavra(&aux->prox->dado.listPal, palavra, t);

        aux = aux->prox;
    }
}

Word searchWordLPTamanho(List<Palavras> *lista, std::string palavra) {
    Block<Palavras>* aux;
    int tam = static_cast<int> (palavra.size());

    aux = lista->cabeca;
    while(aux->prox != nullptr) {
        if(aux->prox->dado.tam == tam) 
            return searchWordPalavra(&aux->prox->dado.listPal, palavra);
        aux = aux->prox;
    }

    return Word();
}