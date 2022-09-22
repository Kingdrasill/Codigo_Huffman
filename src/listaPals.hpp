#ifndef LISTAPALS_HPP
#define LISTAPALS_HPP

#include "palavra.hpp"

// Estrutura que guarda uma lista de palavras de tamanho n
struct Palavras{
    List<Word> listPal;
    int qtd;
    int tam;
};

void insertLPTamanho(List<Palavras> *lista, std::string palavra);  // Insere uma palavra em uma lista de palavras de tamanho n
int removeLPTamanho(List<Palavras> *lista, std::string palavra);   // Remove uma uma palavra em uma lista de palavras de tamanho n
void printLPTamanho(List<Palavras> *lista);                   // Printa uma lista de lista de palavras
bool buscaLPTamanho(List<Palavras> *lista, std::string palavra);
void setTreeLPTamanho(List<Palavras> *lista, std::string palavra, Tree* t);
Word searchWordLPTamanho(List<Palavras> *lista, std::string palavra);
#endif