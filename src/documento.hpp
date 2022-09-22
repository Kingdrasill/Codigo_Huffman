#ifndef DOCUMENTO_HPP
#define DOCUMENTO_HPP

#include "listaPals.hpp"

// Estrutura que guarda um documento
struct Documento{
    List<Palavras> documento;
    std::string nome;
    int qtd;
};

void pegarDocumento(Documento *doc, std::string nome_text);
void normalizeRP(Documento *doc);
float findMaxRP(Documento *doc);
float findMinRP(Documento *doc);

#endif