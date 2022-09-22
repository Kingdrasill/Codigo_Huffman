#include "palavra.hpp"

// Função para inserir uma palavra em uma lista de palavras
void insertListaPalavra(List<Word> *lista, std::string palavra) {
    Word word;
    word.palavra = palavra;
    word.lenght = static_cast<int> (palavra.size());
    word.RP = 1;
    word.initial = palavra.at(0);
    word.value = calcularValorPalavra(palavra);

    Block<Word> *palavras;
    palavras = lista->cabeca;
    while (palavras->prox != nullptr) {
        if(palavras->prox->dado.value == word.value && palavras->prox->dado.initial == palavra.at(0) && palavras->prox->dado.palavra == palavra) {
            palavras->prox->dado.RP++;
            return;
        }
        palavras = palavras->prox;
    }
    

    lista->cauda->prox = new Block<Word>;
    lista->cauda = lista->cauda->prox;
    lista->cauda->dado = word;
    lista->cauda->prox=nullptr;
    lista->qtd++;
}

// Função para remover uma palavra de uma lista de palavras
int removeListaPalavra(List<Word> *lista, std::string palavra) {
    int removed = 0;
    Block<Word> *aux, *freeBloco;
    short int valor = calcularValorPalavra(palavra);
    
    aux = lista->cabeca;
    while (aux->prox!=nullptr)
    {
        if (aux->prox->dado.value == valor && aux->prox->dado.initial == palavra.at(0) && aux->prox->dado.palavra == palavra)   // Verifica se a palavra da próxima posição tem a mesma
        {                                                                                                                       // inicial, o mesmo valor ASCii e se é a mesma palavra que
            if (aux->prox == lista->cauda)                                                                                      // a palavra dada
            {
                removed = aux->prox->dado.RP;
                free(aux->prox);
                aux->prox = nullptr;
                lista->cauda = aux;
            }
            else {
                freeBloco = aux->prox;
                removed = freeBloco->dado.RP;
                aux->prox = aux->prox->prox;
                free(freeBloco);
            }
        }
        else {
            aux=aux->prox;
        }
    }

    lista->qtd = lista->qtd - removed;

    if(lista->cabeca == lista->cauda && lista->qtd > 0) {
        removed += lista->qtd;
        lista->qtd = lista->qtd - removed;
    }

    return removed;
}

// Função para printar uma lista de palavras
void printListaPalavra(List<Word> *lista) {
    Block<Word>* aux;
    aux = lista->cabeca;
    while (aux->prox != nullptr)
    {
        printf("%s\t %c\t%d\t%f\t%d\n",aux->prox->dado.palavra.c_str(), aux->prox->dado.initial, aux->prox->dado.value, aux->prox->dado.RP, aux->prox->dado.lenght);
        aux=aux->prox;
    }
    printf("\n");
}

// Função para calcula o valor ASCii de uma palavra
short int calcularValorPalavra(std::string palavra) {
    short int value = 0;

    for(size_t i=0; i < palavra.size(); i++) {    // Pega o valor ASCii de cada caracter de uma palavra e os soma
        value += palavra[i];
    }

    return value;
}

bool pesquisaPalavra(List<Word> *lista, std::string palavra)
{
    Block<Word> *aux;
    short int valor = calcularValorPalavra(palavra);
    
    aux = lista->cabeca;
    while (aux->prox!=nullptr)
    {
        if (aux->prox->dado.value == valor && aux->prox->dado.initial == palavra.at(0) && aux->prox->dado.palavra == palavra)  
            return true;
        else 
            aux=aux->prox;
    }

    return false;
}

void setTreePalavra(List<Word> *lista, std::string palavra, Tree* t) {
    Block<Word> *aux;
    short int valor = calcularValorPalavra(palavra);
    
    aux = lista->cabeca;
    while (aux->prox!=nullptr)
    {
        if (aux->prox->dado.value == valor && aux->prox->dado.initial == palavra.at(0) && aux->prox->dado.palavra == palavra) {
            aux->prox->dado.t = t;
            return;
        } else 
            aux=aux->prox;
    }
}

Word searchWordPalavra(List<Word> *lista, std::string palavra) {
    Block<Word> *aux;
    short int valor = calcularValorPalavra(palavra);
    
    aux = lista->cabeca;
    while (aux->prox!=nullptr)
    {
        if (aux->prox->dado.value == valor && aux->prox->dado.initial == palavra.at(0) && aux->prox->dado.palavra == palavra)  
            return aux->prox->dado;
        else 
            aux=aux->prox;
    }

    return Word();
}