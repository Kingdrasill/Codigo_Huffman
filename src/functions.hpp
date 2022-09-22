#ifndef FILE_ENTRY
#define FILE_ENTRY

#include "documento.hpp"

void createWordRank(List<Record> *rank, Documento *doc);
void insertListaRankeamento(List<Record> *lista, Record r);
void createListNos(List<Tree*> *nos, List<Record> *rank);
void insertListNos(List<Tree*> *lista, Record r);
void identificadores(Tree** t, std::deque<bool> array, Documento *doc);
void compressFile(Documento *doc, std::string nome_text);
void decompressFile(Tree* raiz);
std::string boolToChar(bool *bools, short int s);
void charToBool(char *c, short int s, bool *b);

#endif