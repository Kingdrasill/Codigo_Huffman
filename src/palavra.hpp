#ifndef PALAVRA_HPP
#define PALAVRA_HPP

#include "huffman.hpp"

// Estrutura que guarda os dados de uma palavra
struct Word{
    std::string palavra;     // Aonde a palavra é guarda mesmo
    short int lenght; 
    float RP;      // Quantidade de vezes que a palavra apareceu
    short int value;    // O valor ASCii da palavra
    char initial;       // A inicial da palavra
    Tree* t;
};

void insertListaPalavra(List<Word> *lista, std::string palavra);   // Insere uma palavra em uma lista de palavras
int removeListaPalavra(List<Word> *lista, std::string palavra);   // Remove uma palavra de uma lista de palavras
void printListaPalavra(List<Word> *lista);                    // Printa uma lista de palavras
short int calcularValorPalavra(std::string palavra);             // Calcula o valor ASCii de uma palavra
bool pesquisaPalavra(List<Word> *lista, std::string palavra);
void setTreePalavra(List<Word> *lista, std::string palavra, Tree* t);
Word searchWordPalavra(List<Word> *lista, std::string palavra);

#endif